#ifndef THREAD_SOCKET_H
#define THREAD_SOCKET_H

#include "user_data.h"
#include "socket.h"

#include <QThread>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QDataStream>

class thread_socket : public QThread
{
    Q_OBJECT
public:
    explicit thread_socket(QObject *parent = nullptr);
    ~thread_socket();

private:
    void run() override;
signals:
    void signal_accept_host_data(QString, int);
    void signal_login(QString, QString);
    void signal_create_new_user(QString, QString);
    void signal_create_new_worker(QString);
    void signal_delete_worker(QString);
    void signal_get_user_data(QString);
    void signal_change_user_data(QString, QString, QString, QString);
    void signal_delete_user(QString, QString);

    void signal_send_answer_resault(QString, QString);
    void signal_send_user_data(user_data);
    void signal_soc_connected();
    void signal_disconnect();
};

#endif // THREAD_SOCKET_H
