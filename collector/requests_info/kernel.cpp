#include "kernel.h"

kernel::kernel()
{
    this->request = "uname -r";
    std::string kernel = this->linux_terminal(this->request).toStdString();
    kernel.erase(kernel.find('\n'));

    this->info = QString::fromStdString(kernel);
}

QString kernel::get_info()
{
    return this->info;
}

QString kernel::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
