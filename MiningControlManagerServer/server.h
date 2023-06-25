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

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QStringList>

class server : public QTcpServer
{
    Q_OBJECT
public:
    server(int port);
    ~server();

private:
    int port;
    QList<QTcpSocket*> connections;
    QSqlDatabase DB;
    QElapsedTimer t;

signals:
    //void incoming_new_worker_data(QDataStream&);
private slots:
    void slot_new_connection();
    void slot_disconnected();
    void slot_routing();
};

#endif // SERVER_H
