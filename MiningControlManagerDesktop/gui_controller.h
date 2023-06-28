#ifndef GUI_CONTROLLER_H
#define GUI_CONTROLLER_H

#include "gui_login_area.h"
//#include "gui_farm_info_area.h"
#include "gui_farm_list_area.h"
#include "gui_reg_area.h"

#include <QObject>
#include <QWidget>
#include <QVector>

class gui_controller : public QWidget
{
    Q_OBJECT
public:
    explicit gui_controller(QWidget *parent = nullptr);
    ~gui_controller();

private:
    QString login;
    QString password;
    user_data data;

    gui_login_area *login_form;
    gui_farm_list_area *farm_list_form;
    gui_reg_area *reg_area = nullptr;

    QVector<gui_farm_info_area> farm_info_gui_list;

signals:
    void send_authorization_data(QString, QString, user_data);
    void snd_new_data(QString, QString, user_data);
public slots:
    void accept_authorization_data(QString log, QString pw, user_data new_data);
    void call_farm_list_form();
    void call_reg_form();

private slots:
    void slot_reg_back();

signals:
    void signal_accept_host_data(QString, int);
    void signal_login(QString, QString);
    void signal_create_new_user(QString, QString);
    void signal_create_new_worker(QString);
    void signal_delete_worker(QString);
    void signal_get_user_data(QString);
    void signal_change_user_data(QString, QString, QString, QString);
    void signal_delete_user(QString, QString);

    void signal_send_answer_resault(QString, QString);
    void signal_send_user_data(user_data);
    void signal_soc_connected();
    void signal_disconnect();
};

#endif // GUI_CONTROLLER_H
