#include "gui_farm_info_area.h"

gui_farm_info_area::gui_farm_info_area(QObject *parent)
    : QObject{parent}
{
    QObject::connect(this, SIGNAL(signal_accept_data(QString, QString, user_data)),
                     this, SLOT  (accept_user_data(QString, QString, user_data)));
    QObject::connect(this, SIGNAL(signal_find_widget(QString)),
                     this, SLOT  (find_widget(QString)));
}

gui_farm_info_area::~gui_farm_info_area()
{
}

void gui_farm_info_area::accept_user_data(QString login, QString password, user_data new_data)
{
    this->login = login;
    this->password = password;
    this->data = new_data;
}

void gui_farm_info_area::find_widget(QString ID)
{
    for (auto& WORKER : this->data.getRIGS())
    {
        if(WORKER.ID == ID)
        {
            bool isF = false;
            for (auto& iter : showArr)
            {
                if(iter.first == ID)
                {
                   isF = true;
                   break;
                }
            }
            if(!isF)
            {
                gui_farm_info_worker *RIG = new gui_farm_info_worker();
                QObject::connect(this, SIGNAL(signal_send_user_data(user_data::WORKER)), RIG, SIGNAL(signal_accept_user_data(user_data::WORKER)));
                QObject::connect(this, SIGNAL(signal_exit_prog()), RIG, SIGNAL(signal_exit_prog()));
                QObject::connect(RIG, SIGNAL(signal_close(QString)), this, SLOT(close_widget(QString)));
                emit signal_send_user_data(WORKER);
                RIG->show();
                QObject::disconnect(this, SIGNAL(signal_send_user_data(user_data::WORKER)), RIG, SIGNAL(signal_accept_user_data(user_data::WORKER)));
                showArr.push_back(QPair(ID, RIG));
            }
        }
    }
}

void gui_farm_info_area::close_widget(QString id)
{
    for (int i = 0; i < showArr.size(); ++i)
    {
        if(showArr[i].first == id)
        {
            showArr.removeAt(i);
            break;
        }
    }
}
