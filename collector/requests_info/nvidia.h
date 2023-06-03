#ifndef NVIDIA_H
#define NVIDIA_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class nvidia
{
public:
    nvidia();
    QString get_version_info();

private:
    QString request;
    QString info;
    QString linux_terminal(QString &request);
};

#endif // NVIDIA_H
