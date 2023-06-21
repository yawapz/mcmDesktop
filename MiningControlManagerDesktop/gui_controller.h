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
    void slot_acceppt_data_and_start_new_widget(QString, QString, user_data);

};

#endif // GUI_CONTROLLER_H
