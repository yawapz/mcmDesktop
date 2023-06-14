#include "server.h"

server::server(int port)
{
    this->DB = QSqlDatabase::addDatabase("QPSQL");
    DB.setHostName("****************");
    DB.setDatabaseName("************");
    DB.setPort(5432);
    DB.setUserName("*************************");
    DB.setPassword("*********************************************");

    if(DB.open())
    {
        qDebug() << "DB connected!" << Qt::endl;
        // для тестов
        QStringList Tables = DB.tables();
        for(const auto& elem : Tables)
        {
            qDebug() << elem << Qt::endl;
        }
    }
    else
    {
        qDebug() << "DB not connected!" << Qt::endl;
    }

    //this->listen(QHostAddress::AnyIPv4, port);
    this->listen(QHostAddress::LocalHost, port);
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
    QTcpSocket* client = (QTcpSocket*)sender();
    QDataStream stream(client->readAll());

    QString command = "";
    stream >> command;
    //qDebug() << command;
    if(command == "inc_worker_data")
    {
        WORKER worker;
        stream >> worker;
        qDebug() << QDate::currentDate().toString() + " accepted data from " + worker.ID;
        client->disconnect();

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
                QString gpu_arr = "";
                for (int i = 0; i < worker.devices.size(); ++i)
                {
                    QString tmp = "";
                    //if(worker.devices.size() != 1)
                        tmp+= "(";
                    tmp += "\'" + worker.devices[i].name + "\', ";
                    tmp += "\'" + worker.devices[i].bus_id + "\', ";
                    tmp += "\'" + worker.devices[i].vendor + "\', ";
                    tmp += "\'" + worker.devices[i].total_memory + "\', ";
                    tmp += "\'" + worker.devices[i].VBIOS_version + "\', ";
                    tmp += "\'" + worker.devices[i].min_pl + "\', ";
                    tmp += "\'" + worker.devices[i].default_pl + "\', ";
                    tmp += "\'" + worker.devices[i].max_pl + "\', ";
                    tmp += QString::number(worker.devices[i].gpu_id) + ", ";
                    tmp += QString::number(worker.devices[i].fan_speed) + ", ";
                    tmp += QString::number(worker.devices[i].core_clock) + ", ";
                    tmp += QString::number(worker.devices[i].memory_clock) + ", ";
                    tmp += QString::number(worker.devices[i].power_usage) + ", ";
                    tmp += QString::number(worker.devices[i].temperature) + ", ";
                    tmp += QString::number(worker.devices[i].max_core_freq) + ", ";
                    tmp += QString::number(worker.devices[i].max_mem_freq) + ", ";
                    tmp += QString::number(worker.devices[i].speed) + ", ";
                    tmp += QString::number(worker.devices[i].speed2) + ", ";
                    tmp += QString::number(worker.devices[i].accepted_shares) + ", ";
                    tmp += QString::number(worker.devices[i].accepted_shares2) + ", ";
                    tmp += QString::number(worker.devices[i].rejected_shares) + ", ";
                    tmp += QString::number(worker.devices[i].rejected_shares2) + ", ";
                    tmp += QString::number(worker.devices[i].stale_shares) + ", ";
                    tmp += QString::number(worker.devices[i].stale_shares2) + ", ";
                    tmp += QString::number(worker.devices[i].invalid_shares) + ", ";
                    tmp += QString::number(worker.devices[i].invalid_shares2) + ", ";
                    tmp += QString::number(worker.devices[i].memory_temperature) + ", ";
                    tmp += QString::number(worker.devices[i].set_fan_speed) + ", ";
                    tmp += QString::number(worker.devices[i].set_core) + ", ";
                    tmp += QString::number(worker.devices[i].set_mem) + ", ";
                    if(i < worker.devices.size() - 1)
                    {
                        tmp += QString::number(worker.devices[i].set_pl);
                        //if(worker.devices.size() != 1)
                            tmp += ")::gpu, ";
                        //else
                            //tmp += ", ";
                    }
                    else if(i == worker.devices.size() - 1)
                    {
                        tmp += QString::number(worker.devices[i].set_pl);
                        //if(worker.devices.size() != 1)
                            tmp += ")::gpu";
                    }
                    gpu_arr.push_back(tmp);
                }

                QString query_str2 = "INSERT INTO worker_" + worker.ID + ""
                " VALUES "
                "("
                        "ARRAY[" + gpu_arr + "], "
                        "" + QString::number(worker.startup) + ", "
                        "\'" + worker.LA1 + "\', "
                        "\'" + worker.LA5 + "\', "
                        "\'" + worker.LA15 + "\', "
                        "\'" + worker.core_version + "\', "
                        "\'" + worker.nvidia_version + "\', "
                        "\'" + worker.amd_version + "\', "
                        "\'" + worker.motherboard_data + "\', "
                        "\'" + worker.CPU_info + "\', "
                        "\'" + worker.CPU_temperature + "\', "
                        "\'" + worker.disk_model + "\', "
                        "\'" + worker.disk_size + "\', "
                        "\'" + worker.disk_free_space + "\', "
                        "\'" + worker.RAM_total + "\', "
                        "\'" + worker.RAM_used + "\', "
                        "\'" + worker.RAM_free + "\', "
                        "\'" + worker.MAC + "\', "
                        "\'" + worker.local_ip + "\', "
                        "\'" + worker.ext_ip + "\', "
                        "\'" + worker.miner + "\', "
                        "\'" + worker.algorithm + "\', "
                        "\'" + worker.algorithm2 + "\', "
                        "\'" + worker.server + "\', "
                        "\'" + worker.server2 + "\', "
                        "\'" + worker.user + "\', "
                        "\'" + worker.user2 + "\', "
                        "" + QString::number(worker.total_accepted_shares) + ", "
                        "" + QString::number(worker.total_accepted_shares2) + ", "
                        "" + QString::number(worker.total_invalid_shares) + ", "
                        "" + QString::number(worker.total_invalid_shares2) + ", "
                        "" + QString::number(worker.total_rejected_shares) + ", "
                        "" + QString::number(worker.total_rejected_shares2) + ", "
                        "" + QString::number(worker.total_stale_shares) + ", "
                        "" + QString::number(worker.total_stale_shares2) + ", "
                        "" + QString::number(worker.uptime) + ", "
                        "\'" + worker.name + "\', "
                        "\'" + worker.ID + "\', "
                        "" + QString::number(worker.electricity_cost, 'f', 2) + ", "
                        "\'" + worker.version + "\', "
                        "" + "true" + ", "
                        "" + QString::number(worker.last_online) + ", "
                        "current_timestamp"
                ");";
                if(!query.exec(query_str2))
                {
                    qDebug() << "Error Query - " << query.lastError().type() << " - " << query.lastError().text();
                    qDebug() << query.lastQuery();
                }
            }
        }
    }
    else if(command == "get_user_data")
    {

    }
    else if(command == "login")
    {

    }
    else if(command == "new_reg")
    {

    }
    else if(command == "add_worker")
    {

    }
    else if(command == "del_worker")
    {

    }
    else if(command == "update_user_data")
    {

    }
}
