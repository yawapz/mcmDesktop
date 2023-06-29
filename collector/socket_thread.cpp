#include "socket_thread.h"

socket_thread::socket_thread(QObject *parent)
    : QThread{parent}
{
}

socket_thread::~socket_thread()
{
}

void socket_thread::run()
{

    socket *soc = new socket();
    QObject::connect(this, SIGNAL(signal_send_worker_data(WORKER)), soc, SIGNAL(signal_new_worker_data(WORKER)));
    this->exec();
    soc->deleteLater();
}
