//#include "mainwindow.h"
#include "gui_controller.h"
//#include "gui_login_area.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui_controller CONTROLLER;
    return a.exec();
}
