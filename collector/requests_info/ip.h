#ifndef IP_H
#define IP_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class ip
{
public:
    ip();
    QString get_local_ip();
    QString get_external_ip();
private:
    QString request1;
    QString request2;
    QString local_ip;
    QString external_ip;
    QString linux_terminal(QString &request);
};

#endif // IP_H
