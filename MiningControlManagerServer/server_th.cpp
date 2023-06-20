#include "server_th.h"

server_th::server_th(QObject *parent)
    : QThread{parent}
{
}

void server_th::run()
{
    server serv(48048);
    this->exec();
}
