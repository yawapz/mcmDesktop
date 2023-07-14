#ifndef WORKER_DATA_BUILDER_H
#define WORKER_DATA_BUILDER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "gpu_struct.cpp"
#include "worker_struct.cpp"
#include "config.h"
#include "requests_info/motherboard.h"
#include "requests_info/disk.h"
#include "requests_info/cpu.h"
#include "requests_info/mac.h"
#include "requests_info/ram.h"
#include "requests_info/ip.h"
#include "requests_info/kernel.h"
#include "requests_info/nvidia.h"
#include "requests_info/radeon.h"
#include "requests_info/load_average.h"
#include "requests_info/startup_timer.h"
#include "requests_info/gpu_collector.h"
#include "requests_info/miner_json_reader.h"

class worker_data_builder : public QObject
{
    Q_OBJECT
public:
    explicit worker_data_builder(QObject *parent = nullptr);
    ~worker_data_builder();
public slots:

private:
    WORKER worker;
    miner_json_reader *reader;
    QJsonObject json;
    void choice_parcer();
    void gminer_json_parcer();

    bool isIncMinerData;
    void dataControl();
signals:
    void signal_accept_json(QJsonObject);
    void signal_send_worker_data(WORKER);
    void signal_get_new_data();
private slots:
    void slot_transfer(QJsonObject);
    void get_new_data();
};

#endif // WORKER_DATA_BUILDER_H
