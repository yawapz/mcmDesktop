#ifndef GUI_FARM_INFO_WORKER_H
#define GUI_FARM_INFO_WORKER_H

#include "user_data.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QList>
#include <QPair>
#include <QPushButton>

class gui_farm_info_worker : public QWidget
{
    Q_OBJECT
protected:
    bool eventFilter(QObject *, QEvent *);
    void closeEvent(QCloseEvent *);

public:
    explicit gui_farm_info_worker();
    ~gui_farm_info_worker();

    QVBoxLayout *main_lay;
    QWidget *top_small_block;
    QWidget *top_status_block;
    QWidget *top_bottom_info_block;
    QWidget *card_counting_small_block;
    QWidget *mid_block;
    QWidget *bottom_block;

    QList<QWidget*> gpu_widget_container;
    QString id;
private:
    void build_top_small_block(user_data::WORKER &WORKER);
    void build_top_status_block(user_data::WORKER &WORKER);
    void build_top_bottom_info_block(user_data::WORKER &WORKER);
    void build_card_counting_small_block(user_data::WORKER &WORKER);
    void build_mid_block(user_data::WORKER &WORKER);
    void build_bottom_block(user_data::WORKER &WORKER);

signals:
    void signal_accept_user_data(user_data::WORKER);
    void signal_exit_prog();
    void signal_close(QString);

private slots:
    void slot_exit_prog();
    void slot_accept_data(user_data::WORKER);
};

#endif // GUI_FARM_INFO_WORKER_H
