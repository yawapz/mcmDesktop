#include "gui_user_settings.h"

gui_user_settings::gui_user_settings(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(300, 300);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setStyleSheet("QWidget {color: white; background-color: #22262b};");

    QSize wid(125,35);
    int f_height = 30;

    QHBoxLayout *block = new QHBoxLayout();
    block->setContentsMargins(0,0,0,20);
    QWidget *change_w = new QWidget();
    QVBoxLayout *change_l = new QVBoxLayout();
    QLabel *change = new QLabel("Change data");
    change->setStyleSheet("QLabel {background-color: transparent; font-size: 18px;}");
    change_w->installEventFilter(this);
    change_w->setStyleSheet("QWidget {background-color: transparent};");
    change_w->setAttribute(Qt::WA_Hover);
    change_w->setFixedSize(wid);
    change_l->addWidget(change);
    change_w->setLayout(change_l);

    QWidget *delUsr_w = new QWidget();
    QVBoxLayout *delUsr_l = new QVBoxLayout();
    QLabel *delUsr = new QLabel("Delete user");
    delUsr->setStyleSheet("QLabel {background-color: transparent; font-size: 18px;}");
    delUsr_w->installEventFilter(this);
    delUsr_w->setStyleSheet("QWidget {background-color: transparent};");
    delUsr_w->setAttribute(Qt::WA_Hover);
    delUsr_w->setFixedSize(wid);
    delUsr_l->addWidget(delUsr);
    delUsr_w->setLayout(delUsr_l);

    block->addWidget(change_w);
    block->addWidget(delUsr_w);
    lbls.push_back(change_w);
    lbls.push_back(delUsr_w);
    current_login = new QLineEdit();
    current_login->setFixedHeight(f_height);
    current_login->setStyleSheet("QLineEdit {padding: 5px;};");
    current_password = new QLineEdit();
    current_password->setEchoMode(QLineEdit::Password);
    current_password->setFixedHeight(f_height);
    current_password->setStyleSheet("QLineEdit {padding: 5px;};");
    new_login = new QLineEdit();
    new_login->setFixedHeight(f_height);
    new_login->setStyleSheet("QLineEdit {padding: 5px;};");
    new_password = new QLineEdit();
    new_password->setEchoMode(QLineEdit::Password);
    new_password->setFixedHeight(f_height);
    new_password->setStyleSheet("QLineEdit {padding: 5px;};");

    save_button = new QPushButton("Save сhanges");
    save_button->setFixedHeight(f_height);
    delete_button = new QPushButton("Delete current user");
    delete_button->setFixedHeight(f_height);
    exit = new QPushButton("Back");
    exit->setFixedHeight(f_height);

    QObject::connect(this, SIGNAL(signal_accept_user_data(QString,QString, user_data)), this, SLOT(slot_accept_user_data(QString,QString,user_data)));
    QObject::connect(this, SIGNAL(signal_new_pos(QPoint, QSize)), this, SLOT(slot_set_pos(QPoint, QSize)));
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString,QString)), this, SLOT(slot_accept_server_answer(QString, QString)), Qt::UniqueConnection);
    QObject::connect(save_button, SIGNAL(clicked()), this, SLOT(slot_update_request()));
    QObject::connect(delete_button, SIGNAL(clicked()), this, SLOT(slot_warning()));
    QObject::connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(exit, SIGNAL(clicked(bool)), this, SIGNAL(signal_unlock()));

    QVBoxLayout *main_lay = new QVBoxLayout();

    current_login->setPlaceholderText("Enter current login");
    current_password->setPlaceholderText("Enter current password");
    new_login->setPlaceholderText("Enter new login");
    new_password->setPlaceholderText("Enter new password");

    main_lay->addLayout(block);
    main_lay->addWidget(current_login);
    main_lay->addWidget(current_password);
    main_lay->addWidget(new_login);
    main_lay->addWidget(new_password);

    QVBoxLayout *button_lay = new QVBoxLayout();
    button_lay->setAlignment(Qt::AlignmentFlag::AlignBottom);
    button_lay->addWidget(save_button);
    button_lay->addWidget(delete_button);
    button_lay->addWidget(exit);

    main_lay->addLayout(button_lay);

    this->setLayout(main_lay);

    new_login->show();
    new_password->show();
    delete_button->hide();
    save_button->show();
}

gui_user_settings::~gui_user_settings()
{
    this->current_login->deleteLater();
    this->current_password->deleteLater();
    this->new_login->deleteLater();
    this->new_password->deleteLater();
    this->delete_button->deleteLater();
    this->save_button->deleteLater();
    this->exit->deleteLater();
    for (auto& iter : lbls)
    {
        iter->deleteLater();
    }
}

void gui_user_settings::closeEvent(QCloseEvent *)
{
    emit this->signal_exit_prog();
}

bool gui_user_settings::eventFilter(QObject *obj, QEvent * event)
{
    for (int i = 0; i < lbls.size(); ++i)
    {
        if(obj == lbls[i])
        {
            QEvent::Type type = event->type();
            if  (type == QEvent::HoverLeave)
            {
                this->lbls[i]->setStyleSheet("QWidget {background-color: transparent; border: none; border-radius: 3px};");
            }
            else if (type == QEvent::HoverEnter)
            {
                this->lbls[i]->setStyleSheet("QWidget {background-color: rgba(35, 146, 220, 0.5); border: none; border-radius: 3px};");
                if(obj == lbls[0])
                {
                    new_login->show();
                    new_password->show();
                    delete_button->hide();
                    save_button->show();
                }
                else if(obj == lbls[1])
                {
                    save_button->hide();
                    new_login->hide();
                    new_password->hide();
                    delete_button->show();
                }

            } else if (type == QEvent::MouseButtonPress)
            {
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void gui_user_settings::blink_lineE()
{
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
}

void gui_user_settings::slot_accept_user_data(QString l, QString p, user_data)
{
    login = l;
    password = p;
}

void gui_user_settings::slot_update_request()
{
    if(current_login->text() == login && current_password->text() == password)
    {
        this->setEnabled(false);
        emit signal_change_user_data(current_login->text(), current_password->text(), new_login->text(), new_password->text());
    }
    else
        blink_lineE();
}

void gui_user_settings::slot_delete_request()
{
    this->setEnabled(false);
    emit signal_delete_user(current_login->text(), current_password->text());
}

void gui_user_settings::slot_accept_server_answer(QString req, QString cmd)
{
    if(cmd == "update_user_data" || cmd == "del_user")
    {
        if(req == "yes")
        {
            slot_restart_programm();
        }
        else
        {
            this->setEnabled(true);
            blink_lineE();
        }
        this->current_login->clear();
        this->current_password->clear();
        this->new_login->clear();
        this->new_password->clear();
    }
}

void gui_user_settings::slot_restart_programm()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void gui_user_settings::slot_warning()
{
    if(current_login->text().isEmpty() || current_password->text().isEmpty() || current_login->text() != login || current_password->text() != password)
    {
        blink_lineE();
    }
    else
    {
        emit signal_delete_user(current_login->text(), current_password->text());
        slot_restart_programm();
    }
}

void gui_user_settings::slot_unlock_form()
{
    this->setEnabled(true);
}

void gui_user_settings::slot_set_pos(QPoint new_pos, QSize size)
{
    this->move(new_pos.x() + (size.width() / 2) - 150, new_pos.y() + 300);
}

void gui_user_settings::slot_red()
{
    current_login->setStyleSheet("QLineEdit {color: red; padding: 5px;};");
    current_password->setStyleSheet("QLineEdit {color: red; padding: 5px;};");
    new_login->setStyleSheet("QLineEdit {color: red; padding: 5px;};");
    new_password->setStyleSheet("QLineEdit {color: red; padding: 5px;};");
}

void gui_user_settings::slot_white()
{
    current_login->setStyleSheet("QLineEdit {color: white; padding: 5px;};");
    current_password->setStyleSheet("QLineEdit {color: white; padding: 5px;};");
    new_login->setStyleSheet("QLineEdit {color: white; padding: 5px;};");
    new_password->setStyleSheet("QLineEdit {color: white; padding: 5px;};");
}
