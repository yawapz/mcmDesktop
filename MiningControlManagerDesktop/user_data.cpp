#include "user_data.h"

user_data::user_data(QObject *parent)
    : QObject{parent}
{
}

int user_data::getTotal_count_WORKERs()
{
    return this->total_count_WORKERs;
}

int user_data::getTotal_count_GPU()
{
    return this->total_count_GPU;
}

double user_data::getTotal_power_usage()
{
    return this->total_power_usage;
}

QList<QPair<QString, unsigned long long> > user_data::getSpeed_pair_list()
{
    return speed_pair_list;
}

void user_data::counting_power_usage()
{
    this->total_power_usage = 0;
    for (auto RIG : this->RIGS)
    {
        if(RIG.status)
        {
            for (auto iter : RIG.devices)
            {
                this->total_power_usage += iter.power_usage;
            }
        }
    }
}

void user_data::counting_rigs()
{
    this->total_count_WORKERs = 0;
    for (auto& iter : RIGS)
    {
        if(iter.status)
            ++this->total_count_WORKERs;
    }
}

void user_data::counting_GPUs()
{
    this->total_count_GPU = 0;
    for (auto RIG : this->RIGS)
    {
        if(RIG.status)
            this->total_count_GPU += RIG.devices.size();
    }
}

void user_data::counting_speed()
{
    for (auto rig : this->RIGS)
    {
        if(rig.status)
        {
            QPair<QString, unsigned long long> speed_pair;
            QPair<QString, unsigned long long> speed_pair2;
            speed_pair.first = rig.algorithm;
            speed_pair2.first = rig.algorithm2;

            speed_pair.second = 0;
            speed_pair2.second = 0;
            for (auto gpu : rig.devices)
            {
                speed_pair.second += gpu.speed;
                speed_pair2.second += gpu.speed2;
            }
            // Наполнение данных
            if(this->speed_pair_list.isEmpty())
            {
                this->speed_pair_list.push_back(speed_pair);
                if(!speed_pair2.first.isEmpty() && speed_pair2.second > 0)
                {
                    this->speed_pair_list.push_back(speed_pair2);
                }
            }
            else
            {
                for(auto &iter : this->speed_pair_list)
                {
                    if(speed_pair.first == iter.first)
                    {
                        iter.second += speed_pair.second;
                    }
                    if(speed_pair2.first == iter.first)
                    {
                        iter.second += speed_pair2.second;
                    }
                }
            }
        }
    }
}

void user_data::JSON_server_to_desktop_parcer()
{
    QJsonArray rigs = this->main_json_file.value("rigs").toArray();
    for (auto rig : rigs)
    {
        WORKER worker;
        QJsonObject rig_obj = rig.toObject();
        worker.ID = rig_obj.take("ID").toString();
        worker.status = rig_obj.take("status").toBool();
        worker.LA1 = rig_obj.take("LA1").toString();
        worker.LA5 = rig_obj.take("LA5").toString();
        worker.LA15 = rig_obj.take("LA15").toString();
        worker.last_online = rig_obj.take("last_online").toInt();
        worker.startup = rig_obj.take("startup").toInt();
        worker.electricity_cost = rig_obj.take("electricity_cost").toDouble();
        worker.algorithm = rig_obj.take("algorithm").toString();
        worker.algorithm2 = rig_obj.take("algorithm2").toString();
        worker.ext_ip = rig_obj.take("ext_ip").toString();
        worker.local_ip = rig_obj.take("local_ip").toString();
        worker.miner = rig_obj.take("miner").toString();
        worker.server = rig_obj.take("server").toString();
        worker.server2 = rig_obj.take("server2").toString();
        worker.user = rig_obj.take("user").toString();
        worker.user2 = rig_obj.take("user2").toString();
        worker.uptime = rig_obj.take("uptime").toInt();
        worker.total_accepted_shares = rig_obj.take("total_accepted_shares").toInt();
        worker.total_accepted_shares2 = rig_obj.take("total_accepted_shares2").toInt();
        worker.total_invalid_shares = rig_obj.take("total_invalid_shares").toInt();
        worker.total_invalid_shares2 = rig_obj.take("total_invalid_shares2").toInt();
        worker.total_rejected_shares = rig_obj.take("total_rejected_shares").toInt();
        worker.total_rejected_shares2 = rig_obj.take("total_rejected_shares2").toInt();
        worker.total_stale_shares = rig_obj.take("total_stale_shares").toInt();
        worker.total_stale_shares2 = rig_obj.take("total_stale_shares2").toInt();
        worker.name = rig_obj.take("worker_name").toString();
        worker.core_version = rig_obj.take("core_version").toString();
        worker.nvidia_version = rig_obj.take("nvidia_version").toString();
        worker.amd_version = rig_obj.take("amd_version").toString();
        worker.motherboard_data = rig_obj.take("motherboard_data").toString();
        worker.CPU_info = rig_obj.take("CPU_info").toString();
        worker.CPU_temperature = rig_obj.take("CPU_temperature").toString();
        worker.disk_model = rig_obj.take("disk_model").toString();
        worker.disk_size = rig_obj.take("disk_size").toString();
        worker.disk_free_space = rig_obj.take("disk_free_space").toString();
        worker.RAM_total = rig_obj.take("RAM_total").toString();
        worker.RAM_used = rig_obj.take("RAM_used").toString();
        worker.RAM_free = rig_obj.take("RAM_free").toString();
        worker.MAC = rig_obj.take("MAC").toString();
        worker.version = rig_obj.take("version").toString();
        QJsonArray GPUs = rig_obj.take("devices").toArray();
        QList<GPU> worker_gpus;
        for (auto iter : GPUs)
        {
            QJsonObject iter_obj = iter.toObject();
            GPU GPU;
            GPU.bus_id = iter_obj.take("bus_id").toString();
            GPU.name = iter_obj.take("name").toString();
            GPU.fan_speed = iter_obj.take("fan_speed").toInt();
            GPU.speed = iter_obj.take("speed").toInt();
            GPU.speed2 = iter_obj.take("speed2").toInt();
            GPU.gpu_id = iter_obj.take("gpu_id").toInt();
            GPU.memory_clock = iter_obj.take("memory_clock").toInt();
            GPU.temperature = iter_obj.take("temperature").toInt();
            GPU.power_usage = iter_obj.take("power_usage").toInt();
            GPU.memory_temperature = iter_obj.take("memory_temperature").toInt();
            GPU.core_clock = iter_obj.take("core_clock").toInt();
            GPU.accepted_shares = iter_obj.take("accepted_shares").toInt();
            GPU.accepted_shares2 = iter_obj.take("accepted_shares2").toInt();
            GPU.invalid_shares = iter_obj.take("invalid_shares").toInt();
            GPU.invalid_shares2 = iter_obj.take("invalid_shares2").toInt();
            GPU.rejected_shares = iter_obj.take("rejected_shares").toInt();
            GPU.rejected_shares2 = iter_obj.take("rejected_shares").toInt();
            GPU.stale_shares = iter_obj.take("stale_shares").toInt();
            GPU.stale_shares2 = iter_obj.take("stale_shares2").toInt();
            GPU.set_fan_speed = iter_obj.take("set_fan_speed").toInt();
            GPU.set_core = iter_obj.take("set_core").toInt();
            GPU.set_mem = iter_obj.take("set_mem").toInt();
            GPU.set_pl = iter_obj.take("set_pl").toInt();
            GPU.vendor = iter_obj.take("vendor").toString();
            GPU.total_memory = iter_obj.take("total_memory").toString();
            GPU.VBIOS_version = iter_obj.take("VBIOS_version").toString();
            GPU.min_pl = iter_obj.take("min_pl").toString();
            GPU.default_pl = iter_obj.take("default_pl").toString();
            GPU.max_pl = iter_obj.take("max_pl").toString();
            GPU.max_core_freq = iter_obj.take("max_core_freq").toInt();
            GPU.max_mem_freq = iter_obj.take("max_mem_freq").toInt();
            worker_gpus.push_back(GPU);
        }
        worker.devices = worker_gpus;
        this->RIGS.push_back(worker);
    }

    // Подсчёты
    this->counting_power_usage();
    this->counting_rigs();
    this->counting_GPUs();
    this->counting_speed();
}

void user_data::JSON_from_local_directory_file()
{
    QString open_file_name = "test.json";
    QFileInfo fileinfo(open_file_name);
    QDir::setCurrent(fileinfo.path());
    QFile json_file(open_file_name);
    if (!json_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QByteArray save_data = json_file.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(save_data));
    this->main_json_file = jsonDocument.toVariant().toJsonObject();
    json_file.close();
}

QList<user_data::WORKER> user_data::getRIGS() const
{
    return this->RIGS;
}

user_data::user_data(const user_data &new_data) : QObject(nullptr)
{
    this->main_json_file = new_data.main_json_file;
    this->RIGS = new_data.RIGS;
    this->total_power_usage = new_data.total_power_usage;
    this->total_count_WORKERs = new_data.total_count_WORKERs;
    this->total_count_GPU = new_data.total_count_GPU;
    this->speed_pair_list = new_data.speed_pair_list;
}

user_data &user_data::operator=(user_data &other)
{
    this->main_json_file = other.main_json_file;
    this->RIGS = other.RIGS;
    this->total_power_usage = other.total_power_usage;
    this->total_count_WORKERs = other.total_count_WORKERs;
    this->total_count_GPU = other.total_count_GPU;
    this->speed_pair_list = other.speed_pair_list;
    return *this;
}

