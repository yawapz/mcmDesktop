#ifndef USER_DATA_H
#define USER_DATA_H
//---------------
// Временно! Нужен запрос с сервера
#include <QFile>
#include <QDir>
//---------------

#include <QObject>
#include <QString>
#include <QList>
#include <QDateTime>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class user_data : public QObject
{
    Q_OBJECT
public:
    explicit user_data(QObject *parent = nullptr);
    user_data(const user_data &new_data);
    user_data& operator=(user_data &other);

    int getTotal_count_WORKERs();
    int getTotal_count_GPU();
    double getTotal_power_usage();


    QList<QPair<QString, unsigned long long> > getSpeed_pair_list();


    //void make_get_request();
    void JSON_server_to_desktop_parcer();
    //------------------------------------
    // Временная загрузка JSON из файла
    void JSON_from_local_directory_file();
    //------------------------------------
//private:
    QJsonObject main_json_file;

    struct GPU
    {
        QString name;
        QString bus_id;

        int gpu_id;
        int fan_speed;
        int core_clock;
        int memory_clock;
        int power_usage;

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

        int temperature;
        int memory_temperature;

        int set_fan_speed;
        int set_core;
        int set_mem;
        int set_pl;

        QString vendor;
        QString total_memory;
        QString VBIOS_version;
        QString min_pl;
        QString default_pl;
        QString max_pl;

        int max_core_freq;
        int max_mem_freq;
    };
    struct WORKER
    {
        QString name;
        QList<GPU> devices;

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

        QString local_ip;
        QString ext_ip;
        QString ID;

        bool status;

        long long int startup;
        long long int last_online;

        QString LA1;
        QString LA5;
        QString LA15;

        double electricity_cost;
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
        QString version;
    };

    QList<WORKER> RIGS;
    double total_power_usage;
    int total_count_WORKERs;
    int total_count_GPU;
    QList<QPair<QString, unsigned long long>> speed_pair_list;

    // метод подсчёта потребления
    void counting_power_usage();
    // метод подсчёта количества ригов
    void counting_rigs();
    // метод подсчёта количества карт
    void counting_GPUs();
    // метод подсчёта алгоритмов и скорости make_pair
    void counting_speed();


    //void make_get_request();
    //void JSON_server_to_desktop_parcer();
    //------------------------------------
    // Временная загрузка JSON из файла
    //void JSON_from_local_directory_file();
    //------------------------------------

public:
        QList<WORKER> getRIGS() const;

signals:

};

#endif // USER_DATA_H
