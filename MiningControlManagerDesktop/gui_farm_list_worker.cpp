#include "gui_farm_list_worker.h"

gui_farm_list_worker::gui_farm_list_worker(user_data::WORKER WORKER)
{
    QObject::connect(this, SIGNAL(signal_inc_data(user_data::WORKER)), this, SLOT(slot_update_worker(user_data::WORKER)));
    this->ID = WORKER.ID;
    this->status = WORKER.status;
    this->count_gpu = WORKER.devices.size();

    QFont font = this->font();
    font.setPixelSize(14);
    font.setFamily("Open Sans,Segoe UI,HelveticaNeue-Light,sans-serif");
    QFont font2 = this->font();
    font2.setPixelSize(11);
    font2.setFamily("Open Sans,Segoe UI,HelveticaNeue-Light,sans-serif");
    //QFont fonr3 = this->font();

//-----------------------------------------------------------------------------------------------------------
    main_container = new QWidget();
    if(!status)
        main_container->setStyleSheet("QWidget {background-color: #262b31; border: none; border-radius: 0px};");
    else
        main_container->setStyleSheet("QWidget {background-color: #363d45; border: none; border-radius: 0px};");
    main_container->setFont(font);
    main_container->setFixedSize(1178, 23);
    main_container->setCursor(Qt::PointingHandCursor);
//-----------------------------------------------------------------------------------------------------------
    lay = new QHBoxLayout();
    lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
    lay->setSpacing(0);
    lay->setContentsMargins(0,0,0,0);
//-----------------------------------------------------------------------------------------------------------
    sec_1 = new QWidget();
    sec_1->setFixedSize(220, 19);
    sec_1->setStyleSheet("background-color: transparent; color: white");
//-----------------------------------------------------------------------------------------------------------
    sec_1_lay = new QHBoxLayout();
    sec_1_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
    sec_1_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
    sec_1_lay->setSpacing(0);
    sec_1_lay->setContentsMargins(0,0,0,0);
//-----------------------------------------------------------------------------------------------------------
    name = new QLabel();
    name->setText(WORKER.name);
    name->setFixedSize(160, 19);
    name->setContentsMargins(6,0,0,0);
    name->setStyleSheet("background-color: transparent; color: white");
    sec_1_lay->addWidget(name, Qt::AlignmentFlag::AlignLeft);
//-----------------------------------------------------------------------------------------------------------
    // Преобразовать время

       long long time_seconds = WORKER.uptime;
       if(!status)
       {
            time_seconds = WORKER.last_online;
       }
       int seconds = time_seconds % 60;
       int minutes = (time_seconds / 60) % 60;
       int hours = (time_seconds / 60 / 60);
       int days = (time_seconds / 60 / 60 / 24);
       QString time_normal_format = "";
       if(days > 0)
       {
           time_normal_format = QString::number(days) + "d " + QString::number(hours % 24) + "h";
       }
       if(days == 0 && hours > 0)
       {
           time_normal_format = QString::number(hours) + "h " + QString::number(minutes % 60) + "m";
       }
       if(days == 0 && hours == 0)
       {
           time_normal_format = QString::number(minutes) + "m " + QString::number(seconds % 60) + "s";
       }
       if(days == 0 && hours == 0 && minutes == 0)
       {
           time_normal_format = QString::number(seconds) + "s";
       }

    time = new QLabel();
    time->setText(time_normal_format);
    time->setFixedSize(55, 19);
    time->setFont(font2);
    time->setStyleSheet("background-color: transparent; color: #818E9C");
    sec_1_lay->addWidget(time, Qt::AlignmentFlag::AlignRight);
    sec_1->setLayout(sec_1_lay);
    lay->addWidget(sec_1);
    main_container->setLayout(lay);
//-----------------------------------------------------------------------------------------------------------
    sec_2 = new QHBoxLayout();
//-----------------------------------------------------------------------------------------------------------
    miner = new QLabel();
    long double keff = double(WORKER.total_accepted_shares + WORKER.total_accepted_shares2) / ((WORKER.total_rejected_shares + WORKER.total_rejected_shares2)
                                                                                            + (WORKER.total_stale_shares + WORKER.total_stale_shares2));
    if(WORKER.miner.length() > 0)
    {
        if(keff > 100)
        {
            keff = 100;
            miner->setText(WORKER.miner + " " + QString::number(int(keff)) + '%');
        }
        else if(keff < 100)
        {
            miner->setText(WORKER.miner + " " + QString::number(keff, 'f', 2) + '%');
        }
        else
        {
            miner->setText(WORKER.miner);
        }

    }
    miner->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");
    miner->setFixedSize(125,19);
//-----------------------------------------------------------------------------------------------------------
    S = new QLabel();
    if((WORKER.total_stale_shares + WORKER.total_stale_shares2) > 0)
    {
        S->setText(QString::number(WORKER.total_stale_shares + WORKER.total_stale_shares2));
    }
    S->setStyleSheet("background-color: transparent; color: #FFAE00; font-size: 12px");
    S->setFixedSize(25,19);
    R = new QLabel();
    if((WORKER.total_invalid_shares + WORKER.total_invalid_shares2) > 0)
    {
        R->setText(QString::number(WORKER.total_invalid_shares + WORKER.total_invalid_shares2));
    }
    R->setStyleSheet("background-color: transparent; color: #FF3733; font-size: 12px");
    R->setFixedSize(25,19);
//-----------------------------------------------------------------------------------------------------------
    ALG = new QLabel();
    ALG->setFixedSize(255, 19);
    ALG->setFont(font2);
    ALG->setStyleSheet("background-color: transparent; color: white");
    ALG->setContentsMargins(10,0,0,0);
    long double ALG_1 = 0;
    long double ALG_2 = 0;
    for (auto& GPU : WORKER.devices)
    {
        ALG_1 += GPU.speed;
        ALG_2 += GPU.speed2;
    }
    QString value = "";
    QString value2 = "";
    long double int_speed = ALG_1;
    long double int_speed2 = ALG_2;
    //Вынос в метод
    if(ALG_1 >= 1000 && ALG_1 < 1000000)
    {
        int_speed /= 1000;
        value = " kH";
    }
    else if(ALG_1 >= 100000 && ALG_1 < 1000000000)
    {
        int_speed /= 1000000;
        value = " Mh";
    }
    else if(ALG_1 >= 100000000 && ALG_1 < 1000000000000)
    {
        int_speed /= 1000000000;
        value = " Gh";
    }
    else
    {
        value = " H";
    }
    if(ALG_2 >= 1000 && ALG_2 < 1000000)
    {
        int_speed2 /= 1000;
        value2 = " kH";
    }
    else if(ALG_2 >= 100000 && ALG_2 < 1000000000)
    {
        int_speed2 /= 1000000;
        value2 = " Mh";
    }
    else if(ALG_2 >= 100000000 && ALG_2 < 1000000000000)
    {
        int_speed2 /= 1000000000;
        value2 = " Gh";
    }
    else
    {
        value2 = " H";
    }
    QString label_insert_value = "";
    if(ALG_2 > 0)
    {
        if (value == " Gh")
        {
            label_insert_value += WORKER.algorithm + " " + QString::number(int_speed, 'f', 2) + value + " " + WORKER.algorithm2
                                                   + " " + QString::number(int_speed2, 'f', 1) + value2;
        }
        else if (value == " Gh" && value2 == " Gh")
        {
            label_insert_value += WORKER.algorithm + " " + QString::number(int_speed, 'f', 2) + value + " " + WORKER.algorithm2
                                                   + " " + QString::number(int_speed2, 'f', 2) + value2;
        }
        else if (value2 == " Gh")
        {
            label_insert_value += WORKER.algorithm + " " + QString::number(int_speed, 'f', 1) + value + " " + WORKER.algorithm2
                                                   + " " + QString::number(int_speed2, 'f', 2) + value2;
        }
        else
        {
            label_insert_value += WORKER.algorithm + " " + QString::number(int_speed, 'f', 1) + value + " " + WORKER.algorithm2
                                                   + " " + QString::number(int_speed2, 'f', 1) + value2;
        }
    }
    else if (ALG_1 > 0 && ALG_2 == 0)
    {
        if (value == " Gh")
        {
            label_insert_value += WORKER.algorithm + " " + QString::number(int_speed, 'f', 2) + value;
        }
        else
        {
            label_insert_value += WORKER.algorithm + " " + QString::number(int_speed, 'f', 1) + value;
        }
    }
    else
    {
        label_insert_value += "n/a";
    }
    ALG->setText(label_insert_value);
//-----------------------------------------------------------------------------------------------------------
    sec_2->addWidget(ALG, Qt::AlignmentFlag::AlignLeft);
    sec_2->addWidget(miner, Qt::AlignmentFlag::AlignLeft);
    sec_2->addWidget(S, Qt::AlignmentFlag::AlignRight);
    sec_2->addWidget(R, Qt::AlignmentFlag::AlignRight);
    if(status)
        lay->addLayout(sec_2);
//-----------------------------------------------------------------------------------------------------------
    sec_3 = new QWidget();
    sec_3->setFixedSize(270, 19);
    sec_3->setStyleSheet("background-color: transparent");
    sec_3->setContentsMargins(0,0,0,0);
//-----------------------------------------------------------------------------------------------------------
    sec_3_lay = new QHBoxLayout();
    sec_3_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    sec_3_lay->setSpacing(2);
    sec_3_lay->setContentsMargins(0,0,0,0);
//-----------------------------------------------------------------------------------------------------------
    for (auto &GPU : WORKER.devices)
    {
        QWidget *unit = new QWidget();
        unit->setFixedSize(11,11);
        unit->setContentsMargins(0,0,0,0);
        // отлов ошибок, каким образом пока непонято
        if(true)
        {
            unit->setStyleSheet("background-color: #84BF40; border-radius: 0px");
        }
        else
        {
            unit->setStyleSheet("background-color: transparent; border: 2px; border-color: #FFAE00");
        }

        sec_3_lay->addWidget(unit);
    }
    sec_3->setLayout(sec_3_lay);
    if(status)
        lay->addWidget(sec_3, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
//-----------------------------------------------------------------------------------------------------------
    sec_4 = new QHBoxLayout();
    sec_4->setAlignment(Qt::AlignmentFlag::AlignRight);
    sec_4->setContentsMargins(2,0,2,0);
    sec_4->setSpacing(0);
//-----------------------------------------------------------------------------------------------------------
    //-------------------------------------------------
    double rig_power = 0;
    int cooler_max_speed = 0;
    power = new QLabel();
    for (auto &iter : WORKER.devices)
    {
        rig_power += iter.power_usage;
        if(iter.fan_speed > cooler_max_speed)
        {
            cooler_max_speed = iter.fan_speed;
        }
    }
    if(rig_power > 0)
    {
        QString power_value = "";
        //Рассчёт для перевода в W - kW
        if(rig_power > 1000)
        {
            rig_power /= 1000;
            power_value = " kW";
            power->setText(QString::number(rig_power, 'f', 2) + power_value);
        }
        else
        {
            power_value = " W";
            power->setText(QString::number(rig_power, 'f', 1) + power_value);
        }
    }

    QPixmap *icon = new QPixmap("res/consumption.svg");
    QPainter qp = QPainter(icon);
    qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
    qp.fillRect(icon->rect(), QColor(129, 142, 156));
    qp.end();

    power->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");
    power->setFixedSize(55,19);
    //-------------------------------------------------
    QLabel *icon_widget = new QLabel();
    icon_widget->setFixedSize(16,16);
    icon_widget->setContentsMargins(2,0,2,0);
    icon_widget->setPixmap(*icon);
    icon_widget->setScaledContents(true);
    icon_widget->setStyleSheet("background-color: transparent;");
    //-------------------------------------------------
    fan_speed = new QLabel();
    fan_speed->setContentsMargins(3,0,3,0);
    fan_speed->setText(QString::number(cooler_max_speed) + '%');
    QPixmap *icon_fan = new QPixmap("res/cooler.svg");
    QPainter qp_fan = QPainter(icon_fan);
    qp_fan.setCompositionMode(QPainter::CompositionMode_SourceIn);
    qp_fan.fillRect(icon_fan->rect(), QColor(129, 142, 156));
    qp_fan.end();

    fan_speed->setFixedSize(40,19);
    fan_speed->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");
    //-------------------------------------------------
    QLabel *icon_fan_widget = new QLabel();
    icon_fan_widget->setFixedSize(21,21);
    icon_fan_widget->setContentsMargins(2,0,2,0);
    icon_fan_widget->setPixmap(*icon_fan);
    icon_fan_widget->setScaledContents(true);
    icon_fan_widget->setStyleSheet("background-color: transparent;");
    //-------------------------------------------------
    sec_4->addWidget(icon_fan_widget, Qt::AlignmentFlag::AlignRight);
    sec_4->addWidget(fan_speed, Qt::AlignmentFlag::AlignRight);
    sec_4->addWidget(icon_widget, Qt::AlignmentFlag::AlignRight);
    sec_4->addWidget(power, Qt::AlignmentFlag::AlignRight);
    if(status)
        lay->addLayout(sec_4, Qt::AlignmentFlag::AlignRight);
//-----------------------------------------------------------------------------------------------------------
    if(!status)
    {
        QHBoxLayout *sec = new QHBoxLayout();
        sec->setAlignment(Qt::AlignmentFlag::AlignRight);
        sec->setContentsMargins(0,0,52,0);
        sec->setSpacing(0);

        QPixmap *icon_offline = new QPixmap("res/offline.svg");
        QPainter qp_icon_offline = QPainter(icon_offline);
        qp_icon_offline.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp_icon_offline.fillRect(icon_offline->rect(), QColor(238, 240, 242));
        qp_icon_offline.end();

        QLabel *icon_offline_widget = new QLabel();
        icon_offline_widget->setAlignment(Qt::AlignmentFlag::AlignRight);
        icon_offline_widget->setFixedSize(22,18);
        icon_offline_widget->setContentsMargins(0,0,4,0);
        icon_offline_widget->setPixmap(*icon_offline);
        icon_offline_widget->setScaledContents(true);
        icon_offline_widget->setStyleSheet("background-color: transparent;");

        sec->addWidget(icon_offline_widget);
        lay->addLayout(sec);
    }
}

gui_farm_list_worker::~gui_farm_list_worker()
{
    main_container->deleteLater();
    lay->deleteLater();
    sec_1->deleteLater();
    sec_1_lay->deleteLater();
    sec_2->deleteLater();
    sec_3->deleteLater();
    sec_3_lay->deleteLater();
    sec_4->deleteLater();
    name->deleteLater();
    time->deleteLater();
    miner->deleteLater();
    S->deleteLater();
    R->deleteLater();
    ALG->deleteLater();
    power->deleteLater();
    fan_speed->deleteLater();
}

void gui_farm_list_worker::slot_update_worker(user_data::WORKER inc)
{

    if(inc.ID == this->ID)
    {
        if(this->count_gpu != inc.devices.size())
        {
            QWidget *unit = new QWidget();
            unit->setFixedSize(11,11);
            unit->setContentsMargins(0,0,0,0);
            // отлов ошибок, каким образом пока непонято
            if(true)
            {
                unit->setStyleSheet("background-color: #84BF40; border-radius: 0px");
            }
            else
            {
                unit->setStyleSheet("background-color: transparent; border: 2px; border-color: #FFAE00");
            }
            if(this->count_gpu > inc.devices.size())
            {
                for (int i = 0; i < (this->count_gpu - inc.devices.size()); ++i)
                {
                    sec_3_lay->removeWidget(unit);
                }

            }
            else if (this->count_gpu < inc.devices.size())
            {
                for (int i = 0; i < (inc.devices.size() - this->count_gpu); ++i)
                {
                    sec_3_lay->addWidget(unit);
                }
            }
        }

        this->name->setText(inc.name);
        long long time_seconds = inc.uptime;
        if(!inc.status)
        {
             time_seconds = inc.last_online;
        }
        int seconds = time_seconds % 60;
        int minutes = (time_seconds / 60) % 60;
        int hours = (time_seconds / 60 / 60);
        int days = (time_seconds / 60 / 60 / 24);
        QString time_normal_format = "";
        if(days > 0)
        {
            time_normal_format = QString::number(days) + "d " + QString::number(hours % 24) + "h";
        }
        if(days == 0 && hours > 0)
        {
            time_normal_format = QString::number(hours) + "h " + QString::number(minutes % 60) + "m";
        }
        if(days == 0 && hours == 0)
        {
            time_normal_format = QString::number(minutes) + "m " + QString::number(seconds % 60) + "s";
        }
        if(days == 0 && hours == 0 && minutes == 0)
        {
            time_normal_format = QString::number(seconds) + "s";
        }
        this->time->setText(time_normal_format);
        long double keff = double(inc.total_accepted_shares + inc.total_accepted_shares2) / ((inc.total_rejected_shares + inc.total_rejected_shares2)
                                                                                                + (inc.total_stale_shares + inc.total_stale_shares2));
        if(inc.miner.length() > 0)
        {
            if(keff > 100)
            {
                keff = 100;
                miner->setText(inc.miner + " " + QString::number(int(keff)) + '%');
            }
            else if(keff < 100)
            {
                miner->setText(inc.miner + " " + QString::number(keff, 'f', 2) + '%');
            }
            else
            {
                miner->setText(inc.miner);
            }

        }
        else
        {
             this->miner->setText("");
        }
        if((inc.total_stale_shares + inc.total_stale_shares2) > 0)
            this->S->setText(QString::number(inc.total_stale_shares + inc.total_stale_shares2));
        else
            this->S->setText("");
        if((inc.total_invalid_shares + inc.total_invalid_shares2) > 0)
            this->R->setText(QString::number(inc.total_invalid_shares + inc.total_invalid_shares2));
        else
            this->R->setText("");

        {
            long double ALG_1 = 0;
            long double ALG_2 = 0;
            for (auto& GPU : inc.devices)
            {
                ALG_1 += GPU.speed;
                ALG_2 += GPU.speed2;
            }
            QString value = "";
            QString value2 = "";
            long double int_speed = ALG_1;
            long double int_speed2 = ALG_2;
            //Вынос в метод
            if(ALG_1 >= 1000 && ALG_1 < 1000000)
            {
                int_speed /= 1000;
                value = " kH";
            }
            else if(ALG_1 >= 100000 && ALG_1 < 1000000000)
            {
                int_speed /= 1000000;
                value = " Mh";
            }
            else if(ALG_1 >= 100000000 && ALG_1 < 1000000000000)
            {
                int_speed /= 1000000000;
                value = " Gh";
            }
            else
            {
                value = " H";
            }
            if(ALG_2 >= 1000 && ALG_2 < 1000000)
            {
                int_speed2 /= 1000;
                value2 = " kH";
            }
            else if(ALG_2 >= 100000 && ALG_2 < 1000000000)
            {
                int_speed2 /= 1000000;
                value2 = " Mh";
            }
            else if(ALG_2 >= 100000000 && ALG_2 < 1000000000000)
            {
                int_speed2 /= 1000000000;
                value2 = " Gh";
            }
            else
            {
                value2 = " H";
            }
            QString label_insert_value = "";
            if(ALG_2 > 0)
            {
                if (value == " Gh")
                {
                    label_insert_value += inc.algorithm + " " + QString::number(int_speed, 'f', 2) + value + " " + inc.algorithm2
                                                           + " " + QString::number(int_speed2, 'f', 1) + value2;
                }
                else if (value == " Gh" && value2 == " Gh")
                {
                    label_insert_value += inc.algorithm + " " + QString::number(int_speed, 'f', 2) + value + " " + inc.algorithm2
                                                           + " " + QString::number(int_speed2, 'f', 2) + value2;
                }
                else if (value2 == " Gh")
                {
                    label_insert_value += inc.algorithm + " " + QString::number(int_speed, 'f', 1) + value + " " + inc.algorithm2
                                                           + " " + QString::number(int_speed2, 'f', 2) + value2;
                }
                else
                {
                    label_insert_value += inc.algorithm + " " + QString::number(int_speed, 'f', 1) + value + " " + inc.algorithm2
                                                           + " " + QString::number(int_speed2, 'f', 1) + value2;
                }
            }
            else if (ALG_1 > 0 && ALG_2 == 0)
            {
                if (value == " Gh")
                {
                    label_insert_value += inc.algorithm + " " + QString::number(int_speed, 'f', 2) + value;
                }
                else
                {
                    label_insert_value += inc.algorithm + " " + QString::number(int_speed, 'f', 1) + value;
                }
            }
            else
            {
                label_insert_value += "n/a";
            }
            ALG->setText(label_insert_value);
        }

        {
            double rig_power = 0;
            int cooler_max_speed = 0;
            for (auto &iter : inc.devices)
            {
                rig_power += iter.power_usage;
                if(iter.fan_speed > cooler_max_speed)
                {
                    cooler_max_speed = iter.fan_speed;
                }
            }
            fan_speed->setText(QString::number(cooler_max_speed) + '%');
            if(rig_power > 0)
            {
                QString power_value = "";
                //Рассчёт для перевода в W - kW
                if(rig_power > 1000)
                {
                    rig_power /= 1000;
                    power_value = " kW";
                    power->setText(QString::number(rig_power, 'f', 2) + power_value);
                }
                else
                {
                    power_value = " W";
                    power->setText(QString::number(rig_power, 'f', 1) + power_value);
                }
            }
        }

        if(!(status == inc.status))
        {
            if(status) // old status is online
            {
                main_container->setStyleSheet("QWidget {background-color: #262b31; border: none; border-radius: 0px};");
                lay->removeItem(sec_2);
                lay->removeWidget(sec_3);
                lay->removeItem(sec_4);
            }
            else // old status is offline
            {
                main_container->setStyleSheet("QWidget {background-color: #363d45; border: none; border-radius: 0px};");
                lay->addLayout(sec_2);
                lay->addWidget(sec_3, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
                lay->addLayout(sec_4, Qt::AlignmentFlag::AlignRight);
            }
        }
        status = inc.status; // new status
    }
}
