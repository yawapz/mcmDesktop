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

    friend QDebug operator<<(QDebug d, const WORKER &worker)
    {
        for (int i = 0; i < worker.devices.size(); ++i)
        {
            GPU gpu = worker.devices[i];
            d << "GPU " << i << " name " << gpu.name << Qt::endl;
            d << "GPU " << i << " bus_id " << gpu.bus_id << Qt::endl;
            d << "GPU " << i << " vendor " << gpu.vendor << Qt::endl;
            d << "GPU " << i << " total_memory " << gpu.total_memory << Qt::endl;
            d << "GPU " << i << " VBIOS_version " << gpu.VBIOS_version << Qt::endl;
            d << "GPU " << i << " min_pl " << gpu.min_pl << Qt::endl;
            d << "GPU " << i << " default_pl " << gpu.default_pl << Qt::endl;
            d << "GPU " << i << " max_pl " << gpu.max_pl << Qt::endl;
            d << "GPU " << i << " gpu_id " << gpu.gpu_id << Qt::endl;
            d << "GPU " << i << " fan_speed " << gpu.fan_speed << Qt::endl;
            d << "GPU " << i << " core_clock " << gpu.core_clock << Qt::endl;
            d << "GPU " << i << " memory_clock " << gpu.memory_clock << Qt::endl;
            d << "GPU " << i << " power_usage " << gpu.power_usage;
            d << "GPU " << i << " temperature " << gpu.temperature << Qt::endl;
            d << "GPU " << i << " max_core_freq " << gpu.max_core_freq << Qt::endl;
            d << "GPU " << i << " max_mem_freq " << gpu.max_mem_freq << Qt::endl;
            d << "GPU " << i << " speed " << gpu.speed << Qt::endl;
            d << "GPU " << i << " speed2 " << gpu.speed2 << Qt::endl;
            d << "GPU " << i << " accepted_shares " << gpu.accepted_shares << Qt::endl;
            d << "GPU " << i << " accepted_shares2 " << gpu.accepted_shares2 << Qt::endl;
            d << "GPU " << i << " rejected_shares " << gpu.rejected_shares << Qt::endl;
            d << "GPU " << i << " rejected_shares2 " << gpu.rejected_shares2 << Qt::endl;
            d << "GPU " << i << " stale_shares " << gpu.stale_shares << Qt::endl;
            d << "GPU " << i << " stale_shares2 " << gpu.stale_shares2 << Qt::endl;
            d << "GPU " << i << " invalid_shares " << gpu.invalid_shares << Qt::endl;
            d << "GPU " << i << " invalid_shares2 " << gpu.invalid_shares2 << Qt::endl;
            d << "GPU " << i << " memory_temperature " << gpu.memory_temperature << Qt::endl;
            d << "GPU " << i << " set_fan_speed " << gpu.set_fan_speed << Qt::endl;
            d << "GPU " << i << " set_core " << gpu.set_core << Qt::endl;
            d << "GPU " << i << " set_mem " << gpu.set_mem << Qt::endl;
            d << "GPU " << i << " set_pl " << gpu.set_pl << Qt::endl;
        }
        d << "startup " << worker.startup << Qt::endl;
        d << "LA1 " << worker.LA1 << Qt::endl;
        d << "LA5 " << worker.LA5 << Qt::endl;
        d << "LA15 " << worker.LA15 << Qt::endl;
        d << "core_version " << worker.core_version << Qt::endl;
        d << "nvidia_version " << worker.nvidia_version << Qt::endl;
        d << "amd_version " << worker.amd_version << Qt::endl;
        d << "motherboard_data " << worker.motherboard_data << Qt::endl;
        d << "CPU_info " << worker.CPU_info << Qt::endl;
        d << "CPU_temperature " << worker.CPU_temperature << Qt::endl;
        d << "disk_model " << worker.disk_model << Qt::endl;
        d << "disk_size " << worker.disk_size << Qt::endl;
        d << "disk_free_space " << worker.disk_free_space << Qt::endl;
        d << "RAM_total " << worker.RAM_total << Qt::endl;
        d << "RAM_used " << worker.RAM_used << Qt::endl;
        d << "RAM_free " << worker.RAM_free << Qt::endl;
        d << "MAC " << worker.MAC << Qt::endl;
        d << "local_ip " << worker.local_ip << Qt::endl;
        d << "ext_ip " << worker.ext_ip << Qt::endl;
        d << "miner " << worker.miner << Qt::endl;
        d << "algorithm " << worker.algorithm << Qt::endl;
        d << "algorithm2 " << worker.algorithm2 << Qt::endl;
        d << "server " << worker.server << Qt::endl;
        d << "server2 " << worker.server2 << Qt::endl;
        d << "user " << worker.user << Qt::endl;
        d << "user2 " << worker.user2 << Qt::endl;
        d << "total_accepted_shares " << worker.total_accepted_shares << Qt::endl;
        d << "total_accepted_shares2 " << worker.total_accepted_shares2 << Qt::endl;
        d << "total_invalid_shares " << worker.total_invalid_shares << Qt::endl;
        d << "total_invalid_shares2 " << worker.total_invalid_shares2 << Qt::endl;
        d << "total_rejected_shares " << worker.total_rejected_shares << Qt::endl;
        d << "total_rejected_shares2 " << worker.total_rejected_shares2 << Qt::endl;
        d << "total_stale_shares " << worker.total_stale_shares << Qt::endl;
        d << "total_stale_shares2 " << worker.total_stale_shares2 << Qt::endl;
        d << "uptime " << worker.uptime << Qt::endl;
        d << "name " << worker.name << Qt::endl;
        d << "ID " << worker.ID << Qt::endl;
        d << "electricity_cost " << worker.electricity_cost << Qt::endl;
        d << "version " << worker.version << Qt::endl;
        d << "status " << worker.status << Qt::endl;
        d << "last_online " << worker.last_online << Qt::endl;
        return d;
    }
};
