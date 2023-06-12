#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QObject>
#include "worker_struct.cpp"
#include "config.h"
#include "config_struct.cpp"

class socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit socket(QObject *parent = nullptr);

signals:
    void signal_new_worker_data(WORKER);

private slots:
    void slot_accept_worker_data(WORKER);

};

#endif // SOCKET_H
