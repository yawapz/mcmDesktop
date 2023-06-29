#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include "socket.h"
#include "worker_struct.cpp"

class socket_thread : public QThread
{
    Q_OBJECT
public:
    explicit socket_thread(QObject *parent = nullptr);
    ~socket_thread();
private:

public slots:
    void run() override;
signals:
    void signal_send_worker_data(WORKER);
private slots:

};

#endif // SOCKET_THREAD_H
