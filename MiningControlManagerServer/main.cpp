#include <QCoreApplication>
#include "server_th.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    server_th server;
    server.run();
    return a.exec();
}
