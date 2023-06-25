#include "gui_worker_settings.h"

gui_worker_settings::gui_worker_settings(QWidget *parent)
    : QWidget{parent}
{
    host = "127.0.0.1";
    port = 48048;
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setStyleSheet("QWidget {color: white; background-color: #22262b};");

    QObject::connect(this, SIGNAL(signal_new_pos(QPoint, QSize)), this, SLOT(slot_accept_new_pos(QPoint, QSize)));
    QObject::connect(this, SIGNAL(signal_inc_data(QString,QString,user_data)),this, SLOT(slot_accept_inc_data(QString,QString,user_data)));
    QObject::connect(this, SIGNAL(signal_data_accepted()),this, SLOT(slot_build_interface()));
    QObject::connect(this, SIGNAL(signal_host_data(QString,int)), this, SLOT(slot_host_data(QString,int)));

}

gui_worker_settings::~gui_worker_settings()
{
    this->soc->deleteLater();
    emit signal_unlock();
}

void gui_worker_settings::widget_list_cleaner()
{
    for (auto& iter : widget_list)
    {
        iter->deleteLater();
    }
    this->layout()->deleteLater();
    widget_list.clear();
}

void gui_worker_settings::closeEvent(QCloseEvent*)
{
    emit signal_unlock();
}

void gui_worker_settings::slot_accept_inc_data(QString l, QString p, user_data d)
{
    this->login = l;
    this->password = p;
    this->data = d;
    emit signal_data_accepted();
}

void gui_worker_settings::slot_build_interface()
{
    delete this->layout();
    widget_list_cleaner();
    QVBoxLayout *main_container = new QVBoxLayout();
    unsigned short int count_blocks = 2 + data.getTotal_count_WORKERs();

    this->setFixedHeight(count_blocks * (36 + 6));

    if(data.getTotal_count_WORKERs() == 0)
    {
        unsigned short int count_blocks = 3;
        this->setFixedHeight(count_blocks * (36 + 6));
        // Информация, что воркеров нет
        QLabel *no_workers = new QLabel("The user has no workers");
        no_workers->setStyleSheet("QLabel {font-size: 18px; text-align: center;}");
        main_container->addWidget(no_workers);
        widget_list.push_back(no_workers);
    }
    else
    {
        for (auto& iter : widget_list)
        {
            main_container->removeWidget(iter);
            iter->deleteLater();
        }
        widget_list.clear();

        unsigned short int count_blocks = 2 + data.getTotal_count_WORKERs();
        this->setFixedHeight(count_blocks * (36 + 6));
        // Информация с блоком о каждом воркере
        for (int i = 0; i < data.getTotal_count_WORKERs(); ++i)
        {
            QWidget *worker_widget = new QWidget();
            worker_widget->setFixedSize(350, 36);
            worker_widget->setStyleSheet("QWidget {background-color: #363d45; border: none; border-radius: 3px};");
            worker_widget->setAttribute(Qt::WA_Hover);
            worker_widget->installEventFilter(this);
            QHBoxLayout *worker_lay = new QHBoxLayout();

            QLabel *worker_name = new QLabel(data.getRIGS()[i].name);
            worker_name->setStyleSheet("background-color: transparent");
            worker_name->setFixedSize(200,18);
            QLabel *worker_id = new QLabel(data.getRIGS()[i].ID);
            worker_id->setStyleSheet("background-color: transparent");
            worker_id->setFixedSize(100, 18);
            worker_id->setCursor(Qt::PointingHandCursor);
            worker_id->setTextInteractionFlags(Qt::TextSelectableByMouse);

            QPushButton *worker_del_btn = new QPushButton();
            worker_del_btn->setContentsMargins(0,0,0,0);
            worker_del_btn->setCursor(Qt::PointingHandCursor);
            QPixmap *icon = new QPixmap("res/del_btn.svg");
            QPainter qp = QPainter(icon);
            qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
            qp.fillRect(icon->rect(), QColor(Qt::white));
            qp.end();
            worker_del_btn->setIcon(*icon);
            worker_del_btn->setIconSize(QSize(18,18));
            worker_del_btn->setFlat(true);

            QObject::connect(worker_del_btn, SIGNAL(clicked(bool)), this, SLOT(slot_delete_worker()));

            worker_lay->addWidget(worker_name);
            worker_lay->addWidget(worker_id);
            worker_lay->addWidget(worker_del_btn, Qt::AlignmentFlag::AlignRight);

            worker_widget->setLayout(worker_lay);
            //main_container->addWidget(worker_widget);
            widget_list.push_back(worker_widget);
        }
        // Так будет работать EventFilter
        for (auto& iter : widget_list)
        {
            main_container->addWidget(iter);
        }
    }
    // Кнопка добавления воркера
    QPushButton *add_worker = new QPushButton("Add worker");
    QObject::connect(add_worker, SIGNAL(clicked(bool)), this, SLOT(slot_add_worker()));
    add_worker->setFixedHeight(36);
    QPushButton *exit = new QPushButton("Exit");
    QObject::connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    exit->setFixedHeight(36);

    main_container->addWidget(add_worker);
    main_container->addWidget(exit);
    widget_list.push_back(add_worker);
    widget_list.push_back(exit);
    this->setLayout(main_container);
}

void gui_worker_settings::slot_delete_worker()
{
    this->setEnabled(false);
    soc = new QTcpSocket();
    QObject::connect(soc, SIGNAL(readyRead()), this, SLOT(slot_check_result_operation()));
    this->setEnabled(false);
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    QString command = "del_worker";
    stream << command;
    stream << data.RIGS[current_element].ID;

    if(!soc->isOpen())
        soc->connectToHost(host, port);
    soc->waitForConnected(1000);
    soc->write(*barr);
    soc->flush();
    delete barr;

    QEventLoop *loop = new QEventLoop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, loop, &QEventLoop::quit);
    t.connect(soc, SIGNAL(readyRead()), loop, SLOT(quit()));
    t.start(5*1000); // 5 sec
    loop->exec();
    loop->deleteLater();
}

void gui_worker_settings::slot_add_worker()
{
    soc = new QTcpSocket();
    QObject::connect(soc, SIGNAL(readyRead()), this, SLOT(slot_check_result_operation()));
    this->setEnabled(false);
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    QString command = "add_worker";
    stream << command;
    stream << login;

    if(!soc->isOpen())
        soc->connectToHost(host, port);
    soc->waitForConnected(1000);
    soc->write(*barr);
    soc->flush();
    delete barr;

    QEventLoop *loop = new QEventLoop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, loop, &QEventLoop::quit);
    t.connect(soc, SIGNAL(readyRead()), loop, SLOT(quit()));
    t.start(5*1000); // 5 sec
    loop->exec();
    loop->deleteLater();
}

void gui_worker_settings::slot_check_result_operation()
{
    soc->waitForReadyRead(1000);
    QString req = "no";
    QByteArray barr = soc->readAll();
    QDataStream stream(&barr, QIODevice::ReadOnly);
    stream >> req;

    soc->waitForDisconnected(1000);
    soc = new QTcpSocket();
    QObject::connect(soc, SIGNAL(readyRead()), this, SLOT(slot_accept_json()));

    if(req == "yes")
    {
        QByteArray *barr2 = new QByteArray();
        QDataStream stream(barr2, QIODevice::Append);
        QString command = "get_user_data";
        stream << command;
        stream << login;
        if(!soc->isOpen())
            soc->connectToHost(host, port);
        soc->waitForConnected(1000);
        soc->write(*barr2);
        soc->flush();
        delete barr2;

        QEventLoop *loop2 = new QEventLoop;
        QTimer t2;
        t2.connect(&t2, &QTimer::timeout, loop2, &QEventLoop::quit);
        t2.connect(soc, SIGNAL(readyRead()), loop2, SLOT(quit()));
        t2.start(5*1000); // 5 sec
        loop2->exec();
        loop2->deleteLater();
    }
    this->setEnabled(true);
}

void gui_worker_settings::slot_accept_json()
{
    soc->waitForReadyRead(1000);
    QByteArray barr = soc->readAll();
    QDataStream stream(&barr, QIODevice::ReadOnly);
    QJsonObject jsonObject;
    stream >> jsonObject;
    data.main_json_file = jsonObject;
    data.JSON_server_to_desktop_parcer();
    soc->waitForDisconnected(1000);
    slot_build_interface();
    emit signal_send_data(data);
}

void gui_worker_settings::slot_accept_new_pos(QPoint new_pos, QSize size)
{
    this->move(new_pos.x() + (size.width() / 2) - 150, new_pos.y() + 300);
}

void gui_worker_settings::slot_host_data(QString h, int p)
{
    host = h;
    port = p;
}

bool gui_worker_settings::eventFilter(QObject *obj, QEvent *event)
{
    for (int i = 0; i < widget_list.size(); ++i)
    {
        if (obj == widget_list[i])
        {
            QEvent::Type type = event->type();
            if  (type == QEvent::HoverLeave)
            {
                widget_list[i]->setStyleSheet("QWidget {background-color: #363d45; border: none; border-radius: 3px};");
            }
            else if (type == QEvent::HoverEnter)
            {
                this->current_element = i;
                widget_list[i]->setStyleSheet("QWidget {background-color: rgba(35, 146, 220, 0.5); border: none; border-radius: 3px;};");

            } else if (type == QEvent::MouseButtonPress)
            {
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}
