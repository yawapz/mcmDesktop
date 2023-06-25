#include "gui_farm_info_area.h"
//#include <QElapsedTimer>

gui_farm_info_area::gui_farm_info_area(QObject *parent)
    : QObject{parent}
{
    QObject::connect(this, SIGNAL(signal_accept_data(QString, QString, user_data)),
                     this, SLOT  (accept_user_data(QString, QString, user_data)));
    QObject::connect(this, SIGNAL(signal_find_widget(QString)),
                     this, SLOT  (find_widget(QString)));
}

void gui_farm_info_area::accept_user_data(QString login, QString password, user_data new_data)
{
    //QElapsedTimer t;
    //t.start();
    this->login = login;
    this->password = password;
    this->data = new_data;
    generate_widget_list();
    //qDebug() << t.elapsed();
}

void gui_farm_info_area::find_widget(QString ID)
{
    if(!this->widget_list.empty())
    {
        auto obj = this->widget_list.find(ID);

        if(obj != widget_list.end())
        {
            QObject::connect(this, SIGNAL(signal_exit_prog()), obj.value(), SIGNAL(signal_exit_prog()));
            obj.value()->show();
        }
    }
}

void gui_farm_info_area::generate_widget_list()
{
    for (auto& WORKER : this->data.getRIGS())
    {
        gui_farm_info_worker *RIG = new gui_farm_info_worker(WORKER);
        this->widget_list.insert(WORKER.ID, RIG);
    }
}
