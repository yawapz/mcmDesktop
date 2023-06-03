#ifndef MAC_H
#define MAC_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class mac
{
public:
    mac();
    QString get_info();

private:
    QString request;
    QString info;
    QString linux_terminal(QString &request);
};

#endif // MAC_H
