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
    bool status;
private:
    QFont fontt;
    QFont fontt2;
    unsigned short int count_gpu;
    void build_main_cont();
    void build_lay();
    void build_sec_1(user_data::WORKER&);
    void build_sec_2(user_data::WORKER&);
    void build_sec_3(user_data::WORKER&);
    void build_sec_4(user_data::WORKER&);

signals:
    void signal_inc_data(user_data::WORKER);

private slots:
    void slot_update_worker(user_data::WORKER);
};

#endif // GUI_FARM_LIST_WORKER_H
