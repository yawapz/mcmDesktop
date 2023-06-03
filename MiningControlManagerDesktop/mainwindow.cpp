#include "mainwindow.h"
#include "gui_login_area.h"
#include "qapplication.h"
#include "qscreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gui_login_area *login_widget = new gui_login_area();
    this->setCentralWidget(login_widget);

    // В центр экрана
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()/2 - 125, size.height()/2 - 110);
    // Помогло убрать автофокус
    this->setFocus();

}

MainWindow::~MainWindow()
{
    this->close();
}

