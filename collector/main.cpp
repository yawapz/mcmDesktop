#include <QCoreApplication>
#include <QTimer>
#include "data_builder_th.h"
#include "socket_thread.h"
//#include "socket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    socket_thread *s = new socket_thread();
    data_builder_th *b = new data_builder_th();
    QObject::connect(b, SIGNAL(signal_send_worker_data(WORKER)), s, SIGNAL(signal_send_worker_data(WORKER)));
    s->start();
    b->start();
//    QTimer *timer = new QTimer();
//    timer->setInterval(2*1000); // 2 sec
//    QObject::connect(timer, SIGNAL(timeout()), b, SLOT(start()));
    //QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(start()));
//    timer->start();
    return a.exec();
}
