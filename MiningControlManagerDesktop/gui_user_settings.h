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

class gui_user_settings : public QWidget
{
    Q_OBJECT
public:
    explicit gui_user_settings(QWidget *parent = nullptr);
    ~gui_user_settings();

private:
    QTcpSocket *soc;
    QLineEdit *current_login;
    QLineEdit *current_password;
    QLineEdit *new_login;
    QLineEdit *new_password;
    QPushButton *save_button;
    QPushButton *delete_button;


signals:

private slots:
    void slot_accept_server_answer();
    void slot_update_request();
    void slot_delete_request();
    void slot_restart_programm();
    void slot_warning();
    void slot_unlock_form();
};

#endif // GUI_USER_SETTINGS_H
