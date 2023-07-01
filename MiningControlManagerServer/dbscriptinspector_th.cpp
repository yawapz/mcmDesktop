#include "dbscriptinspector_th.h"

DbScriptInspector_th::DbScriptInspector_th(QObject *parent)
    : QThread{parent}
{
}

void DbScriptInspector_th::run()
{
    // запуск скрипта по таймеру
    DbScriptInspector script;
    QTimer t;
    QObject::connect(&t, SIGNAL(timeout()), &script, SIGNAL(signal_go()));

    t.start(1000*60); // 1 min
    //t.start(10*1000); // 10 sec for tests
    this->exec();
}
