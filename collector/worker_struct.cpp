#pragma once

#include <QString>
#include <QList>
#include "gpu_struct.cpp"

struct WORKER
{
    // data from system
    QList<GPU> devices;
    long long int startup;

    QString LA1;
    QString LA5;
    QString LA15;
    QString core_version;
    QString nvidia_version;
    QString amd_version;
    QString motherboard_data;
    QString CPU_info;
    QString CPU_temperature;
    QString disk_model;
    QString disk_size;
    QString disk_free_space;
    QString RAM_total;
    QString RAM_used;
    QString RAM_free;
    QString MAC;
    QString local_ip;
    QString ext_ip;

    // data from miner
    QString miner;
    QString algorithm;
    QString algorithm2;
    QString server;
    QString server2;
    QString user;
    QString user2;

    int total_accepted_shares;
    int total_accepted_shares2;
    int total_invalid_shares;
    int total_invalid_shares2;
    int total_rejected_shares;
    int total_rejected_shares2;
    int total_stale_shares;
    int total_stale_shares2;

    long long int uptime;
    // data from config
    QString name;
    QString ID;

    double electricity_cost;
    QString version;

    // Обработка на стороне сервера
    bool status;
    long long int last_online;
};
