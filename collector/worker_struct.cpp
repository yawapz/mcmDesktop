#pragma once

#include <QString>
#include <QIODevice>
#include <QDataStream>
#include <QList>
#include "gpu_struct.cpp"
#include "qdebug.h"

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

    //-----------------------------------------------

    QByteArray* to_raw()
    {
        QByteArray* array = new QByteArray();
        QDataStream stream(array, QIODevice::Append);
        int count_devices = this->devices.size();

        stream << count_devices;
        for (auto& iter : this->devices)
        {
            stream << iter.to_raw();
        }
        stream << this->startup;
        stream << this->LA1;
        stream << this->LA5;
        stream << this->LA15;
        stream << this->core_version;
        stream << this->nvidia_version;
        stream << this->amd_version;
        stream << this->motherboard_data;
        stream << this->CPU_info;
        stream << this->CPU_temperature;
        stream << this->disk_model;
        stream << this->disk_size;
        stream << this->disk_free_space;
        stream << this->RAM_total;
        stream << this->RAM_used;
        stream << this->RAM_free;
        stream << this->MAC;
        stream << this->local_ip;
        stream << this->ext_ip;
        stream << this->miner;
        stream << this->algorithm;
        stream << this->algorithm2;
        stream << this->server;
        stream << this->server2;
        stream << this->user;
        stream << this->user2;
        stream << this->total_accepted_shares;
        stream << this->total_accepted_shares2;
        stream << this->total_invalid_shares;
        stream << this->total_invalid_shares2;
        stream << this->total_rejected_shares;
        stream << this->total_rejected_shares2;
        stream << this->total_stale_shares;
        stream << this->total_stale_shares2;
        stream << this->uptime;
        stream << this->name;
        stream << this->ID;
        stream << this->electricity_cost;
        stream << this->version;
        stream << this->status;
        stream << this->last_online;



        //qDebug() <<*array; // пустая
        return array;
    }

    friend QDataStream &operator<<(QDataStream& stream, const WORKER& worker)
    {
        int count_devices = worker.devices.size();

        stream << count_devices;
        for (auto& iter : worker.devices)
        {
            stream << iter;
        }
        stream << worker.startup;
        stream << worker.LA1;
        stream << worker.LA5;
        stream << worker.LA15;
        stream << worker.core_version;
        stream << worker.nvidia_version;
        stream << worker.amd_version;
        stream << worker.motherboard_data;
        stream << worker.CPU_info;
        stream << worker.CPU_temperature;
        stream << worker.disk_model;
        stream << worker.disk_size;
        stream << worker.disk_free_space;
        stream << worker.RAM_total;
        stream << worker.RAM_used;
        stream << worker.RAM_free;
        stream << worker.MAC;
        stream << worker.local_ip;
        stream << worker.ext_ip;
        stream << worker.miner;
        stream << worker.algorithm;
        stream << worker.algorithm2;
        stream << worker.server;
        stream << worker.server2;
        stream << worker.user;
        stream << worker.user2;
        stream << worker.total_accepted_shares;
        stream << worker.total_accepted_shares2;
        stream << worker.total_invalid_shares;
        stream << worker.total_invalid_shares2;
        stream << worker.total_rejected_shares;
        stream << worker.total_rejected_shares2;
        stream << worker.total_stale_shares;
        stream << worker.total_stale_shares2;
        stream << worker.uptime;
        stream << worker.name;
        stream << worker.ID;
        stream << worker.electricity_cost;
        stream << worker.version;
        stream << worker.status;
        stream << worker.last_online;

        return stream;
    }

    friend QDataStream& operator>>(QDataStream& stream, WORKER& worker)
    {
        int count_devices = 0;
        stream >> count_devices;
        for (int i = 0; i < count_devices; ++i)
        {
            GPU *gpu = new GPU;
            stream >> gpu->name;
            stream >> gpu->bus_id;
            stream >> gpu->vendor;
            stream >> gpu->total_memory;
            stream >> gpu->VBIOS_version;
            stream >> gpu->min_pl;
            stream >> gpu->default_pl;
            stream >> gpu->max_pl;
            stream >> gpu->gpu_id;
            stream >> gpu->fan_speed;
            stream >> gpu->core_clock;
            stream >> gpu->memory_clock;
            stream >> gpu->power_usage;
            stream >> gpu->temperature;
            stream >> gpu->max_core_freq;
            stream >> gpu->max_mem_freq;
            stream >> gpu->speed;
            stream >> gpu->speed2;
            stream >> gpu->accepted_shares;
            stream >> gpu->accepted_shares2;
            stream >> gpu->rejected_shares;
            stream >> gpu->rejected_shares2;
            stream >> gpu->stale_shares;
            stream >> gpu->stale_shares2;
            stream >> gpu->invalid_shares;
            stream >> gpu->invalid_shares2;
            stream >> gpu->memory_temperature;
            stream >> gpu->set_fan_speed;
            stream >> gpu->set_core;
            stream >> gpu->set_mem;
            stream >> gpu->set_pl;
            worker.devices.push_back(*gpu);
        }
        stream >> worker.startup;
        stream >> worker.LA1;
        stream >> worker.LA5;
        stream >> worker.LA15;
        stream >> worker.core_version;
        stream >> worker.nvidia_version;
        stream >> worker.amd_version;
        stream >> worker.motherboard_data;
        stream >> worker.CPU_info;
        stream >> worker.CPU_temperature;
        stream >> worker.disk_model;
        stream >> worker.disk_size;
        stream >> worker.disk_free_space;
        stream >> worker.RAM_total;
        stream >> worker.RAM_used;
        stream >> worker.RAM_free;
        stream >> worker.MAC;
        stream >> worker.local_ip;
        stream >> worker.ext_ip;
        stream >> worker.miner;
        stream >> worker.algorithm;
        stream >> worker.algorithm2;
        stream >> worker.server;
        stream >> worker.server2;
        stream >> worker.user;
        stream >> worker.user2;
        stream >> worker.total_accepted_shares;
        stream >> worker.total_accepted_shares2;
        stream >> worker.total_invalid_shares;
        stream >> worker.total_invalid_shares2;
        stream >> worker.total_rejected_shares;
        stream >> worker.total_rejected_shares2;
        stream >> worker.total_stale_shares;
        stream >> worker.total_stale_shares2;
        stream >> worker.uptime;
        stream >> worker.name;
        stream >> worker.ID;
        stream >> worker.electricity_cost;
        stream >> worker.version;
        stream >> worker.status;
        stream >> worker.last_online;
        return stream;
    }
};
