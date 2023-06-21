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

        this->access = false;
        this->soc = new QTcpSocket();
        this->soc2 = new QTcpSocket();
        this->data = new user_data();
        QObject::connect(soc, SIGNAL(readyRead()), this, SLOT(access_checker()));
        QObject::connect(soc2, SIGNAL(readyRead()), this, SLOT(accept_json()));
}

gui_login_area::~gui_login_area()
{
    soc->deleteLater();
    soc2->deleteLater();
    log->deleteLater();
    data->deleteLater();
}

void gui_login_area::authorization()
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    QString command = "login";
    stream << command;

    QString user_login = this->login_line->text();
    QString user_password = this->pw_line->text();
    stream << user_login;
    stream << user_password;

    if(!soc->isOpen())
        soc->connectToHost("127.0.0.1", 48048);
    soc->waitForConnected(1000);
    soc->write(*barr);
    soc->flush();
    delete barr;

    this->setEnabled(false);

    QEventLoop *loop = new QEventLoop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, loop, &QEventLoop::quit);
    t.connect(soc, SIGNAL(readyRead()), loop, SLOT(quit()));
    t.start(5*1000); // 5 sec
    loop->exec();
    loop->deleteLater();

    if(this->access)
    {
        QByteArray *barr2 = new QByteArray();
        QDataStream stream(barr2, QIODevice::Append);
        QString command = "get_user_data";
        QString login = this->login_line->text();

        stream << command;
        stream << login;
        if(!soc2->isOpen())
            soc2->connectToHost("127.0.0.1", 48048);
        soc2->waitForConnected(1000);
        soc2->write(*barr2);
        soc2->flush();
        delete barr2;

        QEventLoop *loop2 = new QEventLoop;
        QTimer t2;
        t2.connect(&t2, &QTimer::timeout, loop2, &QEventLoop::quit);
        t2.connect(soc2, SIGNAL(readyRead()), loop2, SLOT(quit()));
        t2.start(5*1000); // 5 sec
        loop2->exec();
        loop2->deleteLater();
        // Перенос данных в следующее окно после успешной авторизации + возможно добавить ключ шифрования на сессию
        //data->JSON_from_local_directory_file();
        data->JSON_server_to_desktop_parcer();


        QObject::connect(this, SIGNAL(send_authorization_data_to_another_form(QString, QString, user_data)), parent(), SLOT(accept_authorization_data(QString, QString, user_data)));
        emit this->send_authorization_data_to_another_form(this->login_line->text(), this->pw_line->text(), *data);
        //--------------------------------------------------------------
        this->gui_transit();
        emit this->log->signal_write_to_logfile("Successful authorization for " + this->login_line->text());
    }
    else
    {
        this->setEnabled(true);
        this->pw_line->clear();
        this->resault->setStyleSheet("QLabel {color : red;}");
        this->resault->setText("Error");
        emit this->log->signal_write_to_logfile("Error authorization for " + this->login_line->text());
    }
    this->log->quit();
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

void gui_login_area::access_checker()
{
    soc->waitForReadyRead(1000);
    QString req = "no";

    QByteArray barr = soc->readAll();
    QDataStream stream(&barr, QIODevice::ReadOnly);
    stream >> req;

    if(req == "yes")
    {
        this->access = true;
    }
    else
    {
        this->access = false;
    }
    soc->waitForDisconnected(1000);
}

void gui_login_area::accept_json()
{
    soc2->waitForReadyRead(1000);
    QByteArray barr = soc2->readAll();
    QDataStream stream(&barr, QIODevice::ReadOnly);
    QJsonObject jsonObject;
    stream >> jsonObject;
    this->data->main_json_file = jsonObject;
    soc2->waitForDisconnected(1000);
}
