#include "disk.h"
#include "qdebug.h"

disk::disk()
{
    this->request1 = "inxi -Dxx | grep ID-1";
    std::string disk_name = this->linux_terminal(this->request1).toStdString();
    while (disk_name.find("\u0003") != -1)
    {
        disk_name.erase(disk_name.find("\u0003"), 1);
    }

    int pos1 = disk_name.find("12vendor") + 9;
    disk_name.erase(0, pos1);

    int pos2 = disk_name.find("12model");
    disk_name.erase(pos2, pos2 + 8);

    int pos3 = disk_name.find("12size") - 1;
    disk_name.erase(pos3);

    this->disk_name = QString::fromStdString(disk_name);

    this->request2 = "df / -m | grep dev | gawk '{print $3}'";
    QString str_disk_used = this->linux_terminal(this->request2);
    if(str_disk_used.toInt() < 1024)
        this->disk_used = str_disk_used + " MiB";
    else
        this->disk_used = QString::number((str_disk_used.toDouble() / 1024), 'f', 2) + " GiB";

    this->request3 = "df / -m | grep dev | gawk '{print $4}'";
    QString str_disk_free = this->linux_terminal(this->request3);
    if(str_disk_free.toInt() < 1024)
        this->disk_free = QString::number(str_disk_free.toInt()) + " MiB";
    else
        this->disk_free = QString::number((str_disk_free.toInt() / 1024), 'f', 2) + " GiB";

    double total_space = str_disk_used.toInt() + str_disk_free.toInt();
    if(total_space < 1024)
        this->disk_total = QString::number(total_space, 'f', 2) + " MiB";
    else
        this->disk_total = QString::number((total_space / 1024), 'f', 2) + " GiB";
}

QString disk::get_disk_name()
{
    return this->disk_name;
}

QString disk::get_disk_total()
{
    return this->disk_total;
}

QString disk::get_disk_used()
{
    return this->disk_used;
}

QString disk::get_disk_free()
{
    return this->disk_free;
}

QString disk::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
