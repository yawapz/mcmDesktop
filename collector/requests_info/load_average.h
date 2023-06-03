#ifndef LOAD_AVERAGE_H
#define LOAD_AVERAGE_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class load_average
{
public:
    load_average();
    QString get_la1();
    QString get_la5();
    QString get_la15();

private:
    QString request1;
    QString request2;
    QString request3;
    QString la1;
    QString la5;
    QString la15;
    QString linux_terminal(QString &request);
};

#endif // LOAD_AVERAGE_H
