#include "logger/thread_logger.h"
#include "gui_login_area.h"
#include <QScreen>
#include <QDebug>

gui_login_area::gui_login_area(QWidget *parent)
    : QWidget{parent}
{
        QVBoxLayout* main_lay = new QVBoxLayout();

        QVBoxLayout* login_lay = new QVBoxLayout();
        QLabel* login_label = new QLabel("Enter your login");
        login_line = new QLineEdit();

        login_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        login_line->setDragEnabled(true);
        login_line->setPlaceholderText("login");
        login_line->setAlignment(Qt::AlignmentFlag::AlignCenter);

        QVBoxLayout* pw_lay = new QVBoxLayout();
        QLabel* pw_label = new QLabel("Enter your password");
        pw_line = new QLineEdit();

        pw_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pw_line->setDragEnabled(false);
        pw_line->setPlaceholderText("password");
        pw_line->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pw_line->setEchoMode(QLineEdit::Password);

        login_lay->addWidget(login_label);
        login_lay->addWidget(login_line);
        pw_lay->addWidget(pw_label);
        pw_lay->addWidget(pw_line);

        QLabel* text = new QLabel("<H1> Authorization </H1>");
        text->setAlignment(Qt::AlignmentFlag::AlignCenter);
        QPushButton * enter = new QPushButton("Go");
        QObject::connect(enter, SIGNAL(clicked(bool)), this, SLOT(authorization()));
        QPushButton * reg = new QPushButton("Registration");
        QObject::connect(reg, SIGNAL(clicked(bool)), this, SLOT(registration()));

        resault = new QLabel();
        resault->setAlignment(Qt::AlignmentFlag::AlignCenter);

        main_lay->addWidget(text);
        main_lay->addLayout(login_lay);
        main_lay->addLayout(pw_lay);
        main_lay->addWidget(enter);
        main_lay->addWidget(reg);
        main_lay->addWidget(resault);
        main_lay->setAlignment(Qt::AlignmentFlag::AlignTop);
        this->setLayout(main_lay);

        this->log = new thread_logger();
                this->log->start();

        QObject::connect(this, SIGNAL(signal_send_answer_resault(QString, QString)), this, SLOT(access_checker(QString, QString)));
        QObject::connect(this, SIGNAL(signal_send_user_data(user_data)), this, SLOT(accept_json(user_data)));
}

gui_login_area::~gui_login_area()
{
    resault->deleteLater();
    login_line->deleteLater();
    pw_line->deleteLater();
    log->deleteLater();
}

void gui_login_area::keyReleaseEvent(QKeyEvent *event)
{
    if(QString::number(event->key()) == "16777220")
    {
        authorization();
    }
}

void gui_login_area::authorization()
{
    emit signal_login(this->login_line->text(), this->pw_line->text());
    this->setEnabled(false);
}

void gui_login_area::gui_transit()
{
    QObject::connect(this, SIGNAL(call_farm_list_form()), parent(), SLOT(call_farm_list_form()));
    emit this->call_farm_list_form();
}

void gui_login_area::registration()
{
    QObject::connect(this, SIGNAL(call_reg_form()), parent(), SLOT(call_reg_form()));
    emit this->call_reg_form();
}

void gui_login_area::access_checker(QString req, QString cmd)
{
    if(cmd == "login")
    {
        if(req == "yes")
        {
            emit signal_get_user_data(this->login_line->text());
        }
        else
        {
            this->setEnabled(true);
            this->pw_line->clear();
            this->resault->setStyleSheet("QLabel {color : red;}");
            this->resault->setText("Error");
            emit this->log->signal_write_to_logfile("Error authorization for " + this->login_line->text());
        }
    }
}

void gui_login_area::accept_json(user_data new_data)
{
    data = new_data;
    data.JSON_server_to_desktop_parcer();
    QObject::connect(this, SIGNAL(send_authorization_data_to_another_form(QString, QString, user_data)), parent(), SLOT(accept_authorization_data(QString, QString, user_data)));
    emit this->send_authorization_data_to_another_form(this->login_line->text(), this->pw_line->text(), data);
    this->gui_transit();
    emit this->log->signal_write_to_logfile("Successful authorization for " + this->login_line->text());
    this->log->quit();
}
