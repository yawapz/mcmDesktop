#include "dbscriptcleaner_th.h"

DbScriptCleaner_th::DbScriptCleaner_th(QObject *parent)
    : QThread{parent}
{
}

void DbScriptCleaner_th::run()
{
    // запуск скрипта по таймеру
    DbScriptCleaner script;
    QTimer t;
    QObject::connect(&t, SIGNAL(timeout()), &script, SIGNAL(signal_go()));

    t.start(60*1000*60); // 60 min
    //t.start(10*1000); // 10 sec for tests
    this->exec();
}

void DbScriptCleaner_th::slot_accept_db(QSqlDatabase inc_db)
{
    DB = inc_db;
}
