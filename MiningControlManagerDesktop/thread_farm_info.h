#ifndef THREAD_FARM_INFO_H
#define THREAD_FARM_INFO_H

#include "gui_farm_info_area.h"
#include "user_data.h"

#include <QThread>
#include <QObject>
#include <QDebug>

class thread_farm_info : public QThread
{
    Q_OBJECT
public:
    explicit thread_farm_info(QObject *parent = nullptr);

signals:
    void signal_send_data(QString, QString, user_data);

protected:
    void run() override;

private:
    gui_farm_info_area* farm = nullptr;
};

#endif // THREAD_FARM_INFO_H
