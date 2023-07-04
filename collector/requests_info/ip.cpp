#include "ip.h"
#include "qdebug.h"

ip::ip()
{
    try
    {
        this->request1 = "hostname -I";
        this->local_ip = linux_terminal(this->request1);
        std::string local = this->local_ip.toStdString();
        local.erase(local.find(' '));
        this->local_ip = QString::fromStdString(local);

        this->request2 = "curl https://ipinfo.io/ip";
        this->external_ip = linux_terminal(this->request2);
    }
    catch (std::exception ex)
    {
        qDebug() << "ip module - " << ex.what();
    }
}

QString ip::get_local_ip()
{
    return this->local_ip;
}

QString ip::get_external_ip()
{
    return this->external_ip;
}

QString ip::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
