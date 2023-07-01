#include "server_th.h"

server_th::server_th(QObject *parent)
    : QThread{parent}
{
}

void server_th::run()
{
    server *serv = new server(48048);

    DbScriptCleaner_th *cleaner = new DbScriptCleaner_th();
    DbScriptInspector_th *inspector = new DbScriptInspector_th();

    cleaner->start();
    inspector->start();

    this->exec();
    cleaner->wait();
    inspector->wait();
    cleaner->quit();
    inspector->quit();

    delete serv;
    delete cleaner;
    delete inspector;
}
