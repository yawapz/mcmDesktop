#ifndef DBSCRIPTINSPECTOR_TH_H
#define DBSCRIPTINSPECTOR_TH_H

#include "dbscriptinspector.h"

#include <QThread>
#include <QObject>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QStringList>
#include <QTimer>

class DbScriptInspector_th : public QThread
{
    Q_OBJECT
public:
    explicit DbScriptInspector_th(QObject *parent = nullptr);
    void run() override;
private:
private slots:
signals:
    void signal_go();
};

#endif // DBSCRIPTINSPECTOR_TH_H
