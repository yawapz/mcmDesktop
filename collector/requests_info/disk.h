#ifndef DISK_H
#define DISK_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class disk
{
public:
    disk();
    QString get_disk_name();
    QString get_disk_total();
    QString get_disk_used();
    QString get_disk_free();

private:
    QString request1;
    QString request2;
    QString request3;

    QString disk_name;
    QString disk_total;
    QString disk_used;
    QString disk_free;

    QString linux_terminal(QString &request);
};

#endif // DISK_H
