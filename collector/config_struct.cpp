#pragma once

#include <QString>
#include <QList>

struct gpu_conf_data
{
    int set_fan_speed;
    int set_core;
    int set_mem;
    int set_pl;
};

struct conf_data
{
    int miner_port;
    int server_port;
    double electricity_cost;
    QString server_addr;
    QString name;
    QString ID;
    QString version;

    QList<gpu_conf_data> list;
};
