#include "socket.h"

socket::socket(QObject *parent)
    : QTcpSocket{parent}
{
    timer.setInterval(5*1000); // 5 sec
    qRegisterMetaType<user_data>();
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(slot_read_answer()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_disconnect()), this, SLOT(slot_disconnect()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_accept_host_data(QString,int)), this, SLOT(slot_accept_host_data(QString,int)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_login(QString,QString)), this, SLOT(slot_login(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_create_new_user(QString,QString)), this, SLOT(slot_create_new_user(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_create_new_worker(QString)), this, SLOT(slot_create_new_worker(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_delete_worker(QString)), this, SLOT(slot_delete_worker(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_get_user_data(QString)), this, SLOT(slot_get_user_data(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_change_user_data(QString, QString, QString, QString)), this, SLOT(slot_change_user_data(QString, QString, QString, QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_delete_user(QString, QString)), this, SLOT(slot_delete_user(QString, QString)), Qt::UniqueConnection);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(slot_check_connection()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(connected()), &timer, SLOT(start()));
}

socket::~socket()
{
    this->waitForDisconnected(2000);
    this->deleteLater();
}

void socket::slot_accept_host_data(QString h, int p)
{
    host = h;
    port = p;
    this->connectToHost(h, p);
}

void socket::slot_disconnect()
{
    this->disconnectFromHost();
}

void socket::slot_login(QString l, QString p)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "login";
    stream << command;
    stream << l;
    stream << p;

    this->write(*barr);
    this->flush();
    delete barr;
}

void socket::slot_get_user_data(QString l)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "get_user_data";
    stream << command;
    stream << l;
    this->write(*barr);
    this->flush();
    delete barr;
}

void socket::slot_create_new_worker(QString l)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "add_worker";
    stream << command;
    stream << l;

    this->write(*barr);
    this->flush();
    delete barr;
}

void socket::slot_delete_worker(QString id)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "del_worker";
    stream << command;
    stream << id;

    this->write(*barr);
    this->flush();
    delete barr;
}

void socket::slot_create_new_user(QString l, QString p)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "new_user";
    stream << command;
    stream << l;
    stream << p;

    this->write(*barr);
    this->flush();
    delete barr;
}

void socket::slot_delete_user(QString l, QString p)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "del_user";
    stream << command;
    stream << l;
    stream << p;

    this->write(*barr);
    this->flush();
    delete barr;
}

void socket::slot_change_user_data(QString l, QString p, QString nl, QString np)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "update_user_data";

    stream << command;
    stream << l;
    stream << p;
    stream << nl;
    stream << np;

    this->write(*barr);
    this->flush();
    delete barr;
}

void socket::slot_check_connection()
{
    if(this->state() != QAbstractSocket::ConnectedState)
        this->connectToHost(host, port);
}

void socket::slot_read_answer()
{
    QByteArray barr = this->readAll();
    QDataStream stream(&barr, QIODevice::ReadOnly);
    QString req = "no";
    QString cmd = "";
    stream >> cmd;

    if(cmd == "get_user_data")
    {
        QJsonObject jsonObject;
        stream >> jsonObject;
        data.main_json_file = jsonObject;
        data.JSON_server_to_desktop_parcer();
        emit signal_send_user_data(data);
    }
    else
    {
        stream >> req;
        if(cmd == "ping")
        {
            QByteArray *barr = new QByteArray();
            QDataStream stream(barr, QIODevice::Append);
            stream << "pong";
            this->write(*barr);
            this->flush();
            delete barr;
        }
        else
            emit signal_send_answer_resault(req, cmd);
    }
}
