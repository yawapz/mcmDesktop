#include "worker_data_builder.h"

worker_data_builder::worker_data_builder(QObject *parent)
    : QObject{parent}
{

}

void worker_data_builder::get_new_data()
{
    this->reader = new miner_json_reader(); // в поток

    motherboard motherboard;
    cpu cpu;
    mac mac;
    ram ram;
    disk disk;
    ip ip; // в поток
    kernel kernel;
    nvidia nvidia;
    radeon radeon;
    load_average LA;
    startup_timer timer;
    gpu_collector *arr = new gpu_collector(); // в поток

    connect(reader, SIGNAL(signal_transport_json(QJsonObject)), this, SLOT(slot_transfer(QJsonObject)));
    connect(reader, SIGNAL(signal_transport_json(QJsonObject)), arr, SIGNAL(signal_json_delivered(QJsonObject)));

    this->reader->get_miner_json();

    // system data
    this->worker.motherboard_data = motherboard.get_info();
    this->worker.CPU_info = cpu.get_info();
    this->worker.CPU_temperature = cpu.get_temperature();

    this->worker.LA1  = LA.get_la1();
    this->worker.LA5  = LA.get_la5();
    this->worker.LA15 = LA.get_la15();

    this->worker.MAC = mac.get_info();
    this->worker.local_ip = ip.get_local_ip();
    this->worker.ext_ip = ip.get_external_ip();

    this->worker.disk_free_space = disk.get_disk_free();
    this->worker.disk_model = disk.get_disk_name();
    this->worker.disk_size = disk.get_disk_free();

    this->worker.RAM_free = ram.get_ram_free();
    this->worker.RAM_total = ram.get_ram_total();
    this->worker.RAM_used = ram.get_ram_used();

    this->worker.nvidia_version = nvidia.get_version_info();
    this->worker.amd_version = radeon.get_version_info();

    this->worker.core_version = kernel.get_info();
    this->worker.startup = timer.get_timer_seconds();

    this->worker.devices = arr->get_gpu_list();
    // miner data -- when will the data arrive

    // config data
    this->worker.version;
    this->worker.electricity_cost;
    // server data
    this->worker.status = true;
    this->worker.last_online = 0;
}

void worker_data_builder::choice_parcer()
{
    if(this->json.take("miner").toString().toLower().contains("gminer"))
    {
        this->gminer_json_parcer();
    }
    else if (this->json.take("Software").toString().toLower().contains("lolminer"))
    {
        //this->lolminer_json_parcer();
    }
}

void worker_data_builder::gminer_json_parcer()
{
    QString all_algos = this->json.take("algorithm").toString();
    if(all_algos.contains('+'))
    {
        QString all_algos2 = all_algos;

        std::string alg1 = all_algos.toStdString();
        int alg1_pos = alg1.find_first_of(' ');
        if(alg1_pos != -1)
            alg1.erase(alg1_pos);

        std::string alg2 = all_algos2.toStdString();
        if(alg1_pos != -1)
            alg2.erase(0, alg1_pos + 3);

        int alg2_pos = alg2.find(' ');
        if(alg2_pos != -1)
            alg2.erase(alg2_pos);

        this->worker.algorithm = QString::fromStdString(alg1);
        this->worker.algorithm2 = QString::fromStdString(alg2);
    }
    else
    {
        this->worker.algorithm = all_algos;
        this->worker.algorithm2 = "";
    }

    this->worker.miner = this->json.take("miner").toString();
    this->worker.server = this->json.take("server").toString();
    this->worker.server2 = this->json.take("server2").toString();
    this->worker.user = this->json.take("user").toString();
    this->worker.user2 = this->json.take("user2").toString();
    this->worker.uptime = this->json.take("uptime").toInt();
    this->worker.total_accepted_shares = this->json.take("total_accepted_shares").toInt();
    this->worker.total_accepted_shares2 = this->json.take("total_accepted_shares2").toInt();
    this->worker.total_rejected_shares = this->json.take("total_rejected_shares").toInt();
    this->worker.total_rejected_shares2 = this->json.take("total_rejected_shares2").toInt();
    this->worker.total_stale_shares = this->json.take("total_stale_shares").toInt();
    this->worker.total_stale_shares2 = this->json.take("total_stale_shares2").toInt();
    this->worker.total_invalid_shares = this->json.take("total_invalid_shares").toInt();
    this->worker.total_invalid_shares2 = this->json.take("total_invalid_shares2").toInt();
}

void worker_data_builder::slot_transfer(QJsonObject new_json)
{
    this->json = new_json;
    this->choice_parcer();
}
