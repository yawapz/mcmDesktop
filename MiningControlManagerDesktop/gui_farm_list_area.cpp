#include "gui_farm_list_area.h"

gui_farm_list_area::gui_farm_list_area(QWidget *parent)
    : QWidget{parent}
{
    this->refresher = new thread_refresh_data();
    QObject::connect(this, &gui_farm_list_area::send_authorization_data, refresher,  &thread_refresh_data::signal_accept_data);
    QObject::connect(refresher, SIGNAL(signal_send_new_data(user_data)), this, SLOT(slot_accept_new_user_data(user_data)));
    this->main_area = new QVBoxLayout();
    this->top_button_panel = new QWidget();
    this->grand_info_panel = new QWidget();
    this->text_button_panel = new QHBoxLayout();
    this->sort_button_panel = new QHBoxLayout();
    this->v_rig_main_panel_widget = new QScrollArea();
    this->rig_info_panel = new QHBoxLayout();

    this->farm_info_arr  = new gui_farm_info_area();
    this->user_settings = new gui_user_settings();
    QObject::connect(this, SIGNAL(signal_exit_prog()), user_settings, SIGNAL(signal_exit_prog()));
    QObject::connect(this, SIGNAL(signal_show_user_settings()), user_settings, SLOT(show()));
    QObject::connect(this, SIGNAL(signal_exit_prog()), user_settings, SLOT(close()));
    QObject::connect(this, &gui_farm_list_area::send_authorization_data, this->farm_info_arr,  &gui_farm_info_area::signal_accept_data);


        v_rig_main_panel_widget->setAlignment(Qt::AlignmentFlag::AlignTop);
        //v_rig_main_panel_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        v_rig_main_panel_widget->setBackgroundRole(QPalette::Light);
        v_rig_main_panel_widget->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        v_rig_main_panel_widget->setStyleSheet("QScrollBar:vertical {background-color: transparent; width: 10px; border-radius: 0px; border: none; margin: 0px 0px 0px 0px;}");
        v_rig_main_panel_widget->setStyleSheet("QScrollBar::handle:vertical {background-color: #1d2125; min-height: 30px; border-radius: 5px;}");
        //v_rig_main_panel_widget->setStyleSheet("QScrollBar::handle:vertical:hover {background-color: #2392dc; min-height: 30px; border-radius: 5px;}");
    // Параметры отображения виджета
//-----------------------------------------------------------
    this->setFixedSize(1280,1024);
    this->main_area->layout()->setContentsMargins(0,0,0,0);
    this->main_area->layout()->setSpacing(0);
    this->main_area->layout()->setMargin(0);
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()/2 - 640, size.height()/2 - 512);
    this->setStyleSheet("background-color: #22262b;");
    this->main_area->setAlignment(Qt::AlignmentFlag::AlignTop);
//-----------------------------------------------------------
}

gui_farm_list_area::~gui_farm_list_area()
{
    this->refresher->deleteLater();
    this->main_area->deleteLater();
    this->top_button_panel->deleteLater();
    this->grand_info_panel->deleteLater();
    this->text_button_panel->deleteLater();
    this->sort_button_panel->deleteLater();
    this->v_rig_main_panel_widget->deleteLater();
    this->rig_info_panel->deleteLater();
    this->farm_info_arr->deleteLater();
    this->user_settings->deleteLater();
    this->H_block->deleteLater();
    this->total_rig_panel->deleteLater();
    this->total_gpu_panel->deleteLater();
    this->total_power_usage_panel->deleteLater();
    this->v_rig_main_panel->deleteLater();
}

void gui_farm_list_area::build_top_button_panel()
{
    QPalette pal;
    pal.setColor(QPalette::ButtonText, QColor(Qt::white));
    QFont font = this->font();
    font.setPixelSize(20);
    // Сборка кнопок top_tool_bar
    QHBoxLayout *right = new QHBoxLayout();
    QHBoxLayout *left = new QHBoxLayout();

    right->setAlignment(Qt::AlignmentFlag::AlignRight);
    left->setAlignment(Qt::AlignmentFlag::AlignLeft);
    right->setGeometry(QRect(0,0, 640,80));
    left->setGeometry(QRect(0,0, 640,80));
//--------------------------------------------------------------------------------------------------------
    QHBoxLayout *top_block = new QHBoxLayout();
        //Конопка my_login
    QPushButton *user_button = new QPushButton(this->login + " ");
    user_button->setPalette(pal);
    user_button->setFont(font);
    //user_button->resize(140,35);
    //user_button->setStyleSheet("QPushButton {color: white; border:  none; padding: 10px 85px 10px 0px};");
    user_button->setStyleSheet("QPushButton::hover {color: #2392dc; background-color: #22262b; border: none};");
    user_button->setCursor(Qt::PointingHandCursor);
    user_button->setFlat(true);

    QMenu *user_button_menu = new QMenu(user_button);
    user_button_menu->setPalette(pal);
    user_button_menu->setCursor(Qt::PointingHandCursor);
    user_button_menu->addAction("User settings");
    user_button_menu->addAction("Worker settings");
    user_button_menu->addAction("Change user");
    user_button_menu->addAction("Exit");

    QObject::connect(user_button_menu, SIGNAL(triggered(QAction*)), this, SLOT(TopMenuEvent(QAction*)));
    //user_button_menu->setStyleSheet("QMenu {color: white; background-color: black};");
    //user_button_menu->setStyleSheet("QMenu::item {color: white; background-color: black};");
    //user_button_menu->setStyleSheet("QMenu::hover {color: #2392dc; background-color: #22262b};");
    user_button_menu->setStyleSheet("QMenu::selected {color: #2392dc; background-color: #22262b};");
    //user_button_menu->setStyleSheet("QPushButton::menu-indicator{image:none;}");
    user_button->setMenu(user_button_menu);
//--------------------------------------------------------------------------------------------------------
        // кнопка refresh
    QPushButton *refresh_button = new QPushButton();
    QObject::connect(refresh_button, SIGNAL(clicked(bool)), refresher, SLOT(run()));
    //refresh_button->setAutoDefault(false);

    refresh_button->setCursor(Qt::PointingHandCursor);
    QPixmap *icon = new QPixmap("res/refresh.svg");
    QPainter qp = QPainter(icon);
    qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
    qp.fillRect(icon->rect(), QColor(Qt::white));
    qp.end();
    refresh_button->setIcon(*icon);
    refresh_button->setIconSize(QSize(18,18));
    refresh_button->setFlat(true);
    refresh_button->setStyleSheet("QPushButton {color: white; border:  none; padding-left: 15px; padding: 10px 15px 10px 15px};");
//--------------------------------------------------------------------------------------------------------
        // кнопка лого
    QPushButton *logo = new QPushButton("MCM Desktop");
    logo->setCursor(Qt::PointingHandCursor);
    logo->setPalette(pal);
    logo->setFont(font);
    //logo->setStyleSheet("QPushButton {color: white; background: #22262b; border: none; padding: 10px 10px 10px 10px};");
    logo->setStyleSheet("QPushButton::hover {border: none; color: #2392dc; background-color: #22262b};");
    logo->setFlat(true);
//--------------------------------------------------------------------------------------------------------
    // Настройки блока
    left->addWidget(logo);

    right->addWidget(refresh_button);
    right->addWidget(user_button);
    top_block->addLayout(left, 0);
    top_block->addLayout(right, 1);
    this->top_button_panel->setLayout(top_block);
}

void gui_farm_list_area::build_grand_info_panel()
{
    grand_panel_base_height = 94;
    H_block = new QGridLayout(this->grand_info_panel);
    H_block->setColumnMinimumWidth(7, 160);
    H_block->setRowMinimumHeight(0, 80);
    //QHBoxLayout *H_block = new QHBoxLayout(this->grand_info_panel);
    this->grand_info_panel->setFixedHeight(grand_panel_base_height);
    this->grand_info_panel->setFixedWidth(1280);
    H_block->setMargin(15);
    H_block->setAlignment(Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft);
    this->grand_info_panel->setStyleSheet("background-color: #1d2125");
    block_style = "QLabel {color: white; background-color: #262b31; padding: 10px 10px 10px 10px; border-radius: 5px; margin: 0px 5px 0px 5px};";
    label_fix_h = 65;
    label_fix_w = 150;
    total_rig_panel = new QLabel();
    total_rig_panel->setFixedHeight(label_fix_h);
    total_rig_panel->setFixedWidth(label_fix_w);
    total_rig_panel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    total_rig_panel->setStyleSheet(block_style);
    total_rig_panel->setText(QString::number(this->data.getTotal_count_WORKERs()) + "\nWORKERS");
    total_gpu_panel = new QLabel();
    total_gpu_panel->setFixedHeight(label_fix_h);
    total_gpu_panel->setFixedWidth(label_fix_w);
    total_gpu_panel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    total_gpu_panel->setStyleSheet(block_style);
    total_gpu_panel->setText(QString::number(this->data.getTotal_count_GPU()) + "\nGPU");

    QString power_value = "";
    long double int_power = this->data.getTotal_power_usage();
    if(int_power > 1000)
    {
        int_power /= 1000;
        power_value = " kW";
    }
    else    //this->update();
    {
        power_value = " W";
    }
    total_power_usage_panel = new QLabel();
    total_power_usage_panel->setFixedHeight(label_fix_h);
    total_power_usage_panel->setFixedWidth(label_fix_w);
    total_power_usage_panel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    total_power_usage_panel->setStyleSheet(block_style);
    total_power_usage_panel->setText(QString::number(int_power,'f', 2) + power_value + "\nCONSUMPTION");
    H_block->addWidget(total_rig_panel);
    H_block->addWidget(total_gpu_panel);
    H_block->addWidget(total_power_usage_panel);

    unsigned short int count_panel_obj = 3;

    for (auto algo : this->data.getSpeed_pair_list())
    {
        QString value = "";
        long double int_speed = algo.second;
        if(algo.second >= 1000 && algo.second < 1000000)
        {
            int_speed /= 1000;
            value = " kH/s";
        }
        else if(algo.second >= 100000 && algo.second < 1000000000)
        {
            int_speed /= 1000000;
            value = " Mh/s";
        }
        else if(algo.second >= 100000000 && algo.second < 1000000000000)
        {
            int_speed /= 1000000000;
            value = " Gh/s";
        }
        else
        {
            value = " H/s";
        }
        QLabel *algo_speed = new QLabel();
        algo_speed->setFixedHeight(label_fix_h);
        algo_speed->setFixedWidth(label_fix_w);
        algo_speed->setAlignment(Qt::AlignmentFlag::AlignCenter);
        algo_speed->setStyleSheet(block_style);
        algo_speed->setText(QString::number(int_speed, 'f', 2) + value + "\n" + algo.first);
        H_block->addWidget(algo_speed);
        ++count_panel_obj;
    }

    //---------ДЛЯ ТЕСТОВ-----------------------------------------------------
//    for (int var = 0; var < 92; ++var)
//    {
//        QLabel *test = new QLabel();
//        test->setFixedHeight(label_fix_h);
//        test->setFixedWidth(label_fix_w);
//        test->setAlignment(Qt::AlignmentFlag::AlignCenter);
//        test->setStyleSheet(block_style);
//        test->setText("test" +  QString::number(var));
//        H_block->addWidget(test);
//        ++count_panel_obj;
//    }
    //------------------------------------------------------------------------

    //Определим высоту контейнера
    int factor = count_panel_obj / 8;
    if(factor > 0)
    {
        if(count_panel_obj % 8 != 0)
        ++factor;
    }
    else if (factor < 1)
    {
        factor = 1;
    }

    for (int var = 0; var < factor; ++var)
    {
        H_block->setRowMinimumHeight(var, 80);
    }
    this->grand_info_panel->setFixedHeight(grand_panel_base_height * factor);
}

void gui_farm_list_area::build_v_rig_panel()
{
    v_rig_main_panel = new QVBoxLayout();
    v_rig_main_panel->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignTop);
    v_rig_main_panel->setContentsMargins(11,50,11,25);
    v_rig_main_panel->setSpacing(3);

    for (auto &iter : this->data.getRIGS())
    {
      gui_farm_list_worker *WORKER = new gui_farm_list_worker(iter);
      WORKER->main_container->setAttribute(Qt::WA_Hover);
      WORKER->main_container->installEventFilter(this);
      v_rig_main_panel_widget_container.push_back(WORKER);
      v_rig_main_panel->addWidget(WORKER->main_container);
    }
    this->v_rig_main_panel_widget->setLayout(v_rig_main_panel);
}

bool gui_farm_list_area::eventFilter(QObject *obj, QEvent *event)
{
    for (int i = 0; i < this->v_rig_main_panel_widget_container.size(); ++i)
    {
        if (obj == this->v_rig_main_panel_widget_container[i]->main_container)
        {
            QEvent::Type type = event->type();
            if  (type == QEvent::HoverLeave)
            {
                if(!this->v_rig_main_panel_widget_container[i]->status)
                    this->v_rig_main_panel_widget_container[i]->main_container->setStyleSheet("QWidget {background-color: #262b31; border: none; border-radius: 0px};");
                else
                    this->v_rig_main_panel_widget_container[i]->main_container->setStyleSheet("QWidget {background-color: #363d45; border: none; border-radius: 0px};");
            }
            else if (type == QEvent::HoverEnter)
            {
                this->v_rig_main_panel_widget_container[i]->main_container->setStyleSheet("QWidget {background-color: rgba(35, 146, 220, 0.5); border: none; border-radius: 0px;};");

            } else if (type == QEvent::MouseButtonPress)
            {
                connect(this, SIGNAL(signal_workerinfo_sender(QString)), this->farm_info_arr, SIGNAL(signal_find_widget(QString)));
                connect(this, SIGNAL(signal_exit_prog()), this->farm_info_arr, SIGNAL(signal_exit_prog()));
                emit signal_workerinfo_sender(v_rig_main_panel_widget_container[i]->ID);
                disconnect(this, SIGNAL(signal_workerinfo_sender(QString)), this->farm_info_arr, SIGNAL(signal_find_widget(QString)));
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void gui_farm_list_area::closeEvent(QCloseEvent *event)
{
    emit this->signal_exit_prog();
}

void gui_farm_list_area::accept_authorization_data(QString log, QString pw, user_data new_data)
{
    this->login = log;
    this->password = pw;
    this->data = new_data;
}

void gui_farm_list_area::build_interface()
{
        emit this->send_authorization_data(this->login, this->password, this->data);
    //--------------------------------------------------------------------------------------------------------
        this->build_top_button_panel();
        this->build_grand_info_panel();
        this->build_v_rig_panel();
    //--------------------------------------------------------------------------------------------------------
        this->main_area->addWidget(this->top_button_panel);
        this->main_area->addWidget(this->grand_info_panel);
        this->main_area->addWidget(this->v_rig_main_panel_widget);

        this->setLayout(this->main_area);

    //--------------------------------------------------------------------------------------------------------
}

void gui_farm_list_area::slot_accept_new_user_data(user_data new_data)
{
    v_rig_main_panel->deleteLater();
    v_rig_main_panel_widget_container.clear();
    delete H_block;
    delete v_rig_main_panel_widget;
    v_rig_main_panel_widget = new QScrollArea();
    v_rig_main_panel_widget->setAlignment(Qt::AlignmentFlag::AlignTop);
    //v_rig_main_panel_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    v_rig_main_panel_widget->setBackgroundRole(QPalette::Light);
    v_rig_main_panel_widget->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    v_rig_main_panel_widget->setStyleSheet("QScrollBar:vertical {background-color: transparent; width: 10px; border-radius: 0px; border: none; margin: 0px 0px 0px 0px;}");
    v_rig_main_panel_widget->setStyleSheet("QScrollBar::handle:vertical {background-color: #1d2125; min-height: 30px; border-radius: 5px;}");

    delete main_area;
    main_area = new QVBoxLayout();
    main_area->layout()->setContentsMargins(0,0,0,0);
    main_area->layout()->setSpacing(0);
    main_area->layout()->setMargin(0);
    main_area->setAlignment(Qt::AlignmentFlag::AlignTop);

    delete top_button_panel;
    delete grand_info_panel;
    top_button_panel = new QWidget();
    grand_info_panel = new QWidget();

    this->data = new_data;


    this->build_interface();
}

void gui_farm_list_area::TopMenuEvent(QAction* act)
{
    if(act->text() == "Exit")
    {
        emit signal_exit_prog();
        QApplication::quit();
    }
    else if(act->text() == "Change user")
    {
        qApp->quit();
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    else if(act->text() == "User settings")
    {
        emit signal_show_user_settings();
    }
    else if(act->text() == "Worker settings")
    {

    }
}

