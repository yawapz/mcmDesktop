#ifndef SOCKET_H
#define SOCKET_H

#include "user_data.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QObject>
#include <QTimer>

Q_DECLARE_METATYPE(user_data)

class socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit socket(QObject *parent = nullptr);
    ~socket();
private:
    QString host;
    int port;

    QString command;
    user_data data;
    QTimer timer;

private slots:
    void slot_accept_host_data(QString, int);
    void slot_disconnect();
    void slot_read_answer();

    void slot_login(QString, QString);
    void slot_get_user_data(QString);
    void slot_create_new_worker(QString);
    void slot_delete_worker(QString);
    void slot_create_new_user(QString, QString);
    void slot_delete_user(QString, QString);
    void slot_change_user_data(QString, QString, QString, QString);
    void slot_check_connection();
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
    //void signal_soc_connected();
    void signal_disconnect();
};

#endif // SOCKET_H
