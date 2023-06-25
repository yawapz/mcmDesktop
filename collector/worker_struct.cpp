#pragma once

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QString>
#include <QIODevice>
#include <QDataStream>
#include <QList>
#include "gpu_struct.cpp"
#include "qdebug.h"

struct WORKER
{
    QJsonObject worker_json;
    QString str_json;
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
    WORKER()
    {
        //this->devices;
        this->startup = 0;
        this->LA1 = "";
        this->LA5 = "";
        this->LA15 = "";
        this->core_version = "";
        this->nvidia_version = "";
        this->amd_version = "";
        this->motherboard_data = "";
        this->CPU_info = "";
        this->CPU_temperature = "";
        this->disk_model = "";
        this->disk_size = "";
        this->disk_free_space = "";
        this->RAM_total = "";
        this->RAM_used = "";
        this->RAM_free = "";
        this->MAC ="";
        this->local_ip = "";
        this->ext_ip = "";
        this->miner = "";
        this->algorithm = "";
        this->algorithm2 = "";
        this->server = "";
        this->server2 = "";
        this->user = "";
        this->user2 = "";
        this->total_accepted_shares = 0;
        this->total_accepted_shares = 0;
        this->total_invalid_shares = 0;
        this->total_invalid_shares2 = 0;
        this->total_rejected_shares = 0;
        this->total_rejected_shares2 = 0;
        this->total_stale_shares = 0;
        this->total_stale_shares2 = 0;
        this->uptime = 0;
        this->name = "";
        this->ID = "";
        this->electricity_cost = 0;
        this->version = "";
        this->status = false;
        this->last_online = 0;
    }

    void fill_JSON_object()
    {
        QJsonArray gpu_arr;
        for (auto gpu : this->devices)
        {
            QJsonObject obj;
            obj.insert("name", gpu.name);
            obj.insert("bus_id", gpu.bus_id);
            obj.insert("gpu_id", gpu.gpu_id);
            obj.insert("fan_speed", gpu.fan_speed);
            obj.insert("core_clock", gpu.core_clock);
            obj.insert("memory_clock", gpu.memory_clock);
            obj.insert("power_usage", gpu.power_usage);
            obj.insert("speed", gpu.speed);
            obj.insert("speed2", gpu.speed2);
            obj.insert("accepted_shares", gpu.accepted_shares);
            obj.insert("accepted_shares2", gpu.accepted_shares2);
            obj.insert("rejected_shares", gpu.rejected_shares);
            obj.insert("rejected_shares2", gpu.rejected_shares2);
            obj.insert("stale_shares", gpu.stale_shares);
            obj.insert("stale_shares2", gpu.stale_shares2);
            obj.insert("invalid_shares", gpu.invalid_shares);
            obj.insert("invalid_shares2", gpu.invalid_shares2);
            obj.insert("temperature", gpu.temperature);
            obj.insert("memory_temperature", gpu.memory_temperature);
            obj.insert("set_fan_speed", gpu.set_fan_speed);
            obj.insert("set_core", gpu.set_core);
            obj.insert("set_mem", gpu.set_mem);
            obj.insert("set_pl", gpu.set_pl);
            obj.insert("vendor", gpu.vendor);
            obj.insert("VBIOS_version", gpu.VBIOS_version);
            obj.insert("total_memory", gpu.total_memory);
            obj.insert("min_pl", gpu.min_pl);
            obj.insert("default_pl", gpu.default_pl);
            obj.insert("max_pl", gpu.max_pl);
            obj.insert("max_core_freq", gpu.max_core_freq);
            obj.insert("max_mem_freq", gpu.max_mem_freq);
            gpu_arr.push_back(obj);
        }
        QJsonObject doc;
        doc.insert("status", this->status);
        doc.insert("startup", this->startup);
        doc.insert("last_online", this->last_online);
        doc.insert("worker_name", this->name);
        doc.insert("ID", this->ID);
        doc.insert("devices",gpu_arr);
        doc.insert("miner", this->miner);
        doc.insert("algorithm", this->algorithm);
        doc.insert("algorithm2", this->algorithm2);
        doc.insert("server", this->server);
        doc.insert("server2", this->server2);
        doc.insert("user", this->user);
        doc.insert("user2", this->user2);
        doc.insert("total_accepted_shares", this->total_accepted_shares);
        doc.insert("total_accepted_shares2", this->total_accepted_shares2);
        doc.insert("total_rejected_shares", this->total_rejected_shares);
        doc.insert("total_rejected_shares2", this->total_rejected_shares);
        doc.insert("total_invalid_shares", this->total_invalid_shares);
        doc.insert("total_invalid_shares2", this->total_invalid_shares2);
        doc.insert("total_stale_shares", this->total_stale_shares);
        doc.insert("total_stale_shares2", this->total_stale_shares2);
        doc.insert("uptime", this->uptime);
        doc.insert("local_ip", this->local_ip);
        doc.insert("ext_ip", this->ext_ip);
        doc.insert("LA1", this->LA1);
        doc.insert("LA5", this->LA5);
        doc.insert("LA15", this->LA15);
        doc.insert("electricity_cost", this->electricity_cost);
        doc.insert("core_version", this->core_version);
        doc.insert("nvidia_version", this->nvidia_version);
        doc.insert("amd_version", this->amd_version);
        doc.insert("motherboard_data", this->motherboard_data);
        doc.insert("CPU_info", this->CPU_info);
        doc.insert("CPU_temperature", this->CPU_temperature);
        doc.insert("disk_model", this->disk_model);
        doc.insert("disk_size", this->disk_size);
        doc.insert("disk_free_space", this->disk_free_space);
        doc.insert("RAM_total", this->RAM_total);
        doc.insert("RAM_used", this->RAM_used);
        doc.insert("RAM_free", this->RAM_free);
        doc.insert("MAC", this->MAC);
        doc.insert("version", this->version);
        this->worker_json = doc;
        QJsonDocument json_doc(this->worker_json);
        this->str_json = (json_doc.toJson(QJsonDocument::Compact));
    }
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
        stream << worker.worker_json;
        stream << worker.str_json;

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
        stream >> worker.worker_json;
        stream >> worker.str_json;
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
