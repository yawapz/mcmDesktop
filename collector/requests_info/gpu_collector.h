#ifndef GPU_COLLECTOR_H
#define GPU_COLLECTOR_H

#include <QObject>

#include "../collector/gpu_struct.cpp"
#include <QProcess>
#include <QString>
#include <QList>
#include <QByteArray>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <string>
#include <algorithm>

class gpu_collector  : public QObject
{
    Q_OBJECT
public:
    explicit gpu_collector(QObject *parent = nullptr);
    QList<GPU> get_gpu_list();
    ~gpu_collector();

signals:
    void signal_json_delivered(QJsonObject);

private:
    QList<GPU> gpu_list;

    // data from system
    void get_name();
    void get_bus_id();
    void get_vendor();
    void get_total_memory();
    void get_VBIOS_version();
    void get_min_pl();
    void get_default_pl();
    void get_max_pl();
    void get_fan_speed();
    void get_core_clock();
    void get_memory_clock();
    void get_power_usage();
    void get_temperature();
    void get_max_core_freq();
    void get_max_mem_freq();

    // data from miner
    void get_speed();
    void get_speed2();
    void get_accepted_shares();
    void get_accepted_shares2();
    void get_rejected_shares();
    void get_rejected_shares2();
    void get_stale_shares();
    void get_stale_shares2();
    void get_invalid_shares();
    void get_invalid_shares2();
    void get_memory_temperature();

    // data from config
    void get_config_settings();
    //
    QString linux_terminal(QString &request);
    QJsonObject main_json_file;
    void gminer_json_parcer();
    //void lolminer_json_parcer();

private slots:
    void set_json(QJsonObject);
};

#endif // GPU_COLLECTOR_H
