#include "nvidia.h"

nvidia::nvidia()
{
    this->request = "nvidia-smi | grep Version | gawk '{print $6}'";
    std::string version = this->linux_terminal(this->request).toStdString();
    version.erase(version.find('\n'));

    this->info = QString::fromStdString(version);
}

QString nvidia::get_version_info()
{
    return this->info;
}

QString nvidia::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
