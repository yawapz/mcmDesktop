#ifndef SERVER_H
#define SERVER_H

#include "../collector/worker_struct.cpp"

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <QDate>
#include <QList>

class server : public QTcpServer
{
    Q_OBJECT
public:
    server(int port);
    ~server();

private:
    int port;
    QList<QTcpSocket*> connections;

signals:
    //void incoming_new_worker_data(QDataStream&);
private slots:
    void accept_new_worker_data();
    void slot_new_connection();
    void slot_disconnected();
};

#endif // SERVER_H
