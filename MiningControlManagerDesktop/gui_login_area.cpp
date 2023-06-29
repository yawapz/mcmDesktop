#include "logger/thread_logger.h"
#include "gui_login_area.h"

#include <QDebug>

gui_login_area::gui_login_area(QWidget *parent)
    : QWidget{parent}
{
    // Параметры отображения виджета
//-----------------------------------------------------------
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()/2, size.height()/2 - 110);
    this->setFocus();
    this->setFixedSize(220,320);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setStyleSheet("QWidget {color: white; background-color: #22262b};");
//-----------------------------------------------------------
    isConnected = false;

    int block_height = 30;
    QVBoxLayout* main_lay = new QVBoxLayout();

    server_line = new QLineEdit();
    ReadLastHostConnection();

    server_line->setPlaceholderText("Enter server url:port");
    server_line->setFixedHeight(block_height + 20);
    server_line->setStyleSheet("QLineEdit {color: red; padding: 5px; font-size: 16px;};");
    server_line->setContentsMargins(0,0,0,20);

    login_line = new QLineEdit();
    ReadLastLogin();

    login_line->setDragEnabled(true);
    login_line->setPlaceholderText("Enter your login");
    login_line->setFixedHeight(block_height);
    login_line->setStyleSheet("QLineEdit {color: white; padding: 5px; font-size: 16px;};");

    pw_line = new QLineEdit();
    pw_line->setDragEnabled(false);
    pw_line->setPlaceholderText("Enter your password");
    pw_line->setEchoMode(QLineEdit::Password);
    pw_line->setFixedHeight(block_height + 20);
    pw_line->setStyleSheet("QLineEdit {color: white; padding: 5px; font-size: 16px;};");
    pw_line->setContentsMargins(0,0,0,20);

    QLabel* text = new QLabel("<H1> Authorization </H1>");
    text->setAlignment(Qt::AlignmentFlag::AlignCenter);
    text->setContentsMargins(0,0,0,10);
    QPushButton *enter = new QPushButton("Go");
    enter->setFixedHeight(block_height);
    QObject::connect(enter, SIGNAL(clicked(bool)), this, SLOT(authorization()));
    QPushButton *reg = new QPushButton("Registration");
    reg->setFixedHeight(block_height);
    QObject::connect(reg, SIGNAL(clicked(bool)), this, SLOT(registration()));
    exit = new QPushButton("Exit");
    exit->setFixedHeight(block_height);
    QObject::connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));

    QVBoxLayout *button_lay = new QVBoxLayout();
    button_lay->setAlignment(Qt::AlignmentFlag::AlignBottom);
    button_lay->addWidget(enter);
    button_lay->addWidget(reg);
    button_lay->addWidget(exit);

    main_lay->addWidget(text);
    main_lay->addWidget(server_line);
    main_lay->addWidget(login_line);
    main_lay->addWidget(pw_line);
    main_lay->addLayout(button_lay);
    this->setLayout(main_lay);

    this->log = new thread_logger();
    this->log->start();

    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString, QString)), this, SLOT(access_checker(QString, QString)));
    QObject::connect(this, SIGNAL(signal_send_user_data(user_data)), this, SLOT(accept_json(user_data)));
    QObject::connect(this, SIGNAL(signal_soc_connected()), this, SLOT(slot_connected()));

    QTimer *t =  new QTimer();
    QTimer *t2 = new QTimer();
    t2->setInterval(500);
    QObject::connect(t, SIGNAL(timeout()), this, SLOT(slot_connector()));
    QObject::connect(this, SIGNAL(signal_soc_connected()), t, SLOT(stop()));
    QObject::connect(this, SIGNAL(signal_disconnect()), t, SLOT(start()));
    t->start(1000);

    QObject::connect(this, SIGNAL(signal_soc_connected()), t2, SLOT(start()));
    QObject::connect(t2, SIGNAL(timeout()), this, SLOT(slot_checker()));
    QObject::connect(this, SIGNAL(signal_disconnect()), t2, SLOT(stop()));

    if(!server_line->text().isEmpty())
    {
        if(!login_line->text().isEmpty())
            pw_line->setFocus();
        else
            login_line->setFocus();
    }
    else
        server_line->setFocus();
}

gui_login_area::~gui_login_area()
{
    resault->deleteLater();
    login_line->deleteLater();
    pw_line->deleteLater();
    server_line->deleteLater();
    log->deleteLater();
}

void gui_login_area::keyReleaseEvent(QKeyEvent *event)
{
    if(QString::number(event->key()) == "16777220" || QString::number(event->key()) == "16777221")
    {
        authorization();
    }
    else if (QString::number(event->key()) == "16777216")
        exit->click();
}

void gui_login_area::ReadLastHostConnection()
{
    QFile *hist_file = new QFile("res/lastHostConnection");
    QTextStream *hist_stream = new QTextStream(hist_file);
    hist_file->open(QFile::ReadOnly);
    QString hist;
    *hist_stream >> hist;
    server_line->setText(hist);
    hist_file->deleteLater();
    delete hist_stream;
}

void gui_login_area::WriteLastHostConnection()
{
    QFile *hist_file = new QFile("res/lastHostConnection");
    QTextStream *hist_stream = new QTextStream(hist_file);
    hist_file->open(QFile::ReadWrite);
    *(hist_stream) << server_line->text();
    hist_stream->flush();
    hist_file->deleteLater();
    delete hist_stream;
}

void gui_login_area::ReadLastLogin()
{
    QFile *hist_file = new QFile("res/lastLogin");
    QTextStream *hist_stream = new QTextStream(hist_file);
    hist_file->open(QFile::ReadOnly);
    QString hist;
    *hist_stream >> hist;
    login_line->setText(hist);
    hist_file->deleteLater();
    delete hist_stream;
}

void gui_login_area::WriteLastLogin()
{
    QFile *hist_file = new QFile("res/lastLogin");
    QTextStream *hist_stream = new QTextStream(hist_file);
    hist_file->open(QFile::WriteOnly);
    *(hist_stream) << login_line->text();
    hist_stream->flush();
    hist_file->deleteLater();
    delete hist_stream;
}

void gui_login_area::authorization()
{
    if(isConnected)
    {
        this->setEnabled(false);
        emit signal_login(login_line->text(), pw_line->text());
    }
}

void gui_login_area::gui_transit()
{
    emit call_farm_list_form();
}

void gui_login_area::registration()
{
    if(isConnected)
        emit call_reg_form();
}

void gui_login_area::access_checker(QString req, QString cmd)
{
    if(cmd == "login")
    {
        if(req == "yes")
        {
            WriteLastLogin();
            emit signal_get_user_data(login_line->text());
        }
        else
        {
            this->setEnabled(true);
            this->pw_line->clear();
            QTimer *t = new QTimer();
            t->start(300);
            QObject::connect(t, SIGNAL(timeout()), this, SLOT(slot_red()));

            QTimer *t2 = new QTimer();
            t2->start(500);
            QObject::connect(t2, SIGNAL(timeout()), this, SLOT(slot_white()));

            QTimer *t3 = new QTimer();
            t3->start(1000);
            QObject::connect(t3, SIGNAL(timeout()), t, SLOT(stop()));
            QObject::connect(t3, SIGNAL(timeout()), t2, SLOT(stop()));
            QObject::connect(t3, SIGNAL(timeout()), t, SLOT(deleteLater()));
            QObject::connect(t3, SIGNAL(timeout()), t2, SLOT(deleteLater()));
            QObject::connect(t3, SIGNAL(timeout()), t3, SLOT(deleteLater()));
            QObject::connect(t3, SIGNAL(timeout()), this, SLOT(slot_white()));
            emit this->log->signal_write_to_logfile("Error authorization for " + this->login_line->text());
        }
    }
}

void gui_login_area::accept_json(user_data new_data)
{
    data = new_data;
    data.JSON_server_to_desktop_parcer();
    emit this->send_authorization_data_to_another_form(this->login_line->text(), this->pw_line->text(), data);
    this->gui_transit();
    emit this->log->signal_write_to_logfile("Successful authorization for " + this->login_line->text());
    this->log->quit();
}

void gui_login_area::slot_red()
{
    login_line->setStyleSheet("QLineEdit {color: red; padding: 5px; font-size: 16px;};");
    pw_line->setStyleSheet("QLineEdit {color: red; padding: 5px; font-size: 16px;};");
}

void gui_login_area::slot_white()
{
    login_line->setStyleSheet("QLineEdit {color: white; padding: 5px; font-size: 16px;};");
    pw_line->setStyleSheet("QLineEdit {color: white; padding: 5px; font-size: 16px;};");
}

void gui_login_area::slot_connected()
{
    isConnected = true;
    server_line->setStyleSheet("QLineEdit {color: green; padding: 5px; font-size: 16px;};");
    lastHostConnection = server_line->text();
    WriteLastHostConnection();
}

void gui_login_area::slot_connector()
{
    bool isPort = false;
    QString IP;
    QString s_port;
    if(server_line->text().length() > 10)
    {
        for (auto& ch : server_line->text())
        {
            if(!isPort)
            {
                if(ch != ':')
                {
                    IP += ch;
                }
                else
                {
                    isPort = true;
                }
            }
            else
            {
                s_port += ch;
            }
        }
    }
    emit signal_try_connect(IP, s_port.toInt());
}

void gui_login_area::slot_checker()
{
    if(server_line->text() != lastHostConnection)
    {
        isConnected = false;
        server_line->setStyleSheet("QLineEdit {color: red; padding: 5px; font-size: 16px;};");
        emit signal_disconnect();
    }
}
