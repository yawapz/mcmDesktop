#ifndef PROG_LOGGER_H
#define PROG_LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

class prog_logger : public QObject
{
    Q_OBJECT
public:
    explicit prog_logger();

signals:
    void signal_write_to_logfile(QString data);

public slots:

    void slot_write_to_logfile(QString data);

private:

    QFile* log_file = nullptr;
    QTextStream* log_stream = nullptr;
};

#endif // PROG_LOGGER_H
