#ifndef KERNEL_H
#define KERNEL_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class kernel
{
public:
    kernel();
    QString get_info();

private:
    QString request;
    QString info;
    QString linux_terminal(QString &request);
};

#endif // KERNEL_H
