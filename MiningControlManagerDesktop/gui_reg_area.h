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

class gui_reg_area : public QWidget
{
    Q_OBJECT
public:
    explicit gui_reg_area(QWidget *parent = nullptr);

signals:

private:
    QLineEdit* login;
    QLineEdit* password;

private slots:
    void on_click_send_button();
};

#endif // GUI_REG_AREA_H
