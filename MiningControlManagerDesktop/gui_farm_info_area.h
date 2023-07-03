#ifndef GUI_FARM_INFO_AREA_H
#define GUI_FARM_INFO_AREA_H

#include "user_data.h"
#include "gui_farm_info_worker.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QMap>
#include <thread>

class gui_farm_info_area : public QObject
{
    Q_OBJECT
public:
    explicit gui_farm_info_area(QObject *parent = nullptr);
    ~gui_farm_info_area();
signals:
    void signal_send_user_data(user_data::WORKER);
    void signal_accept_data(QString, QString, user_data);
    void signal_find_widget(QString);
    void signal_transfer_widget(QWidget*);
    void signal_exit_prog();

private slots:
    void accept_user_data(QString login, QString password, user_data new_data);
    void find_widget(QString);
    void close_widget(QString);

private:
    QString login;
    QString password;
    user_data data;
    QList<QPair<QString, QWidget*>> showArr;
};

#endif // GUI_FARM_INFO_AREA_H
