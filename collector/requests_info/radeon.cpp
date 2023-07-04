#include "radeon.h"
#include "qdebug.h"

radeon::radeon()
{
    try
    {
        this->request = "apt list --installed | grep -i amdgpu-pro-core | gawk '{print $2}'";
        QString str = this->linux_terminal(this->request);
        if(this->info.isEmpty())
            this->info = "n/a";
        else
        {
            std::string version = str.toStdString();
            int del_index = version.find('\n');
            if(del_index != -1)
                version.erase(del_index);
            this->info = QString::fromStdString(version);
        }
    }
    catch (std::exception ex)
    {
        qDebug() << "radeon module - " << ex.what();
    }
}

QString radeon::get_version_info()
{
    return this->info;
}

QString radeon::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
