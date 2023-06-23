#include "load_average.h"
#include "qdebug.h"

load_average::load_average()
{
    this->request1 = "cat /proc/loadavg | gawk '{print $1}'";
    this->la1 = linux_terminal(this->request1);

    this->request2 = "cat /proc/loadavg | gawk '{print $2}'";
    this->la5 = linux_terminal(this->request2);

    this->request3 = "cat /proc/loadavg | gawk '{print $3}'";
    this->la15 = linux_terminal(this->request3);
}

QString load_average::get_la1()
{
    return this->la1;
}

QString load_average::get_la5()
{
    return this->la5;
}

QString load_average::get_la15()
{
    return this->la15;
}

QString load_average::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
