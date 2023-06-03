#ifndef THREAD_LOGGER_H
#define THREAD_LOGGER_H

#include "prog_logger.h"

#include <QThread>
#include <QObject>
#include <QDebug>

class thread_logger : public QThread
{
    Q_OBJECT
public:
    explicit thread_logger(QObject *parent = nullptr);

signals:
    void signal_write_to_logfile(QString data);

protected:
    void run() override;

private:

    prog_logger* log = nullptr;
};

#endif // THREAD_LOGGER_H
