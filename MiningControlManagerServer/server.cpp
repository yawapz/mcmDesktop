#include "server.h"

server::server(int port)
{
    this->DB = QSqlDatabase::addDatabase("QPSQL",  "main");
    DB.setHostName("***********your db host*************");
    DB.setDatabaseName("*****your db name*******");
    DB.setPort(5432);
    DB.setUserName("*****your db username******");
    DB.setPassword("********your user password****************");

    if(DB.open())
    {
        qDebug() << "\033[32m" << "The db has been connected!" << Qt::endl;
    }
    else
    {
        qDebug() <<"\033[31m" << "The db was not connected!" << Qt::endl;
    }

    this->listen(QHostAddress::AnyIPv4, port);
    this->port = port;

    QObject::connect(this, SIGNAL(newConnection()), this, SLOT(slot_new_connection()));
}

server::~server()
{
    if(!this->connections.empty())
        for(auto& client : this->connections)
            client->disconnect();   
}

void server::slot_new_connection()
{
    QTcpSocket* nextClient = this->nextPendingConnection();
    QObject::connect(nextClient, SIGNAL(readyRead()), this, SLOT(slot_routing()));
    QObject::connect(nextClient, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));
    this->connections.append(nextClient);
}

void server::slot_disconnected()
{
    QTcpSocket* client = (QTcpSocket*)sender();
    int index = this->connections.indexOf(client);
    this->connections.removeAt(index);
    client->deleteLater();
}

void server::slot_routing()
{
    t.start();
    QTcpSocket* client = (QTcpSocket*)sender();
    QDataStream stream(client->readAll());

    QString command = "";
    stream >> command;
    if(command == "inc_worker_data")
    {
        WORKER worker;
        stream >> worker;
        if(!worker.str_json.isEmpty() && (worker.ID.length() > 0) && worker.status)
        {
            QString format = "dd.MM.yyyy hh:mm:ss.z";
            qDebug() << QDateTime::currentDateTime().toString(format) << "accepted data from " + worker.ID << Qt::endl;

            QString query_str = "SELECT worker_id FROM \"WORKERS\" WHERE worker_id = \'" + worker.ID + "\';";
            QSqlQuery query(this->DB);
            if(!query.exec(query_str))
            {
                qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
            }
            else
            {
                query.first();
                if(query.value(0).toString() == worker.ID)
                {

                    {
    //                QString gpu_arr = "";
    //                for (int i = 0; i < worker.devices.size(); ++i)
    //                {
    //                    QString tmp = "";
    //                    tmp+= "(";
    //                    tmp += "\'" + worker.devices[i].name + "\', ";
    //                    tmp += "\'" + worker.devices[i].bus_id + "\', ";
    //                    tmp += "\'" + worker.devices[i].vendor + "\', ";
    //                    tmp += "\'" + worker.devices[i].total_memory + "\', ";
    //                    tmp += "\'" + worker.devices[i].VBIOS_version + "\', ";
    //                    tmp += "\'" + worker.devices[i].min_pl + "\', ";
    //                    tmp += "\'" + worker.devices[i].default_pl + "\', ";
    //                    tmp += "\'" + worker.devices[i].max_pl + "\', ";
    //                    tmp += QString::number(worker.devices[i].gpu_id) + ", ";
    //                    tmp += QString::number(worker.devices[i].fan_speed) + ", ";
    //                    tmp += QString::number(worker.devices[i].core_clock) + ", ";
    //                    tmp += QString::number(worker.devices[i].memory_clock) + ", ";
    //                    tmp += QString::number(worker.devices[i].power_usage) + ", ";
    //                    tmp += QString::number(worker.devices[i].temperature) + ", ";
    //                    tmp += QString::number(worker.devices[i].max_core_freq) + ", ";
    //                    tmp += QString::number(worker.devices[i].max_mem_freq) + ", ";
    //                    tmp += QString::number(worker.devices[i].speed) + ", ";
    //                    tmp += QString::number(worker.devices[i].speed2) + ", ";
    //                    tmp += QString::number(worker.devices[i].accepted_shares) + ", ";
    //                    tmp += QString::number(worker.devices[i].accepted_shares2) + ", ";
    //                    tmp += QString::number(worker.devices[i].rejected_shares) + ", ";
    //                    tmp += QString::number(worker.devices[i].rejected_shares2) + ", ";
    //                    tmp += QString::number(worker.devices[i].stale_shares) + ", ";
    //                    tmp += QString::number(worker.devices[i].stale_shares2) + ", ";
    //                    tmp += QString::number(worker.devices[i].invalid_shares) + ", ";
    //                    tmp += QString::number(worker.devices[i].invalid_shares2) + ", ";
    //                    tmp += QString::number(worker.devices[i].memory_temperature) + ", ";
    //                    tmp += QString::number(worker.devices[i].set_fan_speed) + ", ";
    //                    tmp += QString::number(worker.devices[i].set_core) + ", ";
    //                    tmp += QString::number(worker.devices[i].set_mem) + ", ";
    //                    if(i < worker.devices.size() - 1)
    //                    {
    //                        tmp += QString::number(worker.devices[i].set_pl);
    //                        tmp += ")::gpu, ";
    //                    }
    //                    else if(i == worker.devices.size() - 1)
    //                    {
    //                        tmp += QString::number(worker.devices[i].set_pl);
    //                        tmp += ")::gpu";
    //                    }
    //                    gpu_arr.push_back(tmp);
    //                }

    //                QString query_str2 = "INSERT INTO worker_" + worker.ID + ""
    //                " VALUES "
    //                "("
    //                        "ARRAY[" + gpu_arr + "], "
    //                        "" + QString::number(worker.startup) + ", "
    //                        "\'" + worker.LA1 + "\', "
    //                        "\'" + worker.LA5 + "\', "
    //                        "\'" + worker.LA15 + "\', "
    //                        "\'" + worker.core_version + "\', "
    //                        "\'" + worker.nvidia_version + "\', "
    //                        "\'" + worker.amd_version + "\', "
    //                        "\'" + worker.motherboard_data + "\', "
    //                        "\'" + worker.CPU_info + "\', "
    //                        "\'" + worker.CPU_temperature + "\', "
    //                        "\'" + worker.disk_model + "\', "
    //                        "\'" + worker.disk_size + "\', "
    //                        "\'" + worker.disk_free_space + "\', "
    //                        "\'" + worker.RAM_total + "\', "
    //                        "\'" + worker.RAM_used + "\', "
    //                        "\'" + worker.RAM_free + "\', "
    //                        "\'" + worker.MAC + "\', "
    //                        "\'" + worker.local_ip + "\', "
    //                        "\'" + worker.ext_ip + "\', "
    //                        "\'" + worker.miner + "\', "
    //                        "\'" + worker.algorithm + "\', "
    //                        "\'" + worker.algorithm2 + "\', "
    //                        "\'" + worker.server + "\', "
    //                        "\'" + worker.server2 + "\', "
    //                        "\'" + worker.user + "\', "
    //                        "\'" + worker.user2 + "\', "
    //                        "" + QString::number(worker.total_accepted_shares) + ", "
    //                        "" + QString::number(worker.total_accepted_shares2) + ", "
    //                        "" + QString::number(worker.total_invalid_shares) + ", "
    //                        "" + QString::number(worker.total_invalid_shares2) + ", "
    //                        "" + QString::number(worker.total_rejected_shares) + ", "
    //                        "" + QString::number(worker.total_rejected_shares2) + ", "
    //                        "" + QString::number(worker.total_stale_shares) + ", "
    //                        "" + QString::number(worker.total_stale_shares2) + ", "
    //                        "" + QString::number(worker.uptime) + ", "
    //                        "\'" + worker.name + "\', "
    //                        "\'" + worker.ID + "\', "
    //                        "" + QString::number(worker.electricity_cost, 'f', 2) + ", "
    //                        "\'" + worker.version + "\', "
    //                        "" + "true" + ", "
    //                        "" + QString::number(worker.last_online) + ", "
    //                        "current_timestamp"
    //                ");";
                    }
                    QString query_str2 = "INSERT INTO \"worker_" + worker.ID + "\""
                    " (id, startup, status, last_online, inc_timestamp, json) VALUES "
                    "("
                            "\'" + worker.ID + "\', "
                            "" + QString::number(worker.startup) + ", "
                            "" + "true" + ", "
                            "" + QString::number(worker.last_online) + ", "
                            "current_timestamp, "
                            "\'" + worker.str_json + "\'"
                    ");";
                    if(!query.exec(query_str2))
                    {
                        qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                        qDebug() << query.lastQuery();
                    }
                }
            }
        }
    }
    else if(command == "get_user_data")
    {
        // Найти все воркеры юзера
        QString user_login = "";
        stream >> user_login;
        // Найти все воркеры юзера
        QString query_fnd_workers = "SELECT worker_id FROM \"WORKERS\" WHERE login = \'" + user_login + "\';";

        QByteArray barr;
        QDataStream req_stream(&barr, QIODevice::Append);

        QSqlQuery query(this->DB);
        if(!query.exec(query_fnd_workers))
        {
            qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
            qDebug() << query.lastQuery();
        }
        else
        {
            QList<WORKER> worker_list;
            QList<QString> worker_id_list;
            int field_number = query.record().indexOf("worker_id");
            while(query.next())
            {
                worker_id_list.append(query.value(field_number).toString());
            }
            // Сборка воркеров
            for (int i = 0; i < worker_id_list.size(); ++i)
            {
                QString worker_selector = "SELECT * FROM \"worker_" + worker_id_list[i] + "\""
                " ORDER BY inc_timestamp DESC LIMIT 1;";
                QSqlQuery worker_query(this->DB);
                if(!worker_query.exec(worker_selector))
                {
                    qDebug() << "Error Query - " << worker_query.lastError().type() << " - " << worker_query.lastError().text();
                    qDebug() << worker_query.lastQuery();
                }
                else
                {
                    WORKER worker;
                    if(worker_query.size() == 0)
                    {
                        worker.ID = worker_id_list[i];
                        worker.name = "<unknown>";
                        worker_list.push_back(worker);
                    }
                    else
                    {
                        // Вычленение параметров воркера
                        worker_query.first();
                        QSqlRecord worker_record = worker_query.record();
                        worker.ID = worker_query.value(worker_record.indexOf("id")).toString();
                        worker.last_online = worker_query.value(worker_record.indexOf("last_online")).toLongLong();
                        worker.status = worker_query.value(worker_record.indexOf("status")).toBool();
                        worker.startup = worker_query.value(worker_record.indexOf("startup")).toLongLong();
                        worker.str_json = worker_query.value(worker_record.indexOf("json")).toString();
                        worker.worker_json = QJsonDocument::fromJson(worker.str_json.toUtf8()).object();

                        if(!worker.status)
                        {
                            // Вкрутить параметры воркера (status, last_online)
                                // в Qt 5 нет нормальной замены значения
                            QJsonObject obj = worker.worker_json;
                            auto iterator = obj.find("status");
                            obj.erase(iterator);
                            obj.insert("status", false);
                            auto iterator2 = obj.find("last_online");
                            obj.erase(iterator2);
                            obj.insert("last_online", worker.last_online);

                            worker.worker_json = obj;
                        }
                        worker_list.push_back(worker);
                    }
                }
            }
            // Собрать данные всех воркеров юзера в JSON
            QJsonObject final_JSON_object;
            QJsonArray arr;
            for (int i = 0; i < worker_list.size(); ++i)
            {
                if(worker_list[i].worker_json.isEmpty())
                {
                    QJsonArray gpu_arr;
                    QJsonObject doc;
                    doc.insert("status", worker_list[i].status);
                    doc.insert("startup", worker_list[i].startup);
                    doc.insert("last_online", worker_list[i].last_online);
                    doc.insert("worker_name", worker_list[i].name);
                    doc.insert("ID", worker_list[i].ID);
                    doc.insert("devices",gpu_arr);
                    doc.insert("miner", worker_list[i].miner);
                    doc.insert("algorithm", worker_list[i].algorithm);
                    doc.insert("algorithm2", worker_list[i].algorithm2);
                    doc.insert("server", worker_list[i].server);
                    doc.insert("server2", worker_list[i].server2);
                    doc.insert("user", worker_list[i].user);
                    doc.insert("user2", worker_list[i].user2);
                    doc.insert("total_accepted_shares", worker_list[i].total_accepted_shares);
                    doc.insert("total_accepted_shares2", worker_list[i].total_accepted_shares2);
                    doc.insert("total_rejected_shares", worker_list[i].total_rejected_shares);
                    doc.insert("total_rejected_shares2", worker_list[i].total_rejected_shares);
                    doc.insert("total_invalid_shares", worker_list[i].total_invalid_shares);
                    doc.insert("total_invalid_shares2", worker_list[i].total_invalid_shares2);
                    doc.insert("total_stale_shares", worker_list[i].total_stale_shares);
                    doc.insert("total_stale_shares2", worker_list[i].total_stale_shares2);
                    doc.insert("uptime", worker_list[i].uptime);
                    doc.insert("local_ip", worker_list[i].local_ip);
                    doc.insert("ext_ip", worker_list[i].ext_ip);
                    doc.insert("LA1", worker_list[i].LA1);
                    doc.insert("LA5", worker_list[i].LA5);
                    doc.insert("LA15", worker_list[i].LA15);
                    doc.insert("electricity_cost", worker_list[i].electricity_cost);
                    doc.insert("core_version", worker_list[i].core_version);
                    doc.insert("nvidia_version", worker_list[i].nvidia_version);
                    doc.insert("amd_version", worker_list[i].amd_version);
                    doc.insert("motherboard_data", worker_list[i].motherboard_data);
                    doc.insert("CPU_info", worker_list[i].CPU_info);
                    doc.insert("CPU_temperature", worker_list[i].CPU_temperature);
                    doc.insert("disk_model", worker_list[i].disk_model);
                    doc.insert("disk_size", worker_list[i].disk_size);
                    doc.insert("disk_free_space", worker_list[i].disk_free_space);
                    doc.insert("RAM_total", worker_list[i].RAM_total);
                    doc.insert("RAM_used", worker_list[i].RAM_used);
                    doc.insert("RAM_free", worker_list[i].RAM_free);
                    doc.insert("MAC", worker_list[i].MAC);
                    doc.insert("version", worker_list[i].version);
                    arr.push_back(doc);
                }
                else
                {
                    arr.push_back(/*doc*/worker_list[i].worker_json);
                }
            }
            final_JSON_object.insert("rigs", arr);
            // Отправить данные клиенту
            req_stream << command;
            req_stream << final_JSON_object;
            client->write(barr);
            client->waitForConnected(1000);
        }
    }
    else if(command == "login")
    {
        QString user_login = "";
        QString user_password = "";
        stream >> user_login;
        stream >> user_password;

        QByteArray barr;
        QDataStream req_stream(&barr, QIODevice::Append);

        QString query_str1 = "SELECT login FROM \"USERS\" WHERE login = \'" + user_login + "\' AND password = "
        "\'" + user_password + "\';";
        QSqlQuery query(this->DB);
        if(!query.exec(query_str1))
        {
            qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
            qDebug() << query.lastQuery();
        }
        else
        {
            req_stream << command;
            if(query.size() > 0)
            {
                qDebug() << "\033[37m" << "successful authentication user " + user_login ;
                // ответ об успешной аунтификации
                req_stream << QString("yes");
            }
            else
            {
                // ответ отказ аунтификации
                req_stream << QString("no");

            }

            client->write(barr);
            client->waitForConnected(1000);
        }
    }
    else if(command == "new_user")
    {
        QString user_login = "";
        QString user_password = "";
        stream >> user_login;
        stream >> user_password;

        QByteArray barr;
        QDataStream req_stream(&barr, QIODevice::Append);

        QString query_str1 = "SELECT login FROM \"USERS\" WHERE login = \'" + user_login + "\';";
        QSqlQuery query(this->DB);
        if(!query.exec(query_str1))
        {
            qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
            qDebug() << query.lastQuery();
        }
        else
        {
            if(query.size() == 0)
            {
                req_stream << command;
                QString query_str2 = "INSERT INTO \"USERS\" (login, password) VALUES (\'" + user_login + "\', \'"
                "" + user_password + "\');";
                if(!query.exec(query_str2))
                {
                    qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                    qDebug() << query.lastQuery();
                    req_stream << QString("no");
                }
                else
                {
                    qDebug() << "new user " + user_login;
                    // Отправить ответ об успешном добавлении в БД
                    req_stream << QString("yes");
                }
                client->write(barr);
                client->waitForConnected(1000);
            }
            else
            {
                // Отправить ответ, что такой логин уже есть
                req_stream << command;
                req_stream << QString("busy");
                client->write(barr);
                client->waitForConnected(1000);
            }
        }
    }
    else if(command == "add_worker")
    {
        QString user_login = "";
        stream >> user_login;

        QString new_worker_id = "";
        bool res = false;
        QByteArray barr;
        QDataStream req_stream(&barr, QIODevice::Append);
        for (int var = 0; var < 50; ++var)
        {
            for (int i = 0; i < 8; ++i)
            {
                int choice = 1 + rand() % (4 - 1);
                if(choice == 1)
                {
                    new_worker_id.push_back((char)(48 + rand() % (57 - 48)));
                }
                else if(choice == 2)
                {
                    new_worker_id.push_back((char)65 + rand() % (90 - 65));
                }
                else if(choice == 3)
                {
                    new_worker_id.push_back((char)97 + rand() % (122 - 97));
                }
            }
            // Проверка на совпадение
            QString query_str1 = "SELECT worker_id FROM \"WORKERS\" WHERE worker_id = \'" + new_worker_id + "\';";
            QSqlQuery query(this->DB);
            if(!query.exec(query_str1))
            {
                qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                qDebug() << query.lastQuery();
            }
            else
            {
                res = true;
                if(query.size() == 0)
                {
                    // добавление
                    QString query_add = "INSERT INTO \"WORKERS\" (login, worker_id) VALUES"
                                        "(\'" + user_login + "\', \'" + new_worker_id + "\');";
                    if(!query.exec(query_add))
                    {
                        qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                        qDebug() << query.lastQuery();
                        // ответ об отказе добавлении
                        req_stream << command;
                        req_stream << QString("no");
                        client->write(barr);
                        client->waitForConnected(1000);
                        break;
                    }
                    else
                    {
                        // создание таблицы воркера

                        {
//                        QString query_create_worker_table = "CREATE TABLE \"worker_" + new_worker_id + "\""
//                        "(" +
//                        "devices gpu[], "
//                        "startup bigserial, "
//                        "LA1 text, "
//                        "LA5 text, "
//                        "LA15 text, "
//                        "core_version text, "
//                        "nvidia_version text, "
//                        "amd_version text, "
//                        "motherboard_data text, "
//                        "CPU_info text, "
//                        "CPU_temperature text, "
//                        "disk_model text, "
//                        "disk_size text, "
//                        "disk_free_space text, "
//                        "RAM_total text, "
//                        "RAM_used text, "
//                        "RAM_free text, "
//                        "MAC text, "
//                        "local_ip text, "
//                        "ext_ip text, "
//                        "miner text, "
//                        "algorithm text, "
//                        "algorithm2 text, "
//                        "server text, "
//                        "server2 text, "
//                        "user_address text, "
//                        "user2_address text, "
//                        "total_accepted_shares integer, "
//                        "total_accepted_shares2 integer, "
//                        "total_invalid_shares integer, "
//                        "total_invalid_shares2 integer, "
//                        "total_rejected_shares integer, "
//                        "total_rejected_shares2 integer, "
//                        "total_stale_shares integer, "
//                        "total_stale_shares2 integer, "
//                        "uptime bigserial, "
//                        "name text, "
//                        "ID text, "
//                        "electricity_cost real, "
//                        "version text, "
//                        "status boolean, "
//                        "last_online bigserial, "
//                        "inc_timestamp timestamp without time zone, "
//                        "FOREIGN KEY (ID) "
//                        "REFERENCES \"WORKERS\" (worker_id) "
//                        "ON DELETE CASCADE "
//                        "ON UPDATE CASCADE"
//                        ");";
                        }
                        QString query_create_worker_table = "CREATE TABLE \"worker_" + new_worker_id + "\""
                        "(" +
                        "id text, "
                        "startup bigserial, "
                        "status boolean, "
                        "last_online bigserial, "
                        "inc_timestamp timestamp without time zone, "
                        "json text, "
                        "FOREIGN KEY (ID) "
                        "REFERENCES \"WORKERS\" (worker_id) "
                        "ON DELETE CASCADE "
                        "ON UPDATE CASCADE"
                        ");";
                        if(!query.exec(query_create_worker_table))
                        {
                            qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                            qDebug() << query.lastQuery();
                            // ответ об отказе добавлении
                            req_stream << command;
                            req_stream << QString("no");
                            client->write(barr);
                            client->waitForConnected(1000);
                            break;
                        }
                        else
                        {
                            qDebug() << "new worker " + new_worker_id;
                            // ответ об успешном добавлении
                            req_stream << command;
                            req_stream << QString("yes");
                            client->write(barr);
                            client->waitForConnected(1000);
                            break;
                        }
                    }
                }
                else
                {
                    new_worker_id.clear();
                }
            }
        }
        if(!res)
        {
            // ответ об отказе добавлении
            req_stream << command;
            req_stream << QString("no");
            client->write(barr);
            client->waitForConnected(1000);
        }
    }
    else if(command == "del_worker")
    {
        QString worker_id = "";
        stream >> worker_id;
        // Удалить запись из таблицы
        QString query_record_del = "DELETE FROM \"WORKERS\" WHERE worker_id = \'" + worker_id + "\';";

        QByteArray barr;
        QDataStream req_stream(&barr, QIODevice::Append);

        QSqlQuery query(this->DB);
        if(!query.exec(query_record_del))
        {
            qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
            qDebug() << query.lastQuery();
            // Отказ
            req_stream << command;
            req_stream << QString("no");
            client->write(barr);
            client->waitForConnected(1000);
        }
        else
        {
            // Удалить таблицу воркера
            QString query_drop_worker_table = "DROP TABLE \"worker_" + worker_id +"\";";
            if(!query.exec(query_drop_worker_table))
            {
                qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                qDebug() << query.lastQuery();
                // Отказ
                req_stream << command;
                req_stream << QString("no");
                client->write(barr);
                client->waitForConnected(1000);
            }
            else
            {
                qDebug() << "Worker " + worker_id + " deleted!";
                // Отправка положительного результата
                req_stream << command;
                req_stream << QString("yes");
                client->write(barr);
                client->waitForConnected(1000);
            }
        }
    }
    else if(command == "del_user")
    {
        QString user_login = "";
        QString user_password = "";
        stream >> user_login;
        stream >> user_password;
        QByteArray barr;
        QDataStream req_stream(&barr, QIODevice::Append);

        QSqlQuery query(this->DB);
        // Есть ли такой юзер?
        QString query_fnd_user = " SELECT login FROM \"USERS\" WHERE login = \'" + user_login + "\' AND password = \'" + user_password + "\';";
        if(!query.exec(query_fnd_user))
        {
            qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
            qDebug() << query.lastQuery();
            // Ответ отказ
            req_stream << command;
            req_stream << QString("no");
            client->write(barr);
            client->waitForConnected(1000);
        }
        else if(query.size() == 0)
        {
            req_stream << command;
            req_stream << QString("no");
            client->write(barr);
            client->waitForConnected(1000);
        }
        else
        {
            // Найти все воркеры юзера
            QString query_fnd_workers = "SELECT worker_id FROM \"WORKERS\" WHERE login = \'" + user_login + "\';";
            if(!query.exec(query_fnd_workers))
            {
                qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                qDebug() << query.lastQuery();
                // Ответ отказ
                req_stream << command;
                req_stream << QString("no");
                client->write(barr);
                client->waitForConnected(1000);
            }
            else
            {
                bool result = false;
                if(query.size() > 0)
                {
                    // Удалить все таблицы воркеров
                    QList<QString> query_request_fields;
                    QSqlRecord rec = query.record();

                    for(int i = 0 ;i < rec.count(); ++i)
                    {
                        QString name = rec.fieldName(i);
                        query_request_fields.append(name);

                        int field_number = rec.indexOf(name);
                        while(query.next())
                        {
                            QString query_drop_worker_table = "DROP TABLE \"worker_" + query.value(field_number).toString() +"\";";
                            QSqlQuery del_query(this->DB);
                            if(!del_query.exec(query_drop_worker_table))
                            {
                                qDebug() << "Error Query - " << del_query.lastError().type() << " - " << del_query.lastError().text();
                                qDebug() << del_query.lastQuery();
                                result = false;
                            }
                            else
                            {
                                result = true;
                            }
                        }
                    }
                    if(result)
                    {
                        // Удалить воркеры
                        QString query_record_del1 = "DELETE FROM \"WORKERS\" WHERE login = \'" + user_login + "\';";
                        if(!query.exec(query_record_del1))
                        {
                            qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                            qDebug() << query.lastQuery();
                        }
                        else
                        {
                            // Удалить юзера
                            QString query_record_del2 = "DELETE FROM \"USERS\" WHERE login = \'" + user_login + "\';";
                            if(!query.exec(query_record_del2))
                            {
                                qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                                qDebug() << query.lastQuery();
                            }
                            else
                            {
                                qDebug() << "The user " + user_login + " has been deleted!";
                                req_stream << command;
                                req_stream << QString("yes");
                                client->write(barr);
                                client->waitForConnected(1000);
                            }
                        }
                    }
                    else
                    {
                        req_stream << command;
                        req_stream << QString("no");
                        client->write(barr);
                        client->waitForConnected(1000);
                    }
                }
                else
                {
                    // Удалить юзера
                    QString query_record_del2 = "DELETE FROM \"USERS\" WHERE login = \'" + user_login + "\';";
                    if(!query.exec(query_record_del2))
                    {
                        qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                        qDebug() << query.lastQuery();
                    }
                    else
                    {
                        qDebug() << "The user " + user_login + " has been deleted!";
                        req_stream << command;
                        req_stream << QString("yes");
                        client->write(barr);
                        client->waitForConnected(1000);
                    }
                }
            }
        }
    }
    else if(command == "update_user_data")
    {
        QString old_login = "";
        QString old_password = "";
        QString new_login = "";
        QString new_password = "";
        stream >> old_login;
        stream >> old_password;
        stream >> new_login;
        stream >> new_password;

        QByteArray barr;
        QDataStream req_stream(&barr, QIODevice::Append);

        QSqlQuery query(this->DB);
        QString query_fnd_user = "SELECT login FROM \"USERS\" WHERE login = \'" + old_login + "\';";

        if(!query.exec(query_fnd_user))
        {
            qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
            qDebug() << query.lastQuery();
            // ответ об отменённой операции
            req_stream << command;
            req_stream << QString("no");
            client->write(barr);
            client->waitForConnected(1000);
        }
        else
        {
            if(query.size() > 0)
            {
                QString query_update1 = "UPDATE \"USERS\" SET login = \'" + new_login + "\', password = \'" + new_password + "\'"
                " WHERE  login = \'" + old_login + "\';";
                QString query_update2 = "UPDATE \"WORKERS\" SET login \'" + new_login + "\' WHERE  login = \'" + old_login + "\';";
                if(!query.exec(query_update1))
                {
                    qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                    qDebug() << query.lastQuery();
                    // ответ об отменённой операции
                    req_stream << command;
                    req_stream << QString("no");
                    client->write(barr);
                    client->waitForConnected(1000);
                }
                else
                {
                    QString query_fnd_workers = "SELECT login FROM \"WORKERS\" WHERE login = \'" + old_login + "\';";
                    if(!query.exec(query_fnd_workers))
                    {
                        QString query_update_def = "UPDATE \"USERS\" SET login = \'" + old_login + "\', password = \'" + old_password + "\'"
                        " WHERE  login = \'" + new_login + "\';";
                        query.exec(query_update_def);
                        qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                        qDebug() << query.lastQuery();
                        // ответ об отменённой операции
                        req_stream << command;
                        req_stream << QString("no");
                        client->write(barr);
                        client->waitForConnected(1000);
                    }
                    else
                    {
                        if(query.size() > 0)
                        {
                            if(!query.exec(query_update2))
                            {
                                QString query_update_def = "UPDATE \"USERS\" SET login \' = " + old_login + "\', password = \'" + old_password + "\'"
                                " WHERE  login = \'" + new_login + "\';";
                                query.exec(query_update_def);
                                qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                                qDebug() << query.lastQuery();
                                // ответ об отменённой операции
                                req_stream << command;
                                req_stream << QString("no");
                                client->write(barr);
                                client->waitForConnected(1000);
                            }
                            else
                            {
                                qDebug() << "successful update data for user " + new_login ;
                                // ответ об успешной операции
                                req_stream << command;
                                req_stream << QString("yes");
                                client->write(barr);
                                client->waitForConnected(1000);
                            }
                        }
                        else
                        {
                            qDebug() << "successful update data for user " + new_login ;
                            // ответ об успешной операции
                            req_stream << command;
                            req_stream << QString("yes");
                            client->write(barr);
                            client->waitForConnected(1000);
                        }
                    }
                }
            }
            else
            {
                // ответ об отменённой операции
                req_stream << command;
                req_stream << QString("no");
                client->write(barr);
                client->waitForConnected(1000);
            }
        }
    }


    qDebug() << "\033[37m" << command << t.elapsed() << " msec " << client->peerAddress().toString()
                + ":" + QString::number(client->peerPort());
}
