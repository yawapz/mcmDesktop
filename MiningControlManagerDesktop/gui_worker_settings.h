#ifndef GUI_WORKER_SETTINGS_H
#define GUI_WORKER_SETTINGS_H

#include "user_data.h"
#include <QObject>
#include <QWidget>
#include <QString>
#include <QDataStream>
#include <QTcpSocket>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QEvent>
#include <QEventLoop>
#include <QScreen>
#include <QApplication>
#include <QPainter>
#include <QTimer>

class gui_worker_settings : public QWidget
{
    Q_OBJECT
public:
    explicit gui_worker_settings(QWidget *parent = nullptr);
    ~gui_worker_settings();

    QTcpSocket *soc;
    user_data data;
    QString login;
    QString password;

    QList<QWidget*> widget_list;

private:
    void widget_list_cleaner();
    unsigned short int current_element;
    void closeEvent(QCloseEvent*);

    QString host;
    int port;


private slots:
    void slot_accept_inc_data(QString, QString, user_data);
    void slot_build_interface();
    void slot_delete_worker();
    void slot_add_worker();
    void slot_check_result_operation();
    void slot_accept_json();
    void slot_accept_new_pos(QPoint, QSize);
    void slot_host_data(QString, int);

signals:
    void signal_inc_data(QString, QString, user_data);
    void signal_send_data(user_data);
    void signal_data_accepted();
    void signal_unlock();
    void signal_new_pos(QPoint, QSize);
    void signal_host_data(QString, int);

protected:
    bool eventFilter(QObject *, QEvent *);
};

#endif // GUI_WORKER_SETTINGS_H
