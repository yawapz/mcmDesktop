#include "gui_farm_info_worker.h"
#include "qevent.h"

gui_farm_info_worker::gui_farm_info_worker()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    main_lay = new QVBoxLayout();
    QObject::connect(this, SIGNAL(signal_accept_user_data(user_data::WORKER)),this, SLOT(slot_accept_data(user_data::WORKER)));
    QObject::connect(this, SIGNAL(signal_exit_prog()), this, SLOT(slot_exit_prog()));

    // Параметры отображения виджета
//-----------------------------------------------------------
    this->setFixedSize(1280,1024);
    this->main_lay->setContentsMargins(0,0,0,0);
    this->main_lay->setSpacing(0);
//    QScreen *screen = QApplication::screens().at(0);
//    QSize size = screen->availableSize();
//    this->move(size.width()/2 - 640, size.height()/2 - 512);
    this->setStyleSheet("background-color: #22262b;");
    this->main_lay->setAlignment(Qt::AlignmentFlag::AlignTop);
//-----------------------------------------------------------

}

gui_farm_info_worker::~gui_farm_info_worker()
{
    for (auto& iter : gpu_widget_container)
    {
        delete iter;
    }
    gpu_widget_container.clear();

//    main_lay->deleteLater();
//    top_small_block->deleteLater();
//    top_status_block->deleteLater();
//    top_bottom_info_block->deleteLater();
//    card_counting_small_block->deleteLater();
//    mid_block->deleteLater();
//    bottom_block->deleteLater();

    delete main_lay;
    delete top_small_block;
    delete top_status_block;
    delete top_bottom_info_block;
    delete card_counting_small_block;
    delete mid_block;
    delete bottom_block;
}

void gui_farm_info_worker::build_top_small_block(user_data::WORKER &WORKER)
{
    top_small_block = new QWidget();
    QHBoxLayout *lay = new QHBoxLayout();
    //-----------------------------------------------------------
    QHBoxLayout *left = new QHBoxLayout();
    left->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    QLabel *worker_name = new QLabel(WORKER.name);
    worker_name->setStyleSheet("background-color: transparent; color: white; font-size: 18px");
    left->addWidget(worker_name);
    if(!WORKER.status)
    {
        QPixmap *icon_offline = new QPixmap("res/offline.svg");
        QPainter qp_icon_offline = QPainter(icon_offline);
        qp_icon_offline.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp_icon_offline.fillRect(icon_offline->rect(), QColor(238, 240, 242));
        qp_icon_offline.end();

        QLabel *icon_offline_widget = new QLabel();
        icon_offline_widget->setFixedSize(30,25);
        icon_offline_widget->setContentsMargins(0,0,4,0);
        icon_offline_widget->setPixmap(*icon_offline);
        icon_offline_widget->setScaledContents(true);
        icon_offline_widget->setStyleSheet("background-color: transparent;");

        left->addWidget(icon_offline_widget);
    }
    //-----------------------------------------------------------
    lay->addLayout(left);

    if(WORKER.status)
    {
        QHBoxLayout *right = new QHBoxLayout();
        right->setAlignment(Qt::AlignmentFlag::AlignRight);

        QHBoxLayout *LR = new QHBoxLayout();
        LR->setContentsMargins(0,0,5,0);
        LR->setSpacing(0);
        LR->setAlignment(Qt::AlignmentFlag::AlignRight);
        QLabel *LA = new QLabel("Load Average");
        LA->setContentsMargins(0,0,5,0);
        LA->setStyleSheet("background-color: transparent; color: white; font-size: 14px");
        LA->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);
        QLabel *LA1 = new QLabel(WORKER.LA1);
        if(WORKER.LA1.toDouble() >= 0.8)
            LA1->setStyleSheet("background-color: transparent; color: #FF3733; font-size: 16px");
        else
            LA1->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 16px");
        LA1->setAlignment( Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        LA1->setFixedSize(35,19);
        LA1->setContentsMargins(2,0,0,0);

        QLabel *LA5 = new QLabel(WORKER.LA5);
        if(WORKER.LA5.toDouble() >= 0.8)
            LA5->setStyleSheet("background-color: transparent; color: #FF3733; font-size: 16px");
        else
            LA5->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 16px");
        LA5->setAlignment( Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        LA5->setFixedSize(35,19);
        LA5->setContentsMargins(2,0,0,0);

        QLabel *LA15 = new QLabel(WORKER.LA15);
        if(WORKER.LA15.toDouble() >= 0.8)
            LA15->setStyleSheet("background-color: transparent; color: #FF3733; font-size: 16px");
        else
            LA15->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 16px");
        LA15->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        LA15->setFixedSize(35,19);
        LA15->setContentsMargins(2,0,0,0);

        QLabel *min1 = new QLabel("1min");
        min1->setContentsMargins(0,0,0,0);
        min1->setStyleSheet("background-color: transparent; color: white; font-size: 10px");
        QLabel *min5 = new QLabel("5min");
        min5->setContentsMargins(0,0,0,0);
        min5->setStyleSheet("background-color: transparent; color: white; font-size: 10px");
        QLabel *min15 = new QLabel("15min");
        min15->setContentsMargins(0,0,0,0);
        min15->setStyleSheet("background-color: transparent; color: white; font-size: 10px");

        LR->addWidget(LA);
        LR->addWidget(LA1);
        LR->addWidget(min1);
        LR->addWidget(LA5);
        LR->addWidget(min5);
        LR->addWidget(LA15);
        LR->addWidget(min15);

        right->addLayout(LR);
        //-----------------------------------------------------------
        QHBoxLayout *RR = new QHBoxLayout();
        RR->setContentsMargins(0,0,30,0);
        RR->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);
        RR->setSpacing(0);

        double rig_power = 0;
        QLabel *power = new QLabel();
        power->setStyleSheet("background-color: transparent; color: #7bbeea; font-size: 14px");
        power->setFixedSize(75,19);
        for (auto &iter : WORKER.devices)
        {
            rig_power += iter.power_usage;
        }
        if(rig_power > 0)
        {
            QString power_value = "";
            //Рассчёт для перевода в W - kW
            if(rig_power > 1000)
            {
                rig_power /= 1000;
                power_value = " kWatt";
                power->setText(QString::number(rig_power, 'f', 2) + power_value);
            }
            else
            {
                power_value = " Watt";
                power->setText(QString::number((int)rig_power) + power_value);
            }
        }

        QPixmap *icon = new QPixmap("res/consumption.svg");
        QPainter qp = QPainter(icon);
        qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp.fillRect(icon->rect(), QColor(123, 190, 234));
        qp.end();

        QLabel *icon_widget = new QLabel();
        icon_widget->setFixedSize(20,20);
        icon_widget->setContentsMargins(2,0,2,0);
        icon_widget->setPixmap(*icon);
        icon_widget->setScaledContents(true);
        icon_widget->setStyleSheet("background-color: transparent;");

        RR->addWidget(icon_widget);
        RR->addWidget(power);

        right->addLayout(RR);

        lay->addLayout(right);
    }
    //-----------------------------------------------------------
    top_small_block->setLayout(lay);
}

void gui_farm_info_worker::build_top_status_block(user_data::WORKER &WORKER)
{
    this->top_status_block = new QWidget();
    this->top_status_block->setFixedSize(1280,78);
    this->top_status_block->setStyleSheet("background-color: #16191d;");
    this->top_status_block->setContentsMargins(0,0,0,0);
    QHBoxLayout *lay = new QHBoxLayout();
    lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);
    //-----------------------------------------------------------
    QWidget *v_widget = new QWidget();
    v_widget->setFixedSize(410, 78);
    v_widget->setContentsMargins(0,0,0,0);
    QVBoxLayout *v_lay = new QVBoxLayout();
    v_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    v_lay->setContentsMargins(0,0,0,0);
    v_lay->setSpacing(0);
    QHBoxLayout *hlay1 = new QHBoxLayout();
    hlay1->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    hlay1->setContentsMargins(0,0,0,0);
    hlay1->setSpacing(0);
    QHBoxLayout *hlay2 = new QHBoxLayout();
    hlay2->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    hlay2->setContentsMargins(0,0,0,0);
    hlay2->setSpacing(2);
    QHBoxLayout *hlay3 = new QHBoxLayout();
    hlay3->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    hlay3->setContentsMargins(0,0,0,0);
    hlay3->setSpacing(0);

    QWidget *w1 = new QWidget();
    w1->setContentsMargins(0,0,0,0);
    w1->setFixedHeight(30);
    w1->setStyleSheet("background-color: transparent; color: white; font-size: 14px");
    QWidget *w2 = new QWidget();
    w2->setContentsMargins(0,0,0,0);
    w2->setFixedHeight(18);
    w2->setStyleSheet("background-color: #2f353c; color: white; font-size: 12px; border-radius: 0px;");
    QWidget *w3 = new QWidget();
    w3->setContentsMargins(0,0,0,0);
    w3->setFixedHeight(30);
    w3->setStyleSheet("background-color: transparent; color: white; font-size: 14px");
    //---------------------------w2------------------------------
    QLabel *miner = new QLabel(WORKER.miner);
    miner->setContentsMargins(20,0,0,0);
    QLabel *Lkeff = new QLabel();
    Lkeff->setFixedWidth(60);
    Lkeff->setContentsMargins(10,0,0,0);
    QLabel *A = new QLabel("A " + QString::number(WORKER.total_accepted_shares + WORKER.total_accepted_shares2));
    A->setFixedWidth(50);
    A->setContentsMargins(0,0,0,0);
    if((WORKER.total_accepted_shares + WORKER.total_accepted_shares2) == 0)
        A->setStyleSheet("color: transparent");
    else
        A->setStyleSheet("color: white");
    QLabel *S = new QLabel("S " + QString::number(WORKER.total_stale_shares + WORKER.total_stale_shares2));
    S->setFixedWidth(35);
    S->setContentsMargins(0,0,0,0);
    if((WORKER.total_stale_shares + WORKER.total_stale_shares2) == 0)
        S->setStyleSheet("color: transparent");
    else
        S->setStyleSheet("color: #FFAE00");
    QLabel *R = new QLabel("R " + QString::number(WORKER.total_rejected_shares + WORKER.total_rejected_shares2));
    R->setFixedWidth(35);
    R->setContentsMargins(0,0,0,0);
    if((WORKER.total_rejected_shares + WORKER.total_rejected_shares2) == 0)
        R->setStyleSheet("color: transparent");
    else
        R->setStyleSheet("color: #FF3733");
    QLabel *I = new QLabel("I " + QString::number(WORKER.total_invalid_shares + WORKER.total_invalid_shares2));
    I->setFixedWidth(35);
    I->setContentsMargins(0,0,0,0);
    if((WORKER.total_invalid_shares + WORKER.total_invalid_shares2) == 0)
        I->setStyleSheet("color: transparent");
    else
        I->setStyleSheet("color: #FF3733");
    long double keff = double(WORKER.total_accepted_shares + WORKER.total_accepted_shares2) / ((WORKER.total_rejected_shares + WORKER.total_rejected_shares2)
                                                                                            + (WORKER.total_stale_shares + WORKER.total_stale_shares2));
    if(WORKER.miner.length() > 0)
    {
        if(keff > 100)
        {
            keff = 100;
            Lkeff->setText(QString::number(int(keff)) + '%');
        }
        else
        {
            Lkeff->setText(QString::number(keff, 'f', 2) + '%');
            if (keff <= 98 && keff >= 97)
            {
                Lkeff->setStyleSheet("color: #FFAE00");
            }
            else if (keff < 97)
            {
                Lkeff->setStyleSheet("color: #FF3733");
            }
        }
    }

    hlay2->addWidget(miner, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    hlay2->addWidget(Lkeff, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    hlay2->addWidget(A, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    hlay2->addWidget(S, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    hlay2->addWidget(R, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    hlay2->addWidget(I, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    //-----------------------------------------------------------
    if(WORKER.status)
    {
        w1->setLayout(hlay1);
        w2->setLayout(hlay2);
        w3->setLayout(hlay3);

        v_lay->addWidget(w1);
        v_lay->addWidget(w2);
        v_lay->addWidget(w3);

        v_widget->setLayout(v_lay);
    }

    //------------------------algo info--------------------------
    QWidget *algo_widget = new QWidget();
    algo_widget->setContentsMargins(20,0,0,0);
    algo_widget->setStyleSheet("background-color: transparent; color: white; font-size: 14px");
    algo_widget->setFixedSize(95,78);
    QVBoxLayout *algo_v = new QVBoxLayout();
    algo_v->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    algo_v->setContentsMargins(0,0,0,0);
    algo_v->setSpacing(0);


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
        value = " H";
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
        value2 = " H";
    QString label_insert_value1 = "";
    QString label_insert_value2 = "";
    if(ALG_2 > 0)
    {
        if (value == " Gh")
            label_insert_value1 += QString::number(int_speed, 'f', 1) + value;
        else
            label_insert_value1 += QString::number(int_speed, 'f', 1) + value;
        if (value2 == " Gh")
            label_insert_value2 += QString::number(int_speed2, 'f', 2) + value2;
        else
            label_insert_value2 += QString::number(int_speed2, 'f', 1) + value2;
    }
    else if (ALG_1 > 0 && ALG_2 == 0)
    {
        if (value == " Gh")
            label_insert_value1 += QString::number(int_speed, 'f', 1) + value;
        else
            label_insert_value1 += QString::number(int_speed, 'f', 1) + value;
        label_insert_value2 += "n/a";
    }
    else
    {
        label_insert_value1 += "n/a";
        label_insert_value2 += "n/a";
    }
    QLabel *alg1_name = new QLabel(WORKER.algorithm);
    alg1_name->setAlignment(Qt::AlignmentFlag::AlignCenter);
    alg1_name->setStyleSheet("background-color: transparent; color: #5c6bc0; font-size: 14px");
    QLabel *alg1_speed = new QLabel(label_insert_value1);
    alg1_speed->setAlignment(Qt::AlignmentFlag::AlignCenter);
    QLabel *alg2_name = new QLabel(WORKER.algorithm2);
    alg2_name->setAlignment(Qt::AlignmentFlag::AlignCenter);
    alg2_name->setStyleSheet("background-color: transparent; color: #2392dc; font-size: 14px");
    QLabel *alg2_speed = new QLabel(label_insert_value2);
    alg2_speed->setAlignment(Qt::AlignmentFlag::AlignCenter);

    algo_v->addWidget(alg1_name);
    algo_v->addWidget(alg1_speed);
    if(ALG_2 > 0)
    {
        algo_v->addWidget(alg2_name);
        algo_v->addWidget(alg2_speed);
    }
    algo_widget->setLayout(algo_v);
    //--------------------------GPU------------------------------
    QWidget *GPU_widget = new QWidget();
    GPU_widget->setContentsMargins(10,0,0,0);
    GPU_widget->setStyleSheet("background-color: transparent; color: white; font-size: 12px;");
    QHBoxLayout *GPU_lay = new QHBoxLayout();
    GPU_lay->setContentsMargins(0,0,0,0);
    GPU_lay->setSpacing(2);
    GPU_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);

    bool double_mining = false;
    for (auto& GPU : WORKER.devices)
    {
        QWidget *v_card_widget = new QWidget();
        v_card_widget->setContentsMargins(0,0,0,0);
        v_card_widget->setStyleSheet("background-color: #2f353c; color: white; font-size: 12px; border-radius: 3px;");
        v_card_widget->setFixedSize(45, 60);
        if(GPU.speed2 > 0)
            double_mining = true;
        if(double_mining)
            v_card_widget->setFixedHeight(70);
        QVBoxLayout *v_card_lay = new QVBoxLayout();
        v_card_lay->setAlignment(Qt::AlignmentFlag::AlignHCenter);
        v_card_lay->setContentsMargins(0,0,0,0);
        v_card_lay->setSpacing(2);

        QLabel *temp = new QLabel(QString::number(GPU.temperature) + "°");
        temp->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);
        temp->setContentsMargins(0,0,7,0);
        QLabel *fan = new QLabel(QString::number(GPU.fan_speed) + "%");
        fan->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);
        fan->setContentsMargins(0,0,4,0);
        fan->setFixedSize(38,17);
        if (GPU.fan_speed == 0)
            fan->setStyleSheet("background-color: #22262b; color: white; font-size: 12px; border-radius: 3px; border-color: #2f353c; border: 2px");
        else if (GPU.fan_speed > 0 && GPU.fan_speed <= 35)
            fan->setStyleSheet("background-color: #5c6bc0; color: #16191d; font-size: 12px; border-radius: 3px;");
        else if (GPU.fan_speed > 35 && GPU.fan_speed <= 65)
            fan->setStyleSheet("background-color: #2392dc; color: #16191d; font-size: 12px; border-radius: 3px;");
        else if (GPU.fan_speed > 65 && GPU.fan_speed <= 80)
            fan->setStyleSheet("background-color: #fcce00; color: #16191d; font-size: 12px; border-radius: 3px;");
        else if (GPU.fan_speed > 80 && GPU.fan_speed <= 100)
            fan->setStyleSheet("background-color: #ff504c; color: #16191d; font-size: 12px; border-radius: 3px;");
        long double ALG_speed1 = GPU.speed;
        long double ALG_speed2 = GPU.speed2;
        if(ALG_speed1 >= 1000 && ALG_speed1 < 1000000)
        {
            ALG_speed1 /= 1000;
        }
        else if(ALG_speed1 >= 100000 && ALG_speed1 < 1000000000)
        {
            ALG_speed1 /= 1000000;
        }
        else if(ALG_speed1 >= 100000000 && ALG_speed1 < 1000000000000)
        {
            ALG_speed1 /= 1000000000;
        }
        if(ALG_speed2 >= 1000 && ALG_speed2 < 1000000)
        {
            ALG_speed2 /= 1000;
        }
        else if(ALG_speed2 >= 100000 && ALG_speed2 < 1000000000)
        {
            ALG_speed2 /= 1000000;
        }
        else if(ALG_speed2 >= 100000000 && ALG_speed2 < 1000000000000)
        {
            ALG_speed2 /= 1000000000;
        }

        QLabel *speed = new QLabel(QString::number(ALG_speed1, 'f', 1));
        speed->setStyleSheet("color: white; font-size: 14px;");
        speed->setAlignment(Qt::AlignmentFlag::AlignCenter);
        QLabel *speed2 = new QLabel(QString::number(ALG_speed2, 'f', 1));
        speed2->setStyleSheet("color: #2392dc; font-size: 14px;");
        speed2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        v_card_lay->addWidget(temp);
        v_card_lay->addWidget(fan);
        v_card_lay->addWidget(speed);
        if(ALG_2 > 0)
            v_card_lay->addWidget(speed2);

        v_card_widget->setLayout(v_card_lay);
        GPU_lay->addWidget(v_card_widget);
    }

    GPU_widget->setLayout(GPU_lay);
    //-----------------------------------------------------------
    lay->addWidget(v_widget, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    if(WORKER.status)
    {
        lay->addWidget(algo_widget, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        lay->addWidget(GPU_widget, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    }
    //-----------------------------------------------------------
    this->top_status_block->setLayout(lay);

}

void gui_farm_info_worker::build_top_bottom_info_block(user_data::WORKER &WORKER)
{
    this->top_bottom_info_block = new QWidget();
    QHBoxLayout *lay = new QHBoxLayout();
    lay->setAlignment(Qt::AlignmentFlag::AlignBottom);
    lay->setContentsMargins(5,2,50,0);
    lay->setSpacing(5);
//-----------------------------------------------------------
    QHBoxLayout *left_block = new QHBoxLayout();
    left_block->setAlignment(Qt::AlignmentFlag::AlignLeft);
    if(WORKER.status)
    {
        QString D1 = QString::number(WORKER.startup / 86400) + 'd';
        QString H1 = QString::number(WORKER.startup / 3600 % 24) + 'h';
        QString M1 = QString::number(WORKER.startup / 60 % 60) + 'm';
        QString S1 = QString::number(WORKER.startup % 60) + 's';

        QString D2 = QString::number(WORKER.uptime / 86400) + 'd';
        QString H2 = QString::number(WORKER.uptime / 3600 % 24) + 'h';
        QString M2 = QString::number(WORKER.uptime / 60 % 60) + 'm';
        QString S2 = QString::number(WORKER.uptime % 60) + 's';

        QLabel *boot_time_text = new QLabel("BOOTED");
        boot_time_text->setStyleSheet("background-color: transparent; color: white; font-size: 12px");
        QLabel *boot_time_value = new QLabel(D1 + " " + H1 + " " + M1 + " " + S1);
        boot_time_value->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

        QLabel *miner_time_text = new QLabel("MINER UPTIME");
        miner_time_text->setStyleSheet("background-color: transparent; color: white; font-size: 12px");

        QLabel *miner_time_value = new QLabel(D2 + " " + H2 + " " + M2 + " " + S2);
        miner_time_value->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

//        QLabel *local_ip_text = new QLabel("IP");
//        local_ip_text->setStyleSheet("background-color: transparent; color: white; font-size: 12px");

//        QLabel *local_ip_value = new QLabel(WORKER.local_ip);
//        local_ip_value->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

        QLabel *version_text = new QLabel("VERSION");
        version_text->setStyleSheet("background-color: transparent; color: white; font-size: 12px");

        QLabel *version_value = new QLabel(WORKER.version);
        version_value->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

        left_block->addWidget(boot_time_text);
        left_block->addWidget(boot_time_value);
        left_block->addWidget(miner_time_text);
        left_block->addWidget(miner_time_value);
//        left_block->addWidget(local_ip_text);
//        left_block->addWidget(local_ip_value);
        left_block->addWidget(version_text);
        left_block->addWidget(version_value);
    }
    else
    {
        QString D = QString::number(WORKER.last_online / 86400) + 'd';
        QString H = QString::number(WORKER.last_online / 3600 % 24) + 'h';
        QString M = QString::number(WORKER.last_online / 60 % 60) + 'm';
        QString S = QString::number(WORKER.last_online % 60) + 's';

        QLabel *boot_time_text = new QLabel("OFFLINE");
        boot_time_text->setStyleSheet("background-color: transparent; color: white; font-size: 12px");
        QLabel *boot_time_value = new QLabel(D + " " + H + " " + M + " " + S);
        boot_time_value->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

        left_block->addWidget(boot_time_text);
        left_block->addWidget(boot_time_value);
    }
//-----------------------------------------------------------
//    QHBoxLayout *right_block = new QHBoxLayout();
//    right_block->setAlignment(Qt::AlignmentFlag::AlignRight);
//    //-------------------------------------------------------
//    QPixmap *icon_linux = new QPixmap("res/linux.svg");
//    QPainter qp_icon_linux = QPainter(icon_linux);
//    qp_icon_linux.setCompositionMode(QPainter::CompositionMode_SourceIn);
//    qp_icon_linux.fillRect(icon_linux->rect(), QColor(129, 142, 156));
//    qp_icon_linux.end();

//    QLabel *icon_linux_widget = new QLabel();
//    icon_linux_widget->setFixedSize(20,20);
//    icon_linux_widget->setContentsMargins(0,0,0,0);
//    icon_linux_widget->setPixmap(*icon_linux);
//    icon_linux_widget->setScaledContents(true);
//    icon_linux_widget->setStyleSheet("background-color: transparent;");

//    QLabel *core_version = new QLabel(WORKER.core_version);
//    core_version->setContentsMargins(0,0,0,0);
//    core_version->setStyleSheet("background-color: transparent; color: #818E9C; font-size 12px");

//    QHBoxLayout *driver_lay = new QHBoxLayout();
//    driver_lay->setContentsMargins(0,0,0,0);
//    driver_lay->setSpacing(0);

//    QLabel *nvidia_n = new QLabel("NVIDIA");
//    nvidia_n->setContentsMargins(0,0,0,0);
//    nvidia_n->setStyleSheet("background-color: transparent; color: #84bf40; font-size 12px");

//    QLabel *nvidia_version = new QLabel(WORKER.nvidia_version);
//    nvidia_version->setContentsMargins(5,0,0,0);
//    nvidia_version->setStyleSheet("background-color: transparent; color: #818E9C; font-size 12px");

//    QLabel *amd_a = new QLabel("AMD");
//    amd_a->setContentsMargins(5,0,0,0);
//    amd_a->setStyleSheet("background-color: transparent; color: #b46fc3; font-size 12px");

//    QLabel *amd_version = new QLabel(WORKER.amd_version);
//    amd_version->setContentsMargins(5,0,0,0);
//    amd_version->setStyleSheet("background-color: transparent; color: #818E9C; font-size 12px");

//    driver_lay->addWidget(nvidia_n);
//    driver_lay->addWidget(nvidia_version);
//    driver_lay->addWidget(amd_a);
//    driver_lay->addWidget(amd_version);

//    QWidget *driver_widget = new QWidget();
//    driver_widget->setContentsMargins(0,0,0,0);
//    driver_widget->setLayout(driver_lay);
//    //-------------------------------------------------------
//    right_block->addWidget(icon_linux_widget);
//    right_block->addWidget(core_version);
//    right_block->addWidget(driver_widget);

//-----------------------------------------------------------
    lay->addLayout(left_block);
//    lay->addLayout(right_block);
    this->top_bottom_info_block->setLayout(lay);
}

void gui_farm_info_worker::build_card_counting_small_block(user_data::WORKER &WORKER)
{
    this->card_counting_small_block = new QWidget();
    QGridLayout *grid = new QGridLayout();
    grid->setAlignment(Qt::AlignmentFlag::AlignRight);
    grid->setSpacing(0);
    grid->setContentsMargins(0,0,50,0);
    grid->setColumnMinimumWidth(2,0);
    grid->setRowMinimumHeight(0, 16);
    QList <QPair<QString, unsigned short int>> chips;
    for (auto& GPU : WORKER.devices)
    {
        bool is_find = false;
        if(chips.empty())
            chips.push_back(QPair(GPU.name, 1));
        else
        {
            for (auto& iter : chips)
            {
                if (iter.first == GPU.name)
                {
                    ++iter.second;
                    is_find = true;
                    break;
                }
                if(!is_find)
                    chips.push_back(QPair(GPU.name, 1));
            }
        }
    }
    for (int i = 0; i < chips.size(); ++i)
    {
        QWidget *wid = new QWidget();
        wid->setContentsMargins(0,0,0,0);
        QHBoxLayout *box = new QHBoxLayout();
        box->setAlignment(Qt::AlignmentFlag::AlignLeft);
        box->addSpacing(0);
        box->setContentsMargins(0,0,0,0);

        QLabel *name = new QLabel(chips[i].first);
        name->setContentsMargins(5,0,0,0);
        name->setStyleSheet("background-color: transparent; color: #84bf40; font-size: 12px");
        QLabel *value = new QLabel("x " + QString::number(chips[i].second));
        value->setStyleSheet("background-color: transparent; color: white; font-size: 12px");

        box->addWidget(name);
        box->addWidget(value);

        wid->setLayout(box);
        grid->addWidget(wid);
    }
    this->card_counting_small_block->setLayout(grid);
}

void gui_farm_info_worker::build_mid_block(user_data::WORKER &WORKER)
{
    this->mid_block = new QWidget();
    QVBoxLayout *mid_lay = new QVBoxLayout();
    mid_lay->setAlignment(Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignHCenter);
    mid_lay->setContentsMargins(0,50,0,0);
    mid_lay->setSpacing(2);
    //-----------------------------------------------------------
    if(WORKER.devices.size() > 0)
    {
        QHBoxLayout *sign_lay = new QHBoxLayout();
        sign_lay->setAlignment(Qt::AlignmentFlag::AlignBottom | Qt::AlignmentFlag::AlignRight);
        sign_lay->setContentsMargins(0,0,0,0);
        sign_lay->setSpacing(0);
        QLabel *fan_lbl = new QLabel("FAN");
        fan_lbl->setContentsMargins(0,0,27,0);
        fan_lbl->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");
        QLabel *core_lbl = new QLabel("CORE");
        core_lbl->setContentsMargins(0,0,32,0);
        core_lbl->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");
        QLabel *mem_lbl = new QLabel("MEM");
        mem_lbl->setContentsMargins(0,0,35,0);
        mem_lbl->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");
        QLabel *pl_lbl = new QLabel("PL");
        pl_lbl->setContentsMargins(0,0,60,0);
        pl_lbl->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

        sign_lay->addWidget(fan_lbl);
        sign_lay->addWidget(core_lbl);
        sign_lay->addWidget(mem_lbl);
        sign_lay->addWidget(pl_lbl);
        mid_lay->addLayout(sign_lay);
    }
    //-----------------------------------------------------------
    for (auto& GPU : WORKER.devices)
    {
        QWidget *gpu_widget = new QWidget();
        gpu_widget->setContentsMargins(0,0,0,0);
        gpu_widget->setFixedSize(1200, 44);
        gpu_widget->setStyleSheet("background-color: #2f353c; color: white; font-size: 12px");
        QHBoxLayout *gpu_lay = new QHBoxLayout();
        gpu_lay->setContentsMargins(0,0,0,0);
        gpu_lay->setSpacing(0);
//-----------------------------------------------------------
        //-----------------------------------------------------------
        QWidget *gpu_id_widget = new QWidget();
        gpu_id_widget->setContentsMargins(0,0,0,0);
        gpu_id_widget->setFixedSize(55, 36);
        QVBoxLayout *gpu_id_lay = new QVBoxLayout();
        gpu_id_lay->setContentsMargins(10,0,0,0);
        gpu_id_lay->setSpacing(0);
        gpu_id_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        QLabel *gpu_id_label = new QLabel("GPU " + QString::number(GPU.gpu_id));
        gpu_id_label->setAlignment(Qt::AlignmentFlag::AlignHCenter);
        QLabel *gpu_bus_label = new QLabel(GPU.bus_id);
        gpu_bus_label->setAlignment(Qt::AlignmentFlag::AlignHCenter);
        gpu_bus_label->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

        gpu_id_lay->addWidget(gpu_id_label);
        gpu_id_lay->addWidget(gpu_bus_label);
        //-----------------------------------------------------------
        QWidget *gpu_name_widget = new QWidget();
        gpu_name_widget->setContentsMargins(0,0,0,0);
        gpu_name_widget->setFixedSize(360, 34);
        QVBoxLayout *gpu_name_vlay = new QVBoxLayout();
        gpu_name_vlay->setContentsMargins(10,0,0,0);
        gpu_name_vlay->setSpacing(0);
        gpu_name_vlay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);

        QWidget *gpu_name_h_widget = new QWidget();
        gpu_name_h_widget->setContentsMargins(0,0,0,0);

        QHBoxLayout *gpu_name_hlay = new QHBoxLayout();
        gpu_name_hlay->setContentsMargins(0,0,0,0);
        gpu_name_hlay->setSpacing(3);
        gpu_name_hlay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        gpu_name_h_widget->setLayout(gpu_name_hlay);


        QLabel *gpu_name_label = new QLabel(GPU.name);
        gpu_name_label->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        gpu_name_label->setStyleSheet("background-color: transparent; color: #84bf40; font-size: 14px");

        QLabel *gpu_param_label = new QLabel(GPU.total_memory + " " + GPU.vendor);
        gpu_param_label->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        gpu_param_label->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

        QLabel *gpu_bios_label = new QLabel(GPU.VBIOS_version + " " + GPU.min_pl + " " + GPU.default_pl + " " + GPU.max_pl);
        gpu_bios_label->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        gpu_bios_label->setStyleSheet("background-color: transparent; color: #818E9C; font-size: 12px");

        gpu_name_hlay->addWidget(gpu_name_label);
        gpu_name_hlay->addWidget(gpu_param_label);

        gpu_name_vlay->addWidget(gpu_name_h_widget);
        gpu_name_vlay->addWidget(gpu_bios_label);
        //-----------------------------------------------------------
        QWidget *gpu_stat_widget = new QWidget();
        gpu_stat_widget->setContentsMargins(0,0,0,0);
        gpu_stat_widget->setFixedSize(190, 34);
        gpu_stat_widget->setStyleSheet("background-color: transparent; color: white; font-size: 14px");
        QHBoxLayout *gpu_stat_lay = new QHBoxLayout();
        gpu_stat_lay->setContentsMargins(10,0,0,0);
        gpu_stat_lay->setSpacing(0);
        gpu_stat_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        QLabel *A = new QLabel("A " + QString::number(GPU.accepted_shares + GPU.accepted_shares2));
        A->setFixedWidth(60);
        A->setContentsMargins(0,0,0,0);
        if((GPU.accepted_shares + GPU.accepted_shares2) == 0)
            A->setStyleSheet("color: transparent");
        else
            A->setStyleSheet("color: white");
        QLabel *S = new QLabel("S " + QString::number(GPU.stale_shares + GPU.stale_shares2));
        S->setFixedWidth(40);
        S->setContentsMargins(0,0,0,0);
        if((GPU.stale_shares + GPU.stale_shares2) == 0)
            S->setStyleSheet("color: transparent");
        else
            S->setStyleSheet("color: #FFAE00");
        QLabel *R = new QLabel("R " + QString::number(GPU.rejected_shares + GPU.rejected_shares2));
        R->setFixedWidth(40);
        R->setContentsMargins(0,0,0,0);
        if((GPU.rejected_shares + GPU.rejected_shares2) == 0)
            R->setStyleSheet("color: transparent");
        else
            R->setStyleSheet("color: #FF3733");
        QLabel *I = new QLabel("I " + QString::number(GPU.invalid_shares + GPU.invalid_shares2));
        I->setFixedWidth(40);
        I->setContentsMargins(0,0,0,0);
        if((GPU.invalid_shares + GPU.invalid_shares2) == 0)
            I->setStyleSheet("color: transparent");
        else
            I->setStyleSheet("color: #FF3733");

        gpu_stat_lay->addWidget(A);
        gpu_stat_lay->addWidget(S);
        gpu_stat_lay->addWidget(R);
        gpu_stat_lay->addWidget(I);
        //-----------------------------------------------------------
        QWidget *gpu_speed_widget = new QWidget();
        gpu_speed_widget->setContentsMargins(0,0,0,0);
        gpu_speed_widget->setFixedSize(70, 34);
        QVBoxLayout *gpu_speed_lay = new QVBoxLayout();
        gpu_speed_lay->setContentsMargins(10,0,0,0);
        gpu_speed_lay->setSpacing(0);
        gpu_speed_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);

        long double ALG_1 = GPU.speed;
        long double ALG_2 = GPU.speed2;
        long double int_speed = ALG_1;
        long double int_speed2 = ALG_2;
        QString value = "";
        QString value2 = "";
        QString label_insert_value1 = "";
        QString label_insert_value2 = "";

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
            value = " H";
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
            value2 = " H";

        if(ALG_2 > 0)
        {
            if (value == " Gh")
                label_insert_value1 += QString::number(int_speed, 'f', 1) + value;
            else
                label_insert_value1 += QString::number(int_speed, 'f', 1) + value;
            if (value2 == " Gh")
                label_insert_value2 += QString::number(int_speed2, 'f', 2) + value2;
            else
                label_insert_value2 += QString::number(int_speed2, 'f', 1) + value2;
        }
        else if (ALG_1 > 0 && ALG_2 == 0)
        {
            if (value == " Gh")
                label_insert_value1 += QString::number(int_speed, 'f', 1) + value;
            else
                label_insert_value1 += QString::number(int_speed, 'f', 1) + value;
            label_insert_value2 += "n/a";
        }
        else
        {
            label_insert_value1 += "n/a";
            label_insert_value2 += "n/a";
        }
        QLabel *speed1 = new QLabel(label_insert_value1);
        speed1->setStyleSheet("background-color: transparent; color: white; font-size: 14px");
        QLabel *speed2 = new QLabel(label_insert_value2);
        speed2->setStyleSheet("background-color: transparent; color: #2392dc; font-size: 14px");

        gpu_speed_lay->addWidget(speed1);
        if(GPU.speed2 > 0)
            gpu_speed_lay->addWidget(speed2);
        //-----------------------------------------------------------
        QWidget *gpu_temp_widget = new QWidget();
        gpu_temp_widget->setContentsMargins(0,0,0,0);
        gpu_temp_widget->setFixedSize(58, 36);
        QHBoxLayout *gpu_temp_lay = new QHBoxLayout();
        gpu_temp_lay->setContentsMargins(10,0,0,0);
        gpu_temp_lay->setSpacing(0);
        gpu_temp_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);

        QPixmap *icon_temperature = new QPixmap("res/temperature.svg");
        QPainter qp_temperature = QPainter(icon_temperature);
        qp_temperature.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp_temperature.fillRect(icon_temperature->rect(), QColor(129, 142, 156));
        qp_temperature.end();

        QLabel *icon_temperature_widget = new QLabel();
        icon_temperature_widget->setFixedSize(25,25);
        icon_temperature_widget->setContentsMargins(0,0,4,0);
        icon_temperature_widget->setPixmap(*icon_temperature);
        icon_temperature_widget->setScaledContents(true);
        icon_temperature_widget->setStyleSheet("background-color: transparent;");

        QLabel *core_temperature = new QLabel(QString::number(GPU.temperature) + "°");
        if(GPU.temperature >= 60)
        {
            core_temperature->setStyleSheet("background-color: transparent; color: #FFAE00; font-size: 14px");
        }
        else if (GPU.temperature > 65)
        {
            core_temperature->setStyleSheet("background-color: transparent; color: #FF3733; font-size: 14px");
        }
        else
        {
            core_temperature->setStyleSheet("background-color: transparent; color: white; font-size: 14px");
        }
        QLabel *mem_temperature = new QLabel(QString::number(GPU.memory_temperature) + "°");
        if(GPU.temperature >= 80)
        {
            mem_temperature->setStyleSheet("background-color: transparent; color: #FFAE00; font-size: 14px");
        }
        else if (GPU.temperature > 95)
        {
            mem_temperature->setStyleSheet("background-color: transparent; color: #FF3733; font-size: 14px");
        }
        else
        {
            mem_temperature->setStyleSheet("background-color: transparent; color: white; font-size: 14px");
        }

        QWidget *temperature = new QWidget();
        temperature->setContentsMargins(0,0,0,0);
        QVBoxLayout *temper = new QVBoxLayout();
        temper->setContentsMargins(0,0,0,0);
        temper->setSpacing(0);

        temper->addWidget(core_temperature);
        if(GPU.memory_temperature > 0)
            temper->addWidget(mem_temperature);
        temperature->setLayout(temper);

        gpu_temp_lay->addWidget(icon_temperature_widget);
        gpu_temp_lay->addWidget(temperature);
        gpu_temp_widget->setLayout(gpu_temp_lay);
        //-----------------------------------------------------------

        QWidget *gpu_fan_widget = new QWidget();
        gpu_fan_widget->setContentsMargins(0,0,0,0);
        gpu_fan_widget->setFixedSize(65, 36);
        QHBoxLayout *gpu_fan_lay = new QHBoxLayout();
        gpu_fan_lay->setContentsMargins(10,0,0,0);
        gpu_fan_lay->setSpacing(0);
        gpu_fan_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
        QLabel *fan_speed_label = new QLabel(QString::number(GPU.fan_speed) + "%");
        fan_speed_label->setStyleSheet("background-color: transparent; color: white; font-size: 14px");

        QPixmap *icon_fan = new QPixmap("res/cooler.svg");
        QPainter qp_fan = QPainter(icon_fan);
        qp_fan.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp_fan.fillRect(icon_fan->rect(), QColor(129, 142, 156));
        qp_fan.end();

        QLabel *icon_fan_widget = new QLabel();
        icon_fan_widget->setFixedSize(20,20);
        icon_fan_widget->setContentsMargins(0,0,4,0);
        icon_fan_widget->setPixmap(*icon_fan);
        icon_fan_widget->setScaledContents(true);
        icon_fan_widget->setStyleSheet("background-color: transparent;");

        gpu_fan_lay->addWidget(icon_fan_widget);
        gpu_fan_lay->addWidget(fan_speed_label);
        gpu_fan_widget->setLayout(gpu_fan_lay);
        //-----------------------------------------------------------
        QWidget *gpu_power_widget = new QWidget();
        gpu_power_widget->setContentsMargins(0,0,0,0);
        gpu_power_widget->setFixedSize(60, 36);
        QHBoxLayout *gpu_power_lay = new QHBoxLayout();
        gpu_power_lay->setContentsMargins(0,0,0,0);
        gpu_power_lay->setSpacing(0);
        gpu_power_lay->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);

        QPixmap *icon_power = new QPixmap("res/consumption.svg");
        QPainter qp_power = QPainter(icon_power);
        qp_power.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp_power.fillRect(icon_power->rect(), QColor(129, 142, 156));
        qp_power.end();

        QLabel *icon_power_widget = new QLabel();
        icon_power_widget->setFixedSize(20,20);
        icon_power_widget->setContentsMargins(0,0,0,0);
        icon_power_widget->setPixmap(*icon_power);
        icon_power_widget->setScaledContents(true);
        icon_power_widget->setStyleSheet("background-color: transparent;");

        QLabel *gpu_power_label = new QLabel(QString::number(GPU.power_usage) + " w");
        gpu_power_label->setStyleSheet("background-color: transparent; color: #818e9c; font-size: 14px");

        gpu_power_lay->addWidget(icon_power_widget);
        gpu_power_lay->addWidget(gpu_power_label);
        gpu_power_widget->setLayout(gpu_power_lay);
        //-----------------------------------------------------------
        QWidget *gpu_set_fan_widget = new QWidget();
        gpu_set_fan_widget->setContentsMargins(0,0,0,0);
        gpu_set_fan_widget->setFixedSize(42, 36);
        QHBoxLayout *gpu_set_fan_lay = new QHBoxLayout();
        gpu_set_fan_lay->setContentsMargins(0,0,0,0);
        gpu_set_fan_lay->setSpacing(0);
        gpu_set_fan_lay->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);

        QLabel *gpu_set_fan_label = new QLabel(QString::number(GPU.set_fan_speed));
        gpu_set_fan_label->setStyleSheet("background-color: transparent; color: #818e9c; font-size: 14px");

        gpu_set_fan_lay->addWidget(gpu_set_fan_label);
        gpu_set_fan_widget->setLayout(gpu_set_fan_lay);
        //-----------------------------------------------------------
        QWidget *gpu_set_core_widget = new QWidget();
        gpu_set_core_widget->setContentsMargins(0,0,0,0);
        gpu_set_core_widget->setFixedSize(48, 36);
        QHBoxLayout *gpu_set_core_lay = new QHBoxLayout();
        gpu_set_core_lay->setContentsMargins(0,0,0,0);
        gpu_set_core_lay->setSpacing(0);
        gpu_set_core_lay->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);

        QLabel *gpu_set_core_label = new QLabel(QString::number(GPU.set_core));
        gpu_set_core_label->setStyleSheet("background-color: transparent; color: #818e9c; font-size: 14px");

        gpu_set_core_lay->addWidget(gpu_set_core_label);
          gpu_set_core_widget->setLayout(gpu_set_core_lay);
        //-----------------------------------------------------------
        QWidget *gpu_set_mem_widget = new QWidget();
        gpu_set_mem_widget->setContentsMargins(0,0,0,0);
        gpu_set_mem_widget->setFixedSize(52, 36);
        QHBoxLayout *gpu_set_mem_lay = new QHBoxLayout();
        gpu_set_mem_lay->setContentsMargins(0,0,0,0);
        gpu_set_mem_lay->setSpacing(0);
        gpu_set_mem_lay->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);
        QLabel *gpu_set_mem_label = new QLabel(QString::number(GPU.set_mem));
        gpu_set_mem_label->setStyleSheet("background-color: transparent; color: #818e9c; font-size: 14px");

        gpu_set_mem_lay->addWidget(gpu_set_mem_label);
        gpu_set_mem_widget->setLayout(gpu_set_core_lay);
        //-----------------------------------------------------------
        QWidget *gpu_set_pl_widget = new QWidget();
        gpu_set_pl_widget->setContentsMargins(0,0,0,0);
        gpu_set_pl_widget->setFixedSize(42, 36);
        QHBoxLayout *gpu_set_pl_lay = new QHBoxLayout();
        gpu_set_pl_lay->setContentsMargins(0,0,0,0);
        gpu_set_pl_lay->setSpacing(0);
        gpu_set_pl_lay->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);
        QLabel *gpu_set_pl_label = new QLabel(QString::number(GPU.set_pl));
        gpu_set_pl_label->setStyleSheet("background-color: transparent; color: #818e9c; font-size: 14px");

        gpu_set_pl_lay->addWidget(gpu_set_pl_label);
        gpu_set_pl_widget->setLayout(gpu_set_core_lay);
        //-----------------------------------------------------------
        QHBoxLayout *gpu_set_lay = new QHBoxLayout();
        gpu_set_lay->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);
        gpu_set_lay->setContentsMargins(0,0,0,0);
        gpu_set_lay->setSpacing(0);

        QPushButton *gpu_set = new QPushButton();
        gpu_set->setFixedSize(40,36);
        gpu_set->setContentsMargins(0,0,0,0);
        gpu_set->setCursor(Qt::PointingHandCursor);
        gpu_set->setFlat(true);
        gpu_set->setLayout(gpu_set_lay);

        QPixmap *icon_button_gpu_set = new QPixmap("res/speed.svg");
        QPainter qp_button_gpu_set = QPainter(icon_button_gpu_set);
        qp_button_gpu_set.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp_button_gpu_set.fillRect(icon_button_gpu_set->rect(), QColor(129, 142, 156));
        qp_button_gpu_set.end();

        gpu_set->setIcon(*icon_button_gpu_set);
        gpu_set->setIconSize(QSize(20,20));
        gpu_set->setStyleSheet("QPushButton {border: none};");

        //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<------------------------------------------- открытие формы ввода параметров разгона по клику
//-----------------------------------------------------------
        gpu_id_widget->setLayout(gpu_id_lay);
        gpu_name_widget->setLayout(gpu_name_vlay);
        gpu_stat_widget->setLayout(gpu_stat_lay);
        gpu_speed_widget->setLayout(gpu_speed_lay);
        gpu_temp_widget->setLayout(gpu_temp_lay);
        gpu_fan_widget->setLayout(gpu_fan_lay);
        gpu_power_widget->setLayout(gpu_power_lay);
        gpu_set_fan_widget->setLayout(gpu_set_fan_lay);
        gpu_set_core_widget->setLayout(gpu_set_core_lay);
        gpu_set_mem_widget->setLayout(gpu_set_mem_lay);
        gpu_set_pl_widget->setLayout(gpu_set_pl_lay);

        gpu_lay->addWidget(gpu_id_widget);
        gpu_lay->addWidget(gpu_name_widget);
        if (WORKER.status)
        {
            gpu_lay->addWidget(gpu_stat_widget);
            gpu_lay->addWidget(gpu_speed_widget);
            gpu_lay->addWidget(gpu_temp_widget);
            gpu_lay->addWidget(gpu_fan_widget);
            gpu_lay->addWidget(gpu_power_widget);
        }
        else
        {
            QWidget *block = new QWidget();
            block->setContentsMargins(0,0,0,0);
            block->setFixedSize(480, 36);
            gpu_lay->addWidget(block);
        }
        gpu_lay->addWidget(gpu_set_fan_widget);
        gpu_lay->addWidget(gpu_set_core_widget);
        gpu_lay->addWidget(gpu_set_mem_widget);
        gpu_lay->addWidget(gpu_set_pl_widget);
        gpu_lay->addWidget(gpu_set);

        gpu_widget->setLayout(gpu_lay);
        gpu_widget->setAttribute(Qt::WA_Hover);
        gpu_widget->installEventFilter(this);
        this->gpu_widget_container.push_back(gpu_widget);
        mid_lay->addWidget(gpu_widget);
    }
    mid_block->setLayout(mid_lay);
}

void gui_farm_info_worker::build_bottom_block(user_data::WORKER &WORKER)
{
    this->bottom_block = new QWidget();
    QVBoxLayout *main_vlay = new QVBoxLayout();
    main_vlay->setAlignment(Qt::AlignmentFlag::AlignBottom);
    main_vlay->setSpacing(0);
    main_vlay->setContentsMargins(10,30,10,10);

    QHBoxLayout *top_hlay = new QHBoxLayout();
    top_hlay->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    top_hlay->setSpacing(5);
    top_hlay->setContentsMargins(0,0,0,0);
//------------------------------top_hlay------------------------------------------
    {
        //----------------block1--------------------
        QHBoxLayout *block1_lay = new QHBoxLayout();
        block1_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        block1_lay->setSpacing(0);
        block1_lay->setContentsMargins(10,10,10,10);
        //---
        QPixmap *icon_cpu = new QPixmap("res/cpu.svg");
        QPainter qp_cpu = QPainter(icon_cpu);
        qp_cpu.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp_cpu.fillRect(icon_cpu->rect(), QColor(129, 142, 156));
        qp_cpu.end();

        QLabel *icon_cpu_widget = new QLabel();
        icon_cpu_widget->setFixedSize(50,50);
        icon_cpu_widget->setContentsMargins(0,0,0,0);
        icon_cpu_widget->setPixmap(*icon_cpu);
        icon_cpu_widget->setScaledContents(true);
        icon_cpu_widget->setStyleSheet("background-color: transparent;");

        block1_lay->addWidget(icon_cpu_widget);
        //---
        QVBoxLayout *block1_subvlay = new QVBoxLayout();
        block1_subvlay->setSpacing(0);
        block1_subvlay->setContentsMargins(10,0,10,0);

        QHBoxLayout *motherboard_lay = new QHBoxLayout();
        motherboard_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        motherboard_lay->setSpacing(5);
        motherboard_lay->setContentsMargins(0,0,0,0);
        QLabel *motherboard_txt = new QLabel("Motherboard");
        motherboard_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *motherboard = new QLabel(WORKER.motherboard_data);
        motherboard_lay->addWidget(motherboard_txt);
        motherboard_lay->addWidget(motherboard);

        QHBoxLayout *cpu_lay = new QHBoxLayout();
        cpu_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        cpu_lay->setSpacing(5);
        cpu_lay->setContentsMargins(0,0,0,0);
        QLabel *cpu_info_txt = new QLabel("CPU");
        cpu_info_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *cpu_info = new QLabel(WORKER.CPU_info);
        cpu_lay->addWidget(cpu_info_txt);
        cpu_lay->addWidget(cpu_info);

        QHBoxLayout *cpuT_lay = new QHBoxLayout();
        cpuT_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        cpuT_lay->setSpacing(5);
        cpuT_lay->setContentsMargins(0,0,0,0);
        QLabel *cpu_temp_txt = new QLabel("CPU TEMP");
        cpu_temp_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *cpu_temp = new QLabel(WORKER.CPU_temperature + "°");
        cpuT_lay->addWidget(cpu_temp_txt);
        cpuT_lay->addWidget(cpu_temp);

        block1_subvlay->addLayout(motherboard_lay);
        block1_subvlay->addLayout(cpu_lay);
        block1_subvlay->addLayout(cpuT_lay);

        QWidget *block1_subv_widget = new QWidget();
        block1_subv_widget->setLayout(block1_subvlay);
        block1_lay->addWidget(block1_subv_widget);
        //---
        QWidget *block1_widget = new QWidget();
        block1_widget->setStyleSheet("background-color: #262b31; color: white; border-radius: 3px;");
        block1_widget->setLayout(block1_lay);
        top_hlay->addWidget(block1_widget);
        //------------------------------------------
    }
    {
        //----------------block2--------------------
        QHBoxLayout *block2_lay = new QHBoxLayout();
        block2_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        block2_lay->setSpacing(0);
        block2_lay->setContentsMargins(10,10,10,10);
        //---
        QVBoxLayout *block2_subvlay = new QVBoxLayout();
        block2_subvlay->setSpacing(0);
        block2_subvlay->setContentsMargins(0,0,0,0);

        QHBoxLayout *disk_model_lay = new QHBoxLayout();
        disk_model_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        disk_model_lay->setSpacing(5);
        disk_model_lay->setContentsMargins(0,0,0,0);
        QLabel *disk_model_txt = new QLabel("Disk Model");
        disk_model_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *disk_model = new QLabel(WORKER.disk_model);
        disk_model_lay->addWidget(disk_model_txt);
        disk_model_lay->addWidget(disk_model);

        QHBoxLayout *disk_size_lay = new QHBoxLayout();
        disk_size_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        disk_size_lay->setSpacing(5);
        disk_size_lay->setContentsMargins(0,0,0,0);
        QLabel *disk_size_txt = new QLabel("Disk Size");
        disk_size_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *disk_size = new QLabel(WORKER.disk_size);
        disk_size_lay->addWidget(disk_size_txt);
        disk_size_lay->addWidget(disk_size);

        QHBoxLayout *disk_free_space_lay = new QHBoxLayout();
        disk_free_space_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        disk_free_space_lay->setSpacing(5);
        disk_free_space_lay->setContentsMargins(0,0,0,0);
        QLabel *disk_free_space_txt = new QLabel("Free Space");
        disk_free_space_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *disk_free_space = new QLabel(WORKER.disk_free_space);
        disk_free_space_lay->addWidget(disk_free_space_txt);
        disk_free_space_lay->addWidget(disk_free_space);

        block2_subvlay->addLayout(disk_model_lay);
        block2_subvlay->addLayout(disk_size_lay);
        block2_subvlay->addLayout(disk_free_space_lay);

        QWidget *block2_subv_widget = new QWidget();
        block2_subv_widget->setLayout(block2_subvlay);
        block2_lay->addWidget(block2_subv_widget);
        //---
        QWidget *block2_widget = new QWidget();
        block2_widget->setStyleSheet("background-color: #262b31; color: white; border-radius: 3px;");
        block2_widget->setLayout(block2_lay);
        top_hlay->addWidget(block2_widget);
        //------------------------------------------
    }
    {
        //----------------block3--------------------
        QHBoxLayout *block3_lay = new QHBoxLayout();
        block3_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        block3_lay->setSpacing(0);
        block3_lay->setContentsMargins(10,10,10,10);
        //---
        QVBoxLayout *block3_subvlay = new QVBoxLayout();
        block3_subvlay->setSpacing(0);
        block3_subvlay->setContentsMargins(0,0,0,0);

        QHBoxLayout *RAM_total_lay = new QHBoxLayout();
        RAM_total_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        RAM_total_lay->setSpacing(5);
        RAM_total_lay->setContentsMargins(0,0,0,0);
        QLabel *RAM_total_txt = new QLabel("RAM Total");
        RAM_total_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *RAM_total = new QLabel(WORKER.RAM_total);
        RAM_total_lay->addWidget(RAM_total_txt);
        RAM_total_lay->addWidget(RAM_total);

        QHBoxLayout *RAM_used_lay = new QHBoxLayout();
        RAM_used_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        RAM_used_lay->setSpacing(5);
        RAM_used_lay->setContentsMargins(0,0,0,0);
        QLabel *RAM_used_txt = new QLabel("RAM Used");
        RAM_used_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *RAM_used = new QLabel(WORKER.RAM_used);
        RAM_used_lay->addWidget(RAM_used_txt);
        RAM_used_lay->addWidget(RAM_used);

        QHBoxLayout *RAM_free_lay = new QHBoxLayout();
        RAM_free_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        RAM_free_lay->setSpacing(5);
        RAM_free_lay->setContentsMargins(0,0,0,0);
        QLabel *RAM_free_txt = new QLabel("RAM Free");
        RAM_free_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *RAM_free = new QLabel(WORKER.RAM_free);
        RAM_free_lay->addWidget(RAM_free_txt);
        RAM_free_lay->addWidget(RAM_free);

        block3_subvlay->addLayout(RAM_total_lay);
        block3_subvlay->addLayout(RAM_used_lay);
        block3_subvlay->addLayout(RAM_free_lay);

        QWidget *block3_subv_widget = new QWidget();
        block3_subv_widget->setLayout(block3_subvlay);
        block3_lay->addWidget(block3_subv_widget);
        //---
        QWidget *block3_widget = new QWidget();
        block3_widget->setStyleSheet("background-color: #262b31; color: white; border-radius: 3px;");
        block3_widget->setLayout(block3_lay);
        top_hlay->addWidget(block3_widget);
        //------------------------------------------
    }
    {
        //----------------block4--------------------
        QHBoxLayout *block4_lay = new QHBoxLayout();
        block4_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        block4_lay->setSpacing(0);
        block4_lay->setContentsMargins(10,10,10,10);
        //---
        QVBoxLayout *block4_subvlay = new QVBoxLayout();
        block4_subvlay->setSpacing(0);
        block4_subvlay->setContentsMargins(0,0,0,0);

        QHBoxLayout *ext_ip_lay = new QHBoxLayout();
        ext_ip_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        ext_ip_lay->setSpacing(5);
        ext_ip_lay->setContentsMargins(0,0,0,0);
        QLabel *ext_ip_txt = new QLabel("Remote IP");
        ext_ip_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *ext_ip = new QLabel(WORKER.ext_ip);
        ext_ip_lay->addWidget(ext_ip_txt);
        ext_ip_lay->addWidget(ext_ip);

        QHBoxLayout *local_ip_lay = new QHBoxLayout();
        local_ip_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        local_ip_lay->setSpacing(5);
        local_ip_lay->setContentsMargins(0,0,0,0);
        QLabel *local_ip_txt = new QLabel("Local IP");
        local_ip_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *local_ip = new QLabel(WORKER.local_ip);
        local_ip_lay->addWidget(local_ip_txt);
        local_ip_lay->addWidget(local_ip);

        QHBoxLayout *MAC_lay = new QHBoxLayout();
        MAC_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        MAC_lay->setSpacing(5);
        MAC_lay->setContentsMargins(0,0,0,0);
        QLabel *MAC_txt = new QLabel("MAC Address");
        MAC_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *MAC = new QLabel(WORKER.MAC);
        MAC_lay->addWidget(MAC_txt);
        MAC_lay->addWidget(MAC);

        block4_subvlay->addLayout(ext_ip_lay);
        block4_subvlay->addLayout(local_ip_lay);
        block4_subvlay->addLayout(MAC_lay);

        QWidget *block3_subv_widget = new QWidget();
        block3_subv_widget->setLayout(block4_subvlay);
        block4_lay->addWidget(block3_subv_widget);
        //---
        QWidget *block3_widget = new QWidget();
        block3_widget->setStyleSheet("background-color: #262b31; color: white; border-radius: 3px;");
        block3_widget->setLayout(block4_lay);
        top_hlay->addWidget(block3_widget);
        //------------------------------------------
    }
    {
        //----------------block5--------------------
        QHBoxLayout *block5_lay = new QHBoxLayout();
        block5_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        block5_lay->setSpacing(0);
        block5_lay->setContentsMargins(10,10,10,10);
        //---
        QPixmap *icon_linux = new QPixmap("res/linux.svg");
        QPainter qp_cpu = QPainter(icon_linux);
        qp_cpu.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp_cpu.fillRect(icon_linux->rect(), QColor(129, 142, 156));
        qp_cpu.end();

        QLabel *icon_linux_widget = new QLabel();
        icon_linux_widget->setFixedSize(50,50);
        icon_linux_widget->setContentsMargins(0,0,0,0);
        icon_linux_widget->setPixmap(*icon_linux);
        icon_linux_widget->setScaledContents(true);
        icon_linux_widget->setStyleSheet("background-color: transparent;");

        block5_lay->addWidget(icon_linux_widget);
        //---
        QVBoxLayout *block5_subvlay = new QVBoxLayout();
        block5_subvlay->setSpacing(0);
        block5_subvlay->setContentsMargins(10,0,10,0);

        QHBoxLayout *core_version_lay = new QHBoxLayout();
        core_version_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        core_version_lay->setSpacing(5);
        core_version_lay->setContentsMargins(0,0,0,0);
        QLabel *core_version_txt = new QLabel("Kernel");
        core_version_txt->setStyleSheet("background-color: transparent; color: #818E9C");
        QLabel *core_version = new QLabel(WORKER.core_version);
        core_version->setContentsMargins(0,0,0,0);
        core_version_lay->addWidget(core_version_txt);
        core_version_lay->addWidget(core_version);

        QHBoxLayout *nvidia_lay = new QHBoxLayout();
        nvidia_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        nvidia_lay->setSpacing(5);
        nvidia_lay->setContentsMargins(0,0,0,0);
        QLabel *nvidia_txt = new QLabel("NVIDIA");
        nvidia_txt->setContentsMargins(0,0,0,0);
        nvidia_txt->setStyleSheet("background-color: transparent; color: #84bf40;");
        QLabel *nvidia_version = new QLabel(WORKER.nvidia_version);
        nvidia_version->setContentsMargins(0,0,0,0);
        nvidia_lay->addWidget(nvidia_txt);
        nvidia_lay->addWidget(nvidia_version);

        QHBoxLayout *amd_lay = new QHBoxLayout();
        amd_lay->setAlignment(Qt::AlignmentFlag::AlignLeft);
        amd_lay->setSpacing(5);
        amd_lay->setContentsMargins(0,0,0,0);
        QLabel *amd_txt = new QLabel("AMD");
        amd_txt->setContentsMargins(0,0,0,0);
        amd_txt->setStyleSheet("background-color: transparent; color: #b46fc3;");
        QLabel *amd_version = new QLabel(WORKER.amd_version);
        amd_version->setContentsMargins(0,0,0,0);
        amd_lay->addWidget(amd_txt);
        amd_lay->addWidget(amd_version);

        block5_subvlay->addLayout(core_version_lay);
        block5_subvlay->addLayout(nvidia_lay);
        block5_subvlay->addLayout(amd_lay);

        QWidget *block5_subv_widget = new QWidget();
        block5_subv_widget->setLayout(block5_subvlay);
        block5_lay->addWidget(block5_subv_widget);
        //---
        QWidget *block5_widget = new QWidget();
        block5_widget->setStyleSheet("background-color: #262b31; color: white;");
        block5_widget->setLayout(block5_lay);
        top_hlay->addWidget(block5_widget);
        //------------------------------------------
    }
//--------------------------------------------------------------------------------
    QWidget *top_widget = new QWidget();
    //top_widget->setFixedSize(1200, 62);
    top_widget->setLayout(top_hlay);
    top_widget->setStyleSheet("background-color: transparent;  font-size: 11px; border-radius: 3px;");

    main_vlay->addWidget(top_widget);
    bottom_block->setLayout(main_vlay);
}

void gui_farm_info_worker::slot_exit_prog()
{
    QApplication::quit();
}

void gui_farm_info_worker::slot_accept_data(user_data::WORKER WORKER)
{
    id = WORKER.ID;
    this->build_top_small_block(WORKER);
    this->build_top_status_block(WORKER);
    this->build_top_bottom_info_block(WORKER);
    this->build_card_counting_small_block(WORKER);
    this->build_mid_block(WORKER);
    this->build_bottom_block(WORKER);

    QWidget *top_widget = new QWidget();
    top_widget->setContentsMargins(0,20,0,0);
    top_widget->setStyleSheet("background-color: #1d2125;");

    QVBoxLayout *top_lay = new QVBoxLayout();
    top_lay->setAlignment(Qt::AlignmentFlag::AlignTop);
    top_lay->setContentsMargins(0,0,0,0);
    top_lay->setSpacing(0);

    top_lay->addWidget(this->top_small_block);
    top_lay->addWidget(this->top_status_block);
    top_lay->addWidget(this->top_bottom_info_block);

    top_widget->setLayout(top_lay);
//-----------------------------------------------------------
    this->main_lay->addWidget(top_widget);
    this->main_lay->addWidget(this->card_counting_small_block);
    this->main_lay->addWidget(this->mid_block);
    if(WORKER.status)
        this->main_lay->addWidget(this->bottom_block, Qt::AlignmentFlag::AlignBottom);

    this->setLayout(main_lay);
}

bool gui_farm_info_worker::eventFilter(QObject *obj, QEvent *event)
{
    for (int i = 0; i < this->gpu_widget_container.size(); ++i)
    {
        if (obj == this->gpu_widget_container[i])
        {
            QEvent::Type type = event->type();
            if  (type == QEvent::HoverLeave)
            {

                this->gpu_widget_container[i]->setStyleSheet("QWidget {background-color: #2f353c; color: white; font-size: 12px};");
            }
            else if (type == QEvent::HoverEnter)
            {
                this->gpu_widget_container[i]->setStyleSheet("QWidget {background-color: rgba(38, 43, 49, 1); color: white; font-size: 12px};");
            }
//            else if (type == QEvent::MouseButtonPress)
//            {
//            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void gui_farm_info_worker::closeEvent(QCloseEvent *event)
{
    emit signal_close(id);
    event->accept();
}
