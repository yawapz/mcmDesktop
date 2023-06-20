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

class gui_reg_area : public QWidget
{
    Q_OBJECT
public:
    explicit gui_reg_area(QWidget *parent = nullptr);
    ~gui_reg_area();

signals:

private:
    QLineEdit* login;
    QLineEdit* password;
    QTcpSocket* soc;

private slots:
    void on_click_send_button();
    void accept_result();
    void restart_programm();
    void unlock_form();
};

#endif // GUI_REG_AREA_H
