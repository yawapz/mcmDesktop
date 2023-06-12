#ifndef DATA_BUILDER_TH_H
#define DATA_BUILDER_TH_H

#include "worker_data_builder.h"

#include <QThread>
#include <QObject>

class data_builder_th : public QThread
{
    Q_OBJECT
public:
    data_builder_th();


public slots:
    void run() override;

signals:
    void signal_send_worker_data(WORKER);

};

#endif // DATA_BUILDER_TH_H
