#ifndef GUI_FARM_LIST_AREA_H
#define GUI_FARM_LIST_AREA_H
#include "user_data.h"
//#include "gui_farm_info_area.h"
//#include "thread_farm_info.h"
#include "gui_farm_list_worker.h"
#include "gui_farm_info_area.h"
#include "gui_worker_settings.h"

#include <QMouseEvent>
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
//#include "thread_refresh_data.h"

class gui_farm_list_area : public QWidget
{
    Q_OBJECT
public:
    explicit gui_farm_list_area(QWidget *parent = nullptr);
    ~gui_farm_list_area();
private:
    gui_farm_info_area *farm_info_arr;
    gui_user_settings *user_settings;
    gui_worker_settings *worker_settings;

    QString login;
    QString password;
    user_data data;

    QVBoxLayout* main_area;
    QWidget* top_button_panel;
    QWidget* grand_info_panel;
//    QHBoxLayout* text_button_panel; // Дальнейшая интеграция
//    QHBoxLayout* sort_button_panel; // Дальнейшая интеграция

    QScrollArea* v_rig_main_panel_widget;
    QVector<gui_farm_list_worker*> v_rig_main_panel_widget_container;

    QHBoxLayout* rig_info_panel;

    void build_top_button_panel();
    void build_grand_info_panel();
    void build_v_rig_panel();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    bool eventFilter(QObject *, QEvent *);
    void closeEvent(QCloseEvent *);
public slots:
    void accept_authorization_data(QString log, QString pw, user_data new_data);
    void build_interface();

private slots:
    void slot_accept_new_user_data(user_data);
    void TopMenuEvent(QAction*);
    void slot_disable_interface();
    void slot_active_interface();
    void slot_emit_data_req();

signals:
    void send_authorization_data(QString, QString, user_data);
    void signal_workerinfo_sender(QString);
    void signal_exit_prog();
    void signal_show_user_settings();
    void signal_show_worker_settings();
    void signal_ready_update(QString, QString, user_data);
    void signal_send_data_for_workers_settings(QString, QString, user_data);
    void signal_new_pos(QPoint, QSize);
    void signal_update_worker(user_data::WORKER);
//-------------------------------------------------------------------------------
    void signal_get_user_data(QString);

    void signal_create_new_worker(QString);
    void signal_delete_worker(QString);

    void signal_change_user_data(QString, QString, QString, QString);
    void signal_delete_user(QString, QString);

    void signal_send_answer_resault(QString, QString);
    void signal_send_user_data(user_data);

private:
    unsigned short int grand_panel_base_height;

    QGridLayout *H_block;
    int count_panel_obj;
    QList<QPair<QLabel*, QPair<QString, unsigned long long>>> H_block_widgets;

    void H_block_refresh();
    void v_rig_refresh();

    QLabel *total_rig_panel;
    QLabel *total_gpu_panel;
    QLabel *total_power_usage_panel;
    QVBoxLayout *v_rig_main_panel;

    //block
    QString block_style;
    int label_fix_h;
    int label_fix_w;

    bool eventFilterblock;


    bool moving;
    QPoint last_mouse_pos;

};

#endif // GUI_FARM_LIST_AREA_H
