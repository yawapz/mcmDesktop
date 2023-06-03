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

signals:

};

#endif // GUI_FARM_LIST_WORKER_H
