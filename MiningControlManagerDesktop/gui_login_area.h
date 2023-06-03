#ifndef GUI_LOGIN_AREA_H
#define GUI_LOGIN_AREA_H

#include "user_data.h"
#include "logger/thread_logger.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStyle>
#include <QThread>

class gui_login_area : public QWidget
{
    Q_OBJECT
public:
    explicit gui_login_area(QWidget *parent = nullptr);
    ~gui_login_area();

private:
    QLabel* resault;
    QLineEdit* login_line;
    QLineEdit* pw_line;

    thread_logger *log;

private slots:
    void authorization();
    void gui_transit();

    void registration();

signals:
    void call_farm_list_form();
    void call_reg_form();
    void send_authorization_data_to_another_form(QString, QString, user_data);
    void click();
};

#endif // GUI_LOGIN_AREA_H
