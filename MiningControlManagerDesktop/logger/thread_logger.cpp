#include "thread_logger.h"

thread_logger::thread_logger(QObject *parent)
    : QThread{parent}
{
}

void thread_logger::run()
{
    this->log = new prog_logger();
    QObject::connect(this , SIGNAL(signal_write_to_logfile(QString)),
                     log  , SIGNAL(signal_write_to_logfile(QString)));
    this->exec();
    delete log;
}
