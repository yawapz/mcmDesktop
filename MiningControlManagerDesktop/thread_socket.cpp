#include "thread_socket.h"

thread_socket::thread_socket(QObject *parent)
    : QThread{parent}
{

}

thread_socket::~thread_socket()
{

}

void thread_socket::run()
{
    socket *soc = new socket();
    QObject::connect(soc, SIGNAL(signal_send_user_data(user_data)), this, SIGNAL(signal_send_user_data(user_data)), Qt::UniqueConnection);
    QObject::connect(soc, SIGNAL(signal_send_answer_resault(QString,QString)), this, SIGNAL(signal_send_answer_resault(QString,QString)), Qt::UniqueConnection);
    QObject::connect(soc, SIGNAL(connected()), this, SIGNAL(signal_soc_connected()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_disconnect()), soc, SIGNAL(signal_disconnect()), Qt::UniqueConnection);

    QObject::connect(this, SIGNAL(signal_accept_host_data(QString,int)), soc, SIGNAL(signal_accept_host_data(QString,int)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_login(QString,QString)), soc, SIGNAL(signal_login(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_create_new_user(QString,QString)), soc, SIGNAL(signal_create_new_user(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_create_new_worker(QString)), soc, SIGNAL(signal_create_new_worker(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_delete_worker(QString)), soc, SIGNAL(signal_delete_worker(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_get_user_data(QString)), soc, SIGNAL(signal_get_user_data(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_change_user_data(QString, QString, QString, QString)), soc, SIGNAL(signal_change_user_data(QString, QString, QString, QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_delete_user(QString, QString)), soc, SIGNAL(signal_delete_user(QString, QString)), Qt::UniqueConnection);

    this->exec();
    soc->deleteLater();
}
