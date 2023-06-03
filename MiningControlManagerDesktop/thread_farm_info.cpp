#include "thread_farm_info.h"

thread_farm_info::thread_farm_info(QObject *parent)
    : QThread{parent}
{
}

void thread_farm_info::run()
{
    this->farm = new gui_farm_info_area();
    QObject::connect(this,        SIGNAL(signal_send_data(QString, QString, user_data)),
                     this->farm,  SIGNAL(signal_accept_data(QString, QString, user_data)));
    this->exec();
    delete farm;
}
