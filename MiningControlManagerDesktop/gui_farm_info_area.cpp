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
    dataSender();
}

void gui_farm_info_area::find_widget(QString ID)
{
    for (auto& WORKER : this->data.getRIGS())
    {
        if(WORKER.ID == ID)
        {
            bool isF = false;
            for (int i = 0; i < idArr.size();  ++i)
            {
                if(idArr[i] == ID)
                {
                   widgetArr[i]->show();
                   isF = true;
                   break;
                }
            }
            if(!isF)
            {
                gui_farm_info_worker *RIG = new gui_farm_info_worker();
                QObject::connect(this, SIGNAL(signal_send_user_data(user_data::WORKER)), RIG, SIGNAL(signal_accept_user_data(user_data::WORKER)), Qt::UniqueConnection);
                QObject::connect(this, SIGNAL(signal_exit_prog()), RIG, SIGNAL(signal_exit_prog()));
                QObject::connect(RIG, SIGNAL(signal_close(QString)), this, SLOT(close_widget(QString)), Qt::UniqueConnection);
                emit signal_send_user_data(WORKER);
                QObject::disconnect(this, SIGNAL(signal_send_user_data(user_data::WORKER)), RIG, SIGNAL(signal_accept_user_data(user_data::WORKER)));
                widgetArr.push_back(RIG);
                idArr.push_back(ID);
                RIG->show();
            }
        }
    }
}

void gui_farm_info_area::close_widget(QString id)
{
    for (int i = 0; i < idArr.size(); ++i)
    {
        if(idArr[i] == id)
        {
            widgetArr.removeAt(i);
            idArr.removeAt(i);
            break;
        }
    }
}

void gui_farm_info_area::dataSender()
{
    for (auto& WORKER : this->data.getRIGS())
    {
        for (auto& iter : widgetArr)
        {
            if(iter->id == WORKER.ID)
            {
                iter->slot_accept_data(WORKER);
            }
        }
    }
}
