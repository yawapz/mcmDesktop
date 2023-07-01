#ifndef DBSCRIPTCLEANER_H
#define DBSCRIPTCLEANER_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QStringList>
#include <QElapsedTimer>

class DbScriptCleaner : public QObject
{
    Q_OBJECT
public:
    DbScriptCleaner(QObject *parent = nullptr);
    ~DbScriptCleaner();

private:
    QSqlDatabase DB;
    bool inProcess;

private slots:
    void slot_go();
signals:
    void signal_go();
};

#endif // DBSCRIPTCLEANER_H
