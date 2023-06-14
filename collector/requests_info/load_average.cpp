#include "load_average.h"
#include "qdebug.h"

load_average::load_average()
{
    this->request1 = "uptime | gawk '{print $8}'";
    this->la1 = linux_terminal(this->request1);
    this->la1.resize(this->la1.length() - 2);
    this->la1.replace(',', '.');

    this->request2 = "uptime | gawk '{print $9}'";
    this->la5 = linux_terminal(this->request2);
    this->la5.resize(this->la5.length() - 2);
    this->la5.replace(',', '.');

    this->request3 = "uptime | gawk '{print $10}'";
    this->la15 = linux_terminal(this->request3);
    this->la15.resize(this->la15.length() - 1);
    this->la15.replace(',', '.');
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
