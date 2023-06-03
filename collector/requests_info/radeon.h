#ifndef RADEON_H
#define RADEON_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class radeon
{
public:
    radeon();
    QString get_version_info();

private:
    QString request;
    QString info;
    QString linux_terminal(QString &request);
};

#endif // RADEON_H
