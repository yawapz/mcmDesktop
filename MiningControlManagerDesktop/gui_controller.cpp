#include "gui_controller.h"
#include "gui_login_area.h"
#include "qapplication.h"
#include "qscreen.h"


gui_controller::gui_controller(QWidget *parent)
    : QWidget{parent}
{
    this->login_form = new gui_login_area();
    QObject::connect(login_form, SIGNAL(send_authorization_data_to_another_form(QString,QString,user_data)), this, SLOT(accept_authorization_data(QString,QString,user_data)));
    QObject::connect(login_form, SIGNAL(call_farm_list_form()), this, SLOT(call_farm_list_form()));
    QObject::connect(login_form, SIGNAL(call_reg_form()), this, SLOT(call_reg_form()));
    QObject::connect(login_form, SIGNAL(signal_disconnect()), this, SIGNAL(signal_disconnect()), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_soc_connected()), login_form, SIGNAL(signal_soc_connected()), Qt::UniqueConnection);
    QObject::connect(login_form, SIGNAL(signal_try_connect(QString,int)), this, SIGNAL(signal_accept_host_data(QString,int)), Qt::UniqueConnection);
    QObject::connect(login_form, SIGNAL(signal_login(QString,QString)), this, SIGNAL(signal_login(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString, QString)), login_form, SIGNAL(signal_send_answer_resault(QString, QString)), Qt::UniqueConnection);
    QObject::connect(login_form, SIGNAL(signal_get_user_data(QString)), this, SIGNAL(signal_get_user_data(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_user_data(user_data)), login_form, SIGNAL(signal_send_user_data(user_data)), Qt::UniqueConnection);
    login_form->show();

    this->farm_list_form = new gui_farm_list_area();
    QObject::connect(this, &gui_controller::send_authorization_data, this->farm_list_form, &gui_farm_list_area::accept_authorization_data, Qt::UniqueConnection);
    QObject::connect(this, &gui_controller::send_authorization_data, this->farm_list_form, &gui_farm_list_area::build_interface, Qt::UniqueConnection);
}

gui_controller::~gui_controller()
{
    login_form->deleteLater();
    farm_list_form->deleteLater();
    reg_area->deleteLater();
}

void gui_controller::accept_authorization_data(QString log, QString pw, user_data new_data)
{
    this->login = log;
    this->password = pw;
    this->data = new_data;
}

void gui_controller::call_farm_list_form()
{
    emit send_authorization_data(this->login, this->password, this->data);
    login_form->close();
    this->farm_list_form->show();

    QObject::connect(farm_list_form, SIGNAL(signal_create_new_worker(QString)), this, SIGNAL(signal_create_new_worker(QString)), Qt::UniqueConnection);
    QObject::connect(farm_list_form, SIGNAL(signal_delete_worker(QString)), this, SIGNAL(signal_delete_worker(QString)), Qt::UniqueConnection);
    QObject::connect(farm_list_form, SIGNAL(signal_delete_user(QString,QString)), this, SIGNAL(signal_delete_user(QString,QString)), Qt::UniqueConnection);
    QObject::connect(farm_list_form, SIGNAL(signal_change_user_data(QString,QString,QString,QString)), this, SIGNAL(signal_change_user_data(QString,QString,QString,QString)), Qt::UniqueConnection);
    QObject::connect(farm_list_form, SIGNAL(signal_get_user_data(QString)), this, SIGNAL(signal_get_user_data(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_user_data(user_data)), farm_list_form, SIGNAL(signal_send_user_data(user_data)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString,QString)), farm_list_form, SIGNAL(signal_send_answer_resault(QString,QString)), Qt::UniqueConnection);

    QObject::disconnect(this, &gui_controller::send_authorization_data, this->farm_list_form, &gui_farm_list_area::accept_authorization_data);
    QObject::disconnect(this, &gui_controller::send_authorization_data, this->farm_list_form, &gui_farm_list_area::build_interface);
    //login_form->deleteLater();
    //reg_area->deleteLater();
}

void gui_controller::call_reg_form()
{
    reg_area = new gui_reg_area();
    QObject::connect(reg_area, SIGNAL(signal_back()), this, SLOT(slot_reg_back()));
    QObject::connect(reg_area, SIGNAL(signal_create_new_user(QString,QString)), this, SIGNAL(signal_create_new_user(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString, QString)), reg_area, SIGNAL(signal_send_answer_resault(QString, QString)), Qt::UniqueConnection);
    login_form->hide();
    reg_area->show();
}

void gui_controller::slot_reg_back()
{
    reg_area->close();
    reg_area->deleteLater();
    login_form->show();
}
