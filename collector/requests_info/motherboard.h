#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class motherboard
{
public:
    motherboard();
    QString get_info();

private:
    QString request1;
    QString request2;
    QString info;
    QString linux_terminal(QString &request);

};

#endif // MOTHERBOARD_H
