#ifndef GUI_USER_SETTINGS_H
#define GUI_USER_SETTINGS_H

#include "user_data.h"
#include <QObject>
#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QApplication>
#include <QScreen>
#include <QProcess>
#include <QTimer>

class gui_user_settings : public QWidget
{
    Q_OBJECT
public:
    explicit gui_user_settings(QWidget *parent = nullptr);
    ~gui_user_settings();
protected:
        void closeEvent(QCloseEvent *);
        bool eventFilter(QObject *, QEvent *);
private:
    QString login;
    QString password;
    QList<QWidget*> lbls;

    QLineEdit *current_login;
    QLineEdit *current_password;
    QLineEdit *new_login;
    QLineEdit *new_password;
    QPushButton *save_button;
    QPushButton *delete_button;
    QPushButton *exit;

    void blink_lineE();

signals:
    void signal_unlock();
    void signal_new_pos(QPoint, QSize);
    void signal_exit_prog();
    void signal_change_user_data(QString, QString, QString, QString);
    void signal_delete_user(QString, QString);
    void signal_send_answer_resault(QString, QString);
    void signal_accept_user_data(QString,QString,user_data);
private slots:
    void slot_accept_user_data(QString,QString,user_data);
    void slot_accept_server_answer(QString, QString);
    void slot_update_request();
    void slot_delete_request();
    void slot_restart_programm();
    void slot_warning();
    void slot_unlock_form();
    void slot_set_pos(QPoint, QSize);
    void slot_red();
    void slot_white();
};

#endif // GUI_USER_SETTINGS_H
