#ifndef DATA_BUILDER_TH_H
#define DATA_BUILDER_TH_H

#include "worker_data_builder.h"

#include <QThread>
#include <QObject>
#include <QTimer>

class data_builder_th : public QThread
{
    Q_OBJECT
public:
    explicit data_builder_th(QObject *parent = nullptr);
    ~data_builder_th();

private:

public slots:
    void run() override;

private slots:
signals:
    void signal_send_worker_data(WORKER);
    void signal_get_new_data();

};

#endif // DATA_BUILDER_TH_H
