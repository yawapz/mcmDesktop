#include "mac.h"

mac::mac()
{
    this->request = "ip link show | grep \"UP mode\" -A 1 | grep ether | gawk '{print $2}'";

    std::string result_mac = this->linux_terminal(this->request).toStdString();
    result_mac.erase(result_mac.find('\n'));

    this->info = QString::fromStdString(result_mac);
}

QString mac::get_info()
{
    return this->info;
}

QString mac::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
