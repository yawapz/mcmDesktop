//#include "mainwindow.h"
#include "gui_controller.h"
#include "thread_socket.h"
//#include "gui_login_area.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    thread_socket *socket = new thread_socket();
    gui_controller *CONTROLLER = new gui_controller();

    QObject::connect(socket, SIGNAL(signal_soc_connected()), CONTROLLER, SIGNAL(signal_soc_connected()), Qt::UniqueConnection);
    QObject::connect(socket, SIGNAL(signal_send_user_data(user_data)), CONTROLLER, SIGNAL(signal_send_user_data(user_data)), Qt::UniqueConnection);
    QObject::connect(socket, SIGNAL(signal_send_answer_resault(QString, QString)), CONTROLLER, SIGNAL(signal_send_answer_resault(QString, QString)), Qt::UniqueConnection);

    QObject::connect(CONTROLLER, SIGNAL(signal_accept_host_data(QString,int)), socket, SIGNAL(signal_accept_host_data(QString,int)), Qt::UniqueConnection);
    QObject::connect(CONTROLLER, SIGNAL(signal_login(QString,QString)), socket, SIGNAL(signal_login(QString,QString)), Qt::UniqueConnection);
    QObject::connect(CONTROLLER, SIGNAL(signal_create_new_user(QString,QString)), socket, SIGNAL(signal_create_new_user(QString,QString)), Qt::UniqueConnection);
    QObject::connect(CONTROLLER, SIGNAL(signal_create_new_worker(QString)), socket, SIGNAL(signal_create_new_worker(QString)), Qt::UniqueConnection);
    QObject::connect(CONTROLLER, SIGNAL(signal_delete_worker(QString)), socket, SIGNAL(signal_delete_worker(QString)), Qt::UniqueConnection);
    QObject::connect(CONTROLLER, SIGNAL(signal_get_user_data(QString)), socket, SIGNAL(signal_get_user_data(QString)), Qt::UniqueConnection);
    QObject::connect(CONTROLLER, SIGNAL(signal_change_user_data(QString, QString, QString, QString)), socket, SIGNAL(signal_change_user_data(QString, QString, QString, QString)), Qt::UniqueConnection);
    QObject::connect(CONTROLLER, SIGNAL(signal_delete_user(QString, QString)), socket, SIGNAL(signal_delete_user(QString, QString)), Qt::UniqueConnection);

    socket->start();
    return a.exec();
    socket->deleteLater();
    CONTROLLER->deleteLater();
}
