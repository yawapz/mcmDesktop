#include "thread_socket.h"

thread_socket::thread_socket(QObject *parent)
    : QThread{parent}
{
    soc = new QTcpSocket();
    QObject::connect(soc, SIGNAL(readyRead()), this, SLOT(slot_read_answer()), Qt::UniqueConnection);
    QObject::connect(soc, SIGNAL(connected()), this, SIGNAL(signal_soc_connected()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_disconnect()), this, SLOT(slot_disconnect()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_accept_host_data(QString,int)), this, SLOT(slot_accept_host_data(QString,int)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_login(QString,QString)), this, SLOT(slot_login(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_create_new_user(QString,QString)), this, SLOT(slot_create_new_user(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_create_new_worker(QString)), this, SLOT(slot_create_new_worker(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_delete_worker(QString)), this, SLOT(slot_delete_worker(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_get_user_data(QString)), this, SLOT(slot_get_user_data(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_change_user_data(QString, QString, QString, QString)), this, SLOT(slot_change_user_data(QString, QString, QString, QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_delete_user(QString, QString)), this, SLOT(slot_delete_user(QString, QString)), Qt::UniqueConnection);
}

thread_socket::~thread_socket()
{
    soc->waitForDisconnected(2000);
    soc->deleteLater();
}

void thread_socket::run()
{
    this->exec();
}

void thread_socket::slot_accept_host_data(QString h, int p)
{
    host = h;
    port = p;
    soc->connectToHost(h, p);
}

void thread_socket::slot_disconnect()
{
    soc->disconnectFromHost();
}

void thread_socket::slot_login(QString l, QString p)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "login";
    stream << command;
    stream << l;
    stream << p;

    soc->write(*barr);
    soc->flush();
    delete barr;
}

void thread_socket::slot_get_user_data(QString l)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "get_user_data";
    stream << command;
    stream << l;
    soc->write(*barr);
    soc->flush();
    delete barr;
}

void thread_socket::slot_create_new_worker(QString l)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "add_worker";
    stream << command;
    stream << l;

    soc->write(*barr);
    soc->flush();
    delete barr;
}

void thread_socket::slot_delete_worker(QString id)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "del_worker";
    stream << command;
    stream << id;

    soc->write(*barr);
    soc->flush();
    delete barr;
}

void thread_socket::slot_create_new_user(QString l, QString p)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "new_user";
    stream << command;
    stream << l;
    stream << p;

    soc->write(*barr);
    soc->flush();
    delete barr;
}

void thread_socket::slot_delete_user(QString l, QString p)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "del_user";
    stream << command;
    stream << l;
    stream << p;

    soc->write(*barr);
    soc->flush();
    delete barr;
}

void thread_socket::slot_change_user_data(QString l, QString p, QString nl, QString np)
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    command = "update_user_data";

    stream << command;
    stream << l;
    stream << p;
    stream << nl;
    stream << np;

    soc->write(*barr);
    soc->flush();
    delete barr;
}

void thread_socket::slot_read_answer()
{
    if(command == "get_user_data")
    {
        QByteArray barr = soc->readAll();
        QDataStream stream(&barr, QIODevice::ReadOnly);
        QJsonObject jsonObject;
        stream >> jsonObject;
        data.main_json_file = jsonObject;
        data.JSON_server_to_desktop_parcer();
        emit signal_send_user_data(data);
    }
    else
    {
        QString req = "no";
        QString cmd = "";
        QByteArray barr = soc->readAll();
        QDataStream stream(&barr, QIODevice::ReadOnly);
        stream >> req;
        stream >> cmd;
        emit signal_send_answer_resault(req, cmd);
    }
}
