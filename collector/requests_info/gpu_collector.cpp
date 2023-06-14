#include "gpu_collector.h"

gpu_collector::gpu_collector(QObject *parent)
    : QObject{parent}
{
    QObject::connect(this, SIGNAL(signal_json_delivered(QJsonObject)), this, SLOT(set_json(QJsonObject)));

    QString req_gpu_count = "nvidia-smi --query-gpu=name --format=csv,noheader | wc -l";
    int gpu_count = this->linux_terminal(req_gpu_count).toInt();
    for (int i = 0; i < gpu_count; ++i)
    {
        GPU new_gpu;
        new_gpu.gpu_id = i;
        this->gpu_list.push_back(new_gpu);
    }

    this->get_name();
    this->get_bus_id();
    this->get_vendor();
    this->get_total_memory();
    this->get_VBIOS_version();
    this->get_min_pl();
    this->get_default_pl();
    this->get_max_pl();
    this->get_fan_speed();
    this->get_core_clock();
    this->get_memory_clock();
    this->get_power_usage();
    this->get_temperature();
    this->get_max_core_freq();
    this->get_max_mem_freq();
}

QList<GPU> gpu_collector::get_gpu_list()
{
    return this->gpu_list;
}

gpu_collector::~gpu_collector()
{
}

void gpu_collector::get_name()
{
    QString req = "nvidia-smi --query-gpu=name --format=csv,noheader";
    QString names = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < names.length(); ++i)
    {
        if(names[i] != '\n')
            temp += names[i];
        else
        {
            this->gpu_list[index].name = temp;
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_bus_id()
{
    QString req = "nvidia-smi --query-gpu=pci.bus_id --format=csv,noheader";
    QString bus_id = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < bus_id.length(); ++i)
    {
        if(bus_id[i] != '\n')
            temp += bus_id[i];
        else
        {
            temp.remove(0,9);
            this->gpu_list[index].bus_id = temp;
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_vendor()
{
    QString req = "lspci -v -m | grep VGA -A 7 | grep SVendor";
    QString vendor = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < vendor.length(); ++i)
    {
        if(vendor[i] != '\n')
            temp += vendor[i];
        else
        {
            temp.remove(0,9);
            this->gpu_list[index].vendor = temp;
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_total_memory()
{
    QString req = "nvidia-smi --query-gpu=memory.total --format=csv,noheader";
    QString mem = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < mem.length(); ++i)
    {
        if(mem[i] != '\n')
            temp += mem[i];
        else
        {
            this->gpu_list[index].total_memory = temp;
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_VBIOS_version()
{
    QString req = "nvidia-smi --query-gpu=vbios_version --format=csv,noheader";
    QString mem = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < mem.length(); ++i)
    {
        if(mem[i] != '\n')
            temp += mem[i];
        else
        {
            this->gpu_list[index].VBIOS_version = temp;
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_min_pl()
{
    QString req = "nvidia-smi --query-gpu=power.min_limit --format=csv,noheader";
    QString min_pl = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < min_pl.length(); ++i)
    {
        if(min_pl[i] != '\n')
            temp += min_pl[i];
        else
        {
            this->gpu_list[index].min_pl = temp;
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_default_pl()
{
    QString req = "nvidia-smi --query-gpu=power.default_limit --format=csv,noheader";
    QString default_pl = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < default_pl.length(); ++i)
    {
        if(default_pl[i] != '\n')
            temp += default_pl[i];
        else
        {
            this->gpu_list[index].default_pl = temp;
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_max_pl()
{
    QString req = "nvidia-smi --query-gpu=power.max_limit --format=csv,noheader";
    QString max_pl = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < max_pl.length(); ++i)
    {
        if(max_pl[i] != '\n')
            temp += max_pl[i];
        else
        {
            this->gpu_list[index].max_pl = temp;
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_fan_speed()
{
    QString req = "nvidia-smi --query-gpu=fan.speed --format=csv,noheader";
    QString fan_speed = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < fan_speed.length(); ++i)
    {
        if(fan_speed[i] != '\n' && fan_speed[i] != '%' && fan_speed[i] != ' ')
            temp += fan_speed[i];
        else if(fan_speed[i] == '%' || fan_speed[i] != ' ')
            continue;
        else
        {
            this->gpu_list[index].fan_speed = temp.toInt();
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_core_clock()
{
    QString req = "nvidia-smi --query-gpu=clocks.sm --format=csv,noheader";
    QString core_clock = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < core_clock.length(); ++i)
    {
        if(core_clock[i] == ' ' || core_clock[i] == 'M' || core_clock[i] == 'H' || core_clock[i] == 'z')
            continue;

        if(core_clock[i] != '\n')
            temp += core_clock[i];
        else
        {
            this->gpu_list[index].core_clock = temp.toInt();
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_memory_clock()
{
    QString req = "nvidia-smi --query-gpu=clocks.current.memory --format=csv,noheader";
    QString mem_clock = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < mem_clock.length(); ++i)
    {
        if(mem_clock[i] == ' ' || mem_clock[i] == 'M' || mem_clock[i] == 'H' || mem_clock[i] == 'z')
            continue;

        if(mem_clock[i] != '\n')
            temp += mem_clock[i];
        else
        {
            this->gpu_list[index].memory_clock = temp.toInt();
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_power_usage()
{
    QString req = "nvidia-smi --query-gpu=power.draw --format=csv,noheader";
    QString power_usage = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < power_usage.length(); ++i)
    {
        if(power_usage[i] == ' ' || power_usage[i] == 'W')
            continue;

        if(power_usage[i] != '\n')
            temp += power_usage[i];
        else
        {
            this->gpu_list[index].power_usage = (int)temp.toDouble();
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_temperature()
{
    QString req = "nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader";
    QString core_temperature = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < core_temperature.length(); ++i)
    {
        if(core_temperature[i] != '\n')
            temp += core_temperature[i];
        else
        {
            this->gpu_list[index].temperature = temp.toInt();
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_max_core_freq()
{
    QString req = "nvidia-smi --query-gpu=clocks.max.graphics --format=csv,noheader";
    QString max_core_clock = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < max_core_clock.length(); ++i)
    {
        if(max_core_clock[i] == ' ' || max_core_clock[i] == 'M' || max_core_clock[i] == 'H' || max_core_clock[i] == 'z')
            continue;

        if(max_core_clock[i] != '\n')
            temp += max_core_clock[i];
        else
        {
            this->gpu_list[index].max_mem_freq = temp.toInt();
            temp.clear();
            ++index;
        }
    }
}

void gpu_collector::get_max_mem_freq()
{
    QString req = "nvidia-smi --query-gpu=clocks.max.memory --format=csv,noheader";
    QString max_mem_clock = this->linux_terminal(req);

    QString temp = "";
    int index = 0;
    for (int i = 0; i < max_mem_clock.length(); ++i)
    {
        if(max_mem_clock[i] == ' ' || max_mem_clock[i] == 'M' || max_mem_clock[i] == 'H' || max_mem_clock[i] == 'z')
            continue;

        if(max_mem_clock[i] != '\n')
            temp += max_mem_clock[i];
        else
        {
            this->gpu_list[index].max_mem_freq = temp.toInt();
            temp.clear();
            ++index;
        }
    }
}

QString gpu_collector::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}

void gpu_collector::gminer_json_parcer()
{
    int index = 0;
    QJsonArray GPUs = this->main_json_file.take("devices").toArray();
    for (auto iter : GPUs)
    {
        QJsonObject iter_obj = iter.toObject();
        gpu_list[index].speed = iter_obj.take("speed").toInt();
        gpu_list[index].speed2 = iter_obj.take("speed2").toInt();
        gpu_list[index].memory_temperature = this->main_json_file.take("memory_temperature").toInt();
        gpu_list[index].accepted_shares = this->main_json_file.take("accepted_shares").toInt();
        gpu_list[index].accepted_shares2 = this->main_json_file.take("accepted_shares2").toInt();
        gpu_list[index].invalid_shares = this->main_json_file.take("invalid_shares").toInt();
        gpu_list[index].invalid_shares2 = this->main_json_file.take("invalid_shares2").toInt();
        gpu_list[index].rejected_shares = this->main_json_file.take("rejected_shares").toInt();
        gpu_list[index].rejected_shares2 = this->main_json_file.take("rejected_shares").toInt();
        gpu_list[index].stale_shares = this->main_json_file.take("stale_shares").toInt();
        gpu_list[index].stale_shares2 = this->main_json_file.take("stale_shares2").toInt();
        ++index;
    }
}

void gpu_collector::set_json(QJsonObject new_json)
{
    this->main_json_file = new_json;
    if(this->main_json_file.take("miner").toString().toLower().contains("gminer"))
    {
        this->gminer_json_parcer();
    }
    else if (this->main_json_file.take("Software").toString().toLower().contains("lolminer"))
    {
        //this->lolminer_json_parcer();
    }
}
