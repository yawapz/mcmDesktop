#ifndef SOCKET_TH_H
#define SOCKET_TH_H

#include <QThread>
#include <QObject>
#include "socket.h"
#include "config_struct.cpp"
#include "worker_struct.cpp"

class socket_th : public QThread
{
public:
    explicit socket_th(QObject *parent = nullptr);
public slots:
    void run() override;
signals:
    void signal_send_worker_data(WORKER);
};

#endif // SOCKET_TH_H
