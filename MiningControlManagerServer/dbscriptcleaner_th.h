#ifndef DBSCRIPTCLEANER_TH_H
#define DBSCRIPTCLEANER_TH_H

#include "dbscriptcleaner.h"
#include <QThread>
#include <QObject>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QStringList>
#include <QTimer>

class DbScriptCleaner_th : public QThread
{
    Q_OBJECT
public:
    explicit DbScriptCleaner_th(QObject *parent = nullptr);
    void run() override;
private:
    QSqlDatabase DB;
private slots:
    void slot_accept_db(QSqlDatabase);
signals:
    void signal_accept_db(QSqlDatabase);
    void signal_send_db(QSqlDatabase);
};

#endif // DBSCRIPTCLEANER_TH_H
