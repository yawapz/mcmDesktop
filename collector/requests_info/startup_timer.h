#ifndef STARTUP_TIMER_H
#define STARTUP_TIMER_H

#include <QProcess>
#include <QString>
#include <QByteArray>
#include <string>
#include <algorithm>

class startup_timer
{
public:
    startup_timer();
    long long get_timer_seconds();

private:
    QString request;

    long long start_up_seconds;
    QString linux_terminal(QString &request);
};

#endif // STARTUP_TIMER_H
