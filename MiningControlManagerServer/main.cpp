#include <QCoreApplication>
#include "server_th.h"
//#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    server_th server;
    server.start();
    //server serv(48048);

    return a.exec();
}
