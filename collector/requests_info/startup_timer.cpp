#include "startup_timer.h"

startup_timer::startup_timer()
{
    this->request = "awk '{print int($1)}' /proc/uptime";

    this->start_up_seconds = linux_terminal(this->request).toLongLong();
}

long long startup_timer::get_timer_seconds()
{
    return this->start_up_seconds;
}

QString startup_timer::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
