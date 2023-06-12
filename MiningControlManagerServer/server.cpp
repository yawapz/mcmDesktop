#include "server.h"

server::server(int port)
{
    //this->listen(QHostAddress::AnyIPv4, port);
    this->listen(QHostAddress::LocalHost, port);
    this->port = port;

    QObject::connect(this, SIGNAL(newConnection()), this, SLOT(slot_new_connection()));
}

server::~server()
{
    if(!this->connections.empty())
        for(auto& client : this->connections)
            client->disconnect();
}

void server::accept_new_worker_data()
{   
    QTcpSocket* client = (QTcpSocket*)sender();
    QDataStream stream(client->readAll());

    WORKER worker;
    stream >> worker;
    qDebug() << QDate::currentDate().toString() + " accepted data from " + worker.ID;
    // отправка в бд

    client->disconnect();
}

void server::slot_new_connection()
{
    QTcpSocket* nextClient = this->nextPendingConnection();

    QObject::connect(nextClient, SIGNAL(readyRead()), this, SLOT(accept_new_worker_data()));
    QObject::connect(nextClient, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));

    this->connections.append(nextClient);
}

void server::slot_disconnected()
{
    QTcpSocket* client = (QTcpSocket*)sender();
    int index = this->connections.indexOf(client);
    this->connections.removeAt(index);
    client->deleteLater();
}
