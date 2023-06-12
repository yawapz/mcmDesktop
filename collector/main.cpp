#include <QCoreApplication>
#include <QTimer>
#include "worker_data_builder.h"
#include "config.h"
#include "config_struct.cpp"
#include "data_builder_th.h"
#include "socket_th.h"

#include "socket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //socket_th *s = new socket_th();
    //s->run();
    socket *soc = new socket();

    data_builder_th *b = new data_builder_th();
    //QObject::connect(b, SIGNAL(signal_send_worker_data(WORKER)), s, SIGNAL(signal_send_worker_data(WORKER)));
    QObject::connect(b, SIGNAL(signal_send_worker_data(WORKER)), soc, SIGNAL(signal_new_worker_data(WORKER)));
    //b->run();

    QTimer *timer = new QTimer();
    timer->setInterval(2*1000); // 2 sec
    QObject::connect(timer, SIGNAL(timeout()), b, SLOT(run()));
    QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(start()));
    timer->start();

    a.exec();
    b->quit();
    b->wait();
    //s->quit();
    //s->wait();
    delete b;
    //delete s;

    //qDebug() << conf.get_conf().version;

    //return a.exec();
}
