#ifndef GUI_FARM_LIST_WORKER_H
#define GUI_FARM_LIST_WORKER_H

#include "user_data.h"

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QFont>

class gui_farm_list_worker : public QWidget
{
    Q_OBJECT
public:
    explicit gui_farm_list_worker(user_data::WORKER WORKER);
    ~gui_farm_list_worker();

    QString ID;
//private:
    QWidget *main_container;
    QHBoxLayout *lay;

    QWidget *sec_1;
    QHBoxLayout *sec_1_lay;
    QHBoxLayout *sec_2;
    QWidget *sec_3;
    QHBoxLayout *sec_3_lay;
    QHBoxLayout *sec_4;

    bool status;

    QLabel *name;
    QLabel *time;
    QLabel *miner;
    QLabel *S;
    QLabel *R;
    QLabel *ALG;
    QLabel *power;
    QLabel *fan_speed;
private:
    unsigned short int count_gpu;

signals:
    void signal_inc_data(user_data::WORKER);

private slots:
    void slot_update_worker(user_data::WORKER);
};

#endif // GUI_FARM_LIST_WORKER_H
