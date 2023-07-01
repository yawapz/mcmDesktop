#ifndef DBSCRIPTINSPECTOR_H
#define DBSCRIPTINSPECTOR_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QStringList>
#include <QElapsedTimer>

class DbScriptInspector : public QObject
{
    Q_OBJECT
public:
    explicit DbScriptInspector(QObject *parent = nullptr);
    ~DbScriptInspector();

private:
    QSqlDatabase DB;
    bool inProcess;
private slots:
    void slot_go();
signals:
    void signal_go();
};

#endif // DBSCRIPTINSPECTOR_H
