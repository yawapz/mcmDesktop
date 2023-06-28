#ifndef GUI_REG_AREA_H
#define GUI_REG_AREA_H

#include <QObject>
#include <QWidget>
#include <QScreen>
#include <QLineEdit>
#include "qapplication.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QProcess>
#include <QTcpSocket>
#include <QDialog>
#include <QTimer>

class gui_reg_area : public QWidget
{
    Q_OBJECT
public:
    explicit gui_reg_area(QWidget *parent = nullptr);
    ~gui_reg_area();

signals:
    void signal_create_new_user(QString, QString);
    void signal_send_answer_resault(QString, QString);
    void signal_back();
private:
    QLineEdit* login;
    QLineEdit* password;

private slots:
    void on_click_send_button();
    void accept_result(QString, QString);
    void restart_programm();
    void unlock_form();
    void slot_red();
    void slot_white();
};

#endif // GUI_REG_AREA_H
