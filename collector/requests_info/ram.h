#ifndef RAM_H
#define RAM_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class ram
{
public:
    ram();
    QString get_ram_total();
    QString get_ram_used();
    QString get_ram_free();

private:
    QString request;

    QString ram_total;
    QString ram_used;
    QString ram_free;

    QString linux_terminal(QString &request);
};

#endif // RAM_H
