#include "gui_controller.h"
#include "gui_login_area.h"
#include "qapplication.h"
#include "qscreen.h"


gui_controller::gui_controller(QWidget *parent)
    : QWidget{parent}
{
    // Параметры отображения виджета
//-----------------------------------------------------------
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()/2 - 125, size.height()/2 - 110);
    this->setFocus();
    this->setFixedSize(220,240);
//-----------------------------------------------------------
    this->login_form = new gui_login_area(this);
    this->show();

    this->farm_list_form = new gui_farm_list_area();
    QObject::connect(this, &gui_controller::send_authorization_data, this->farm_list_form, &gui_farm_list_area::accept_authorization_data);
    QObject::connect(this, &gui_controller::send_authorization_data, this->farm_list_form, &gui_farm_list_area::build_interface);
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
}

void gui_controller::call_reg_form()
{
    this->reg_area = new gui_reg_area();
    this->close();
    this->reg_area->show();
}
