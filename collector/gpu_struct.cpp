#pragma once

#include <QString>
#include <QIODevice>
#include <QDataStream>

struct GPU
{
    GPU()
    {
        this->name = "";
        this->bus_id = "";
        this->vendor = "";
        this->total_memory = "";
        this->VBIOS_version = "";
        this->min_pl = "";
        this->default_pl = "";
        this->max_pl = "";
        this->gpu_id = 0;
        this->fan_speed = 0;
        this->core_clock = 0;
        this->memory_clock = 0;
        this->power_usage = 0;
        this->temperature = 0;
        this->max_core_freq = 0;
        this->max_mem_freq = 0;
        this->speed = 0;
        this->speed2 = 0;
        this->accepted_shares = 0;
        this->accepted_shares2 = 0;
        this->rejected_shares = 0;
        this->rejected_shares2 = 0;
        this->stale_shares = 0;
        this->stale_shares2 = 0;
        this->invalid_shares = 0;
        this->invalid_shares2 = 0;
        this->memory_temperature = 0;
        this->set_fan_speed = 0;
        this->set_core = 0;
        this->set_mem = 0;
        this->set_pl = 0;
    }
    // data from system
    QString name;
    QString bus_id;
    QString vendor;
    QString total_memory;
    QString VBIOS_version;
    QString min_pl;
    QString default_pl;
    QString max_pl;

    int gpu_id;
    int fan_speed;
    int core_clock;
    int memory_clock;
    int power_usage;
    int temperature;
    int max_core_freq;
    int max_mem_freq;

    // data from miner
    int speed;
    int speed2;
    int accepted_shares;
    int accepted_shares2;
    int rejected_shares;
    int rejected_shares2;
    int stale_shares;
    int stale_shares2;
    int invalid_shares;
    int invalid_shares2;
    int memory_temperature;

    // data from config
    int set_fan_speed;
    int set_core;
    int set_mem;
    int set_pl;

    QByteArray* to_raw()
    {
        QByteArray* array = new QByteArray();
        QDataStream stream(array, QIODevice::Append);

        stream << this->name;
        stream << this->bus_id;
        stream << this->vendor;
        stream << this->total_memory;
        stream << this->VBIOS_version;
        stream << this->min_pl;
        stream << this->default_pl;
        stream << this->max_pl;
        stream << this->gpu_id;
        stream << this->fan_speed;
        stream << this->core_clock;
        stream << this->memory_clock;
        stream << this->power_usage;
        stream << this->temperature;
        stream << this->max_core_freq;
        stream << this->max_mem_freq;
        stream << this->speed;
        stream << this->speed2;
        stream << this->accepted_shares;
        stream << this->accepted_shares2;
        stream << this->rejected_shares;
        stream << this->rejected_shares2;
        stream << this->stale_shares;
        stream << this->stale_shares2;
        stream << this->invalid_shares;
        stream << this->invalid_shares2;
        stream << this->memory_temperature;
        stream << this->set_fan_speed;
        stream << this->set_core;
        stream << this->set_mem;
        stream << this->set_pl;

        return array;
    }

    friend QDataStream &operator<<(QDataStream& stream, const GPU& gpu)
    {
        stream << gpu.name;
        stream << gpu.bus_id;
        stream << gpu.vendor;
        stream << gpu.total_memory;
        stream << gpu.VBIOS_version;
        stream << gpu.min_pl;
        stream << gpu.default_pl;
        stream << gpu.max_pl;
        stream << gpu.gpu_id;
        stream << gpu.fan_speed;
        stream << gpu.core_clock;
        stream << gpu.memory_clock;
        stream << gpu.power_usage;
        stream << gpu.temperature;
        stream << gpu.max_core_freq;
        stream << gpu.max_mem_freq;
        stream << gpu.speed;
        stream << gpu.speed2;
        stream << gpu.accepted_shares;
        stream << gpu.accepted_shares2;
        stream << gpu.rejected_shares;
        stream << gpu.rejected_shares2;
        stream << gpu.stale_shares;
        stream << gpu.stale_shares2;
        stream << gpu.invalid_shares;
        stream << gpu.invalid_shares2;
        stream << gpu.memory_temperature;
        stream << gpu.set_fan_speed;
        stream << gpu.set_core;
        stream << gpu.set_mem;
        stream << gpu.set_pl;

        return stream;
    }

    friend QDataStream& operator>>(QDataStream& stream, GPU& gpu)
    {
        stream >> gpu.name;
        stream >> gpu.bus_id;
        stream >> gpu.vendor;
        stream >> gpu.total_memory;
        stream >> gpu.VBIOS_version;
        stream >> gpu.min_pl;
        stream >> gpu.default_pl;
        stream >> gpu.max_pl;
        stream >> gpu.gpu_id;
        stream >> gpu.fan_speed;
        stream >> gpu.core_clock;
        stream >> gpu.memory_clock;
        stream >> gpu.power_usage;
        stream >> gpu.temperature;
        stream >> gpu.max_core_freq;
        stream >> gpu.max_mem_freq;
        stream >> gpu.speed;
        stream >> gpu.speed2;
        stream >> gpu.accepted_shares;
        stream >> gpu.accepted_shares2;
        stream >> gpu.rejected_shares;
        stream >> gpu.rejected_shares2;
        stream >> gpu.stale_shares;
        stream >> gpu.stale_shares2;
        stream >> gpu.invalid_shares;
        stream >> gpu.invalid_shares2;
        stream >> gpu.memory_temperature;
        stream >> gpu.set_fan_speed;
        stream >> gpu.set_core;
        stream >> gpu.set_mem;
        stream >> gpu.set_pl;

        return stream;
    }
};
