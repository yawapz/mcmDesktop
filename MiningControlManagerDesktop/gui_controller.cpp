#include "gui_controller.h"
#include "gui_login_area.h"
#include "qapplication.h"
#include "qscreen.h"


gui_controller::gui_controller(QWidget *parent)
    : QWidget{parent}
{
    //emit signal_accept_host_data("127.0.0.1", 48048); // <--- connect!
    // Параметры отображения виджета
//-----------------------------------------------------------
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()/2 - 125, size.height()/2 - 110);
    this->setFocus();
    this->setFixedSize(220,240);
//-----------------------------------------------------------
    this->login_form = new gui_login_area(this);
    QObject::connect(login_form, SIGNAL(signal_login(QString,QString)), this, SIGNAL(signal_login(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString, QString)), login_form, SIGNAL(signal_send_answer_resault(QString, QString)), Qt::UniqueConnection);
    QObject::connect(login_form, SIGNAL(signal_get_user_data(QString)), this, SIGNAL(signal_get_user_data(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_user_data(user_data)), login_form, SIGNAL(signal_send_user_data(user_data)), Qt::UniqueConnection);
    this->show();

    this->farm_list_form = new gui_farm_list_area();
    QObject::connect(this, &gui_controller::send_authorization_data, this->farm_list_form, &gui_farm_list_area::accept_authorization_data);
    QObject::connect(this, &gui_controller::send_authorization_data, this->farm_list_form, &gui_farm_list_area::build_interface);
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
    this->close();
    this->farm_list_form->show();

    QObject::connect(farm_list_form, SIGNAL(signal_create_new_worker(QString)), this, SIGNAL(signal_create_new_worker(QString)), Qt::UniqueConnection);
    QObject::connect(farm_list_form, SIGNAL(signal_delete_worker(QString)), this, SIGNAL(signal_delete_worker(QString)), Qt::UniqueConnection);
    QObject::connect(farm_list_form, SIGNAL(signal_delete_user(QString,QString)), this, SIGNAL(signal_delete_user(QString,QString)), Qt::UniqueConnection);
    QObject::connect(farm_list_form, SIGNAL(signal_change_user_data(QString,QString,QString,QString)), this, SIGNAL(signal_change_user_data(QString,QString,QString,QString)), Qt::UniqueConnection);
    QObject::connect(farm_list_form, SIGNAL(signal_get_user_data(QString)), this, SIGNAL(signal_get_user_data(QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_user_data(user_data)), farm_list_form, SIGNAL(signal_send_user_data(user_data)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString,QString)), farm_list_form, SIGNAL(signal_send_answer_resault(QString,QString)), Qt::UniqueConnection);

    login_form->deleteLater();
    reg_area->deleteLater();
}

void gui_controller::call_reg_form()
{
    this->reg_area = new gui_reg_area();
    QObject::connect(reg_area, SIGNAL(signal_create_new_user(QString,QString)), this, SIGNAL(signal_create_new_user(QString,QString)), Qt::UniqueConnection);
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString, QString)), reg_area, SIGNAL(signal_send_answer_resault(QString, QString)), Qt::UniqueConnection);
    this->close();
    this->reg_area->show();
}
