#pragma once

#include <QString>

struct GPU
{
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
};
