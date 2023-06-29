#include "data_builder_th.h"
#include "qtimer.h"

data_builder_th::data_builder_th(QObject *parent)
    : QThread{parent}
{
}

data_builder_th::~data_builder_th()
{
}

void data_builder_th::run()
{
    worker_data_builder *builder = new worker_data_builder();
    QObject::connect(builder, SIGNAL(signal_send_worker_data(WORKER)), this, SIGNAL(signal_send_worker_data(WORKER)));
    QObject::connect(this, SIGNAL(signal_get_new_data()), builder, SIGNAL(signal_get_new_data()));

    QTimer *timer = new QTimer();
    timer->setInterval(5*1000); // 5 sec
    QObject::connect(timer, SIGNAL(timeout()), builder, SIGNAL(signal_get_new_data()));
    timer->start();
    this->exec();
    builder->deleteLater();
}
