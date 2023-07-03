#include "dbscriptcleaner.h"

DbScriptCleaner::DbScriptCleaner(QObject *parent)
    : QObject{parent}
{
    this->DB = QSqlDatabase::addDatabase("QPSQL", "cleaner");
    DB.setHostName("***********************");
    DB.setDatabaseName("************");
    DB.setPort(5432);
    DB.setUserName("************************");
    DB.setPassword("****************************************");

    if(DB.open())
    {
        qDebug() << "\033[32m" << "The cleaner has been connected!" << Qt::endl;
    }
    else
    {
        qDebug() << "\033[31m" << "The cleaner was not connected!" << Qt::endl;
    }
    inProcess = false;
    QObject::connect(this, SIGNAL(signal_go()), this, SLOT(slot_go()));
}

DbScriptCleaner::~DbScriptCleaner()
{
}

void DbScriptCleaner::slot_go()
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
            qDebug() << "\033[31m" << "db_cleaner finished with errors" << t.elapsed() << " msec";
        }
        else
        {
            // Для каждого воркера
            QList<QString> query_request_fields;
            QSqlRecord rec = query_workers.record();

            for(int i = 0 ;i < rec.count(); ++i)
            {
                QString name = rec.fieldName(i);
                query_request_fields.append(name);

                int field_number = rec.indexOf(name);
                while(query_workers.next())
                {
                    QString query_string = "DELETE FROM \"worker_" + query_workers.value(field_number).toString() + "\""
                                           " WHERE now() - inc_timestamp > interval '1 day';";
                    QSqlQuery query(this->DB);
                    if(!query.exec(query_string))
                    {
                        qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                        qDebug() << query.lastQuery();
                    }
                }
            }
            qDebug() << "\033[32m" << "db_cleaner finished " << t.elapsed() << " msec";
        }
        inProcess = false;
    }

}
