#include "dbscriptinspector.h"

DbScriptInspector::DbScriptInspector(QObject *parent)
    : QObject{parent}
{
    this->DB = QSqlDatabase::addDatabase("QPSQL", "inspector");
    DB.setHostName("***********your db host*************");
    DB.setDatabaseName("*****your db name*******");
    DB.setPort(5432);
    DB.setUserName("*****your db username******");
    DB.setPassword("********your user password****************");

    if(DB.open())
    {
        qDebug() << "\033[32m" << "The inspector has been connected!" << Qt::endl;
    }
    else
    {
        qDebug() << "\033[31m" << "The inspector was not connected!" << Qt::endl;
    }
    inProcess = false;
    QObject::connect(this, SIGNAL(signal_go()), this, SLOT(slot_go()));
}

DbScriptInspector::~DbScriptInspector()
{

}

void DbScriptInspector::slot_go()
{
    QElapsedTimer t;
    t.start();
    if(!inProcess)
    {
        inProcess = true;
        // Найти всех воркеров
        QString query_workers_string = "SELECT worker_id FROM \"WORKERS\";";
        QSqlQuery query_workers(this->DB);
        if(!query_workers.exec(query_workers_string))
        {
            qDebug() << "Error Query - " << query_workers.lastError().type() << " - " << query_workers.lastError().text();
            qDebug() << query_workers.lastQuery();
            qDebug() << "\033[31m" << "db_inspector finished with errors" << t.elapsed() << " msec";
        }
        else
        {
            QList<QString> query_request_fields;
            QSqlRecord rec = query_workers.record();

            for(int i = 0 ;i < rec.count(); ++i)
            {
                QString name = rec.fieldName(i);
                query_request_fields.append(name);

                int field_number = rec.indexOf(name);
                while(query_workers.next())
                {
                    QString query_string = "UPDATE \"worker_" + query_workers.value(field_number).toString() + "\" "
                                           "SET status=false WHERE now()::timestamp - inc_timestamp > interval '1 minute';";
                    QSqlQuery query(this->DB);
                    if(!query.exec(query_string))
                    {
                        qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                        qDebug() << query.lastQuery();
                    }
                    else
                    {
                        QString query_string2 = "UPDATE \"worker_" + query_workers.value(field_number).toString() + "\" "
                                                "SET last_online=EXTRACT(EPOCH FROM (now()::timestamp - inc_timestamp)) "
                                                "WHERE now()::timestamp - inc_timestamp > interval '1 minute';";
                        QSqlQuery query2(this->DB);
                        if(!query2.exec(query_string2))
                        {
                            qDebug() << "Error Query - " << query2.lastError().type() << " - " << query2.lastError().text();
                            qDebug() << query2.lastQuery();
                        }
                    }
                }
            }
            qDebug() << "\033[32m" << "db_inspector finished " << t.elapsed() << " msec";
        }
        inProcess = false;
    }
}
