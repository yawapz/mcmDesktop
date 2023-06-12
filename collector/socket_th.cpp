#include "socket_th.h"

socket_th::socket_th(QObject *parent)
    : QThread{parent}
{

}

void socket_th::run()
{
    socket *soc = new socket();
    QObject::connect(this, SIGNAL(signal_send_worker_data(WORKER)), soc, SIGNAL(signal_new_worker_data(WORKER)));
    this->exec();
    delete soc;
}
