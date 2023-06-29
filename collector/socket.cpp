#include "socket.h"

socket::socket(QObject *parent)
    : QTcpSocket{parent}
{
    qRegisterMetaType<WORKER>();
    conf = lconf.get_conf();
    this->connectToHost(conf.server_addr, conf.server_port);
    QObject::connect(this, SIGNAL(signal_new_worker_data(WORKER)), this, SLOT(slot_send_worker_data(WORKER)));
}

void socket::slot_send_worker_data(WORKER inc_worker)
{
    if(this->state() == QAbstractSocket::ConnectedState)
    {
        conf = lconf.get_conf();
        worker = inc_worker;
        worker.version = conf.version;
        worker.name = conf.name;
        worker.ID = conf.ID;
        worker.electricity_cost = conf.electricity_cost;
        worker.fill_JSON_object();
        //qDebug() << QJsonDocument::fromJson(worker.str_json.toUtf8());

        QByteArray *barr = new QByteArray();
        QDataStream stream(barr, QIODevice::Append);
        QString command = "inc_worker_data";
        stream << command;
        stream << worker;
        this->write(*barr);
        this->flush();
        delete barr;
    }
    else if (this->state() == QAbstractSocket::UnconnectedState)
    {
        this->connectToHost(conf.server_addr, conf.server_port);
    }
}
