#ifndef CPU_H
#define CPU_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class cpu
{
public:
    cpu();
    QString get_info();
    QString get_temperature();
private:
    QString request1;
    QString request2;
    QString name;
    QString temperature;
    QString linux_terminal(QString &request);
};

#endif // CPU_H
