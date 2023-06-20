#ifndef GUI_FARM_LIST_AREA_H
#define GUI_FARM_LIST_AREA_H
#include "user_data.h"
//#include "gui_farm_info_area.h"
//#include "thread_farm_info.h"
#include "gui_farm_list_worker.h"
#include "gui_farm_info_area.h"


#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QLabel>
#include <QProcess>
#include <QPainter>
#include <QGridLayout>
#include <QScrollArea>
#include <QStyleOptionFocusRect>
#include "qapplication.h"
#include "qscreen.h"
#include <QDebug>
#include "gui_user_settings.h"

class gui_farm_list_area : public QWidget
{
    Q_OBJECT
public:
    explicit gui_farm_list_area(QWidget *parent = nullptr);
    ~gui_farm_list_area();



private:

    gui_farm_info_area *farm_info_arr;
    gui_user_settings *user_settings;

    QString login;
    QString password;
    //QString RSI_KEY

    user_data data;

    QVBoxLayout* main_area;
    QWidget* top_button_panel;
    QWidget* grand_info_panel;
    QHBoxLayout* text_button_panel; // Дальнейшая интеграция
    QHBoxLayout* sort_button_panel; // Дальнейшая интеграция

    QScrollArea* v_rig_main_panel_widget;
    QVector<gui_farm_list_worker*> v_rig_main_panel_widget_container;

    QHBoxLayout* rig_info_panel;

    void build_top_button_panel();
    void build_grand_info_panel();
    void build_v_rig_panel();

protected:
    bool eventFilter(QObject *, QEvent *);
    void closeEvent(QCloseEvent *);
public slots:
    void accept_authorization_data(QString log, QString pw, user_data new_data);
    void build_interface();

private slots:
    //void clicked_on_refresh_button();
    void TopMenuEvent(QAction*);



signals:
    void send_authorization_data(QString, QString, user_data);
    void signal_workerinfo_sender(QString);
    void signal_exit_prog();
    void signal_show_user_settings();

};

#endif // GUI_FARM_LIST_AREA_H
