#include "prog_logger.h"

prog_logger::prog_logger()
{
    this->log_file = new QFile("log/log.txt");

    if(!this->log_file->open(QFile::Append))
    {
        this->log_file->open(QFile::WriteOnly);
    }
    this->log_stream = new QTextStream(this->log_file);

    QObject::connect(this, SIGNAL(signal_write_to_logfile     (QString)),
                     this, SLOT  (slot_write_to_logfile       (QString)));
}

void prog_logger::slot_write_to_logfile(QString data)
{
    QString format = "dd.MM.yyyy HH:mm:ss";
    *(this->log_stream) << QDateTime::currentDateTime().toString(format) + " " << data << Qt::endl;
    this->log_stream->flush();
}
