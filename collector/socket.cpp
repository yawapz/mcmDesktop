#include "socket.h"

socket::socket(QObject *parent)
    : QTcpSocket{parent}
{
    QObject::connect(this, SIGNAL(signal_new_worker_data(WORKER)), this, SLOT(slot_send_worker_data(WORKER)));
}

void socket::slot_send_worker_data(WORKER inc_worker)
{
    config lconf;
    conf_data conf = lconf.get_conf();
    WORKER worker = inc_worker;
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

    this->connectToHost(conf.server_addr, conf.server_port);
    this->write(*barr);
    //this->flush();
    this->disconnectFromHost();

    delete barr;
}
