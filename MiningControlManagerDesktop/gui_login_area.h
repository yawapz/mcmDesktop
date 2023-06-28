#ifndef GUI_LOGIN_AREA_H
#define GUI_LOGIN_AREA_H

#include "user_data.h"
#include "logger/thread_logger.h"

#include <QWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStyle>
#include <QThread>
#include <QTcpSocket>
#include <QEventLoop>
#include <QTimer>
#include <QKeyEvent>
#include <QFile>
#include <QScreen>
#include <QTextStream>

class gui_login_area : public QWidget
{
    Q_OBJECT
public:
    explicit gui_login_area(QWidget *parent = nullptr);
    ~gui_login_area();

protected:
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    bool isConnected;
    QString lastHostConnection;
    void ReadLastHostConnection();
    void WriteLastHostConnection();
    void ReadLastLogin();
    void WriteLastLogin();

    QLabel* resault;
    QLineEdit* login_line;
    QLineEdit* pw_line;
    QLineEdit* server_line;
    user_data data;
    thread_logger *log;
    QPushButton *exit;

private slots:
    void authorization();
    void gui_transit();

    void registration();
    void access_checker(QString, QString);
    void accept_json(user_data);
    void slot_red();
    void slot_white();
    void slot_connected();
    void slot_connector();
    void slot_checker();

signals:
    void signal_disconnect();
    void signal_try_connect(QString, int);
    void signal_soc_connected();
    void call_farm_list_form();
    void call_reg_form();
    void send_authorization_data_to_another_form(QString, QString, user_data);
    void click();

    void signal_login(QString, QString);
    void signal_send_answer_resault(QString, QString);

    void signal_get_user_data(QString);
    void signal_send_user_data(user_data);
};

#endif // GUI_LOGIN_AREA_H
