#include "thread_refresh_data.h"

thread_refresh_data::thread_refresh_data(QObject *parent)
    : QThread{parent}
{
    this->soc = new QTcpSocket();
    QObject::connect(this, SIGNAL(signal_accept_data(QString,QString,user_data)), this, SLOT(slot_accept_data(QString,QString,user_data)));
    QObject::connect(soc, SIGNAL(readyRead()), this, SLOT(slot_accept_json()));
}

thread_refresh_data::~thread_refresh_data()
{
    this->soc->deleteLater();
}

void thread_refresh_data::run()
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    QString command = "get_user_data";

    stream << command;
    stream << this->login;
    if(!soc->isOpen())
        soc->connectToHost("127.0.0.1", 48048);
    soc->waitForConnected(1000);
    soc->write(*barr);
    soc->flush();
    delete barr;
}

void thread_refresh_data::slot_accept_data(QString l, QString p, user_data d)
{
    this->login = l;
    this->password = p;
    this->data = d;
}

void thread_refresh_data::slot_accept_json()
{
    soc->waitForReadyRead(1000);
    QByteArray barr = soc->readAll();
    QDataStream stream(&barr, QIODevice::ReadOnly);
    QJsonObject jsonObject;
    stream >> jsonObject;
    soc->waitForDisconnected(1000);
    user_data inc_data;
    inc_data.main_json_file = jsonObject;
    inc_data.JSON_server_to_desktop_parcer();
    emit signal_send_new_data(inc_data);
}
