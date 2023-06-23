#include "gui_user_settings.h"

gui_user_settings::gui_user_settings(QWidget *parent)
    : QWidget{parent}
{
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()/2 - 125, size.height()/2 - 110);

    this->soc = new QTcpSocket();
    current_login = new QLineEdit();
    current_password = new QLineEdit();
    new_login = new QLineEdit();
    new_password = new QLineEdit();
    save_button = new QPushButton("Save сhanges");
    delete_button = new QPushButton("Delete current user");

    QObject::connect(soc, SIGNAL(readyRead()), this, SLOT(slot_accept_server_answer()));
    QObject::connect(save_button, SIGNAL(clicked()), this, SLOT(slot_update_request()));
    QObject::connect(delete_button, SIGNAL(clicked()), this, SLOT(slot_warning()));

    QVBoxLayout *main_lay = new QVBoxLayout();

    current_login->setPlaceholderText("Current login");
    current_password->setPlaceholderText("Current password");
    new_login->setPlaceholderText("New login");
    new_password->setPlaceholderText("New password");

    main_lay->addWidget(current_login);
    main_lay->addWidget(current_password);
    main_lay->addWidget(new_login);
    main_lay->addWidget(new_password);
    main_lay->addWidget(save_button);
    main_lay->addWidget(delete_button);
    this->setLayout(main_lay);
}

gui_user_settings::~gui_user_settings()
{
    this->soc->deleteLater();
    this->current_login->deleteLater();
    this->current_password->deleteLater();
    this->new_login->deleteLater();
    this->new_password->deleteLater();
    this->delete_button->deleteLater();
    this->save_button->deleteLater();
}

void gui_user_settings::closeEvent(QCloseEvent *)
{
    emit this->signal_exit_prog();
}

void gui_user_settings::slot_update_request()
{
    this->setEnabled(false);
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    QString command = "update_user_data";

    stream << command;
    stream << this->current_login->text();
    stream << this->current_password->text();
    stream << this->new_login->text();
    stream << this->new_password->text();

    if(!soc->isOpen())
        soc->connectToHost("127.0.0.1", 48048);
    soc->waitForConnected(1000);
    soc->write(*barr);
    soc->flush();
    delete barr;
}

void gui_user_settings::slot_delete_request()
{
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    QString command = "del_user";

    stream << command;
    stream << this->current_login->text();
    stream << this->current_password->text();

    if(!soc->isOpen())
        soc->connectToHost("127.0.0.1", 48048);
    soc->waitForConnected(1000);
    soc->write(*barr);
    soc->flush();
    delete barr;
}

void gui_user_settings::slot_accept_server_answer()
{
    soc->waitForReadyRead(1000);
    QString req = "no";
    QByteArray barr = soc->readAll();
    QDataStream stream(&barr, QIODevice::ReadOnly);
    stream >> req;
    QDialog *win = new QDialog();
    QObject::connect(this, SIGNAL(signal_exit_prog()), win, SLOT(close()));
    win->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    win->move(size.width()/2 - 125 + 50, size.height()/2 - 110 + 80);
    QVBoxLayout *lay = new QVBoxLayout();
    QLabel *label = new QLabel();
    QPushButton *button = new QPushButton("OK");
    QObject::connect(button, SIGNAL(clicked()), win, SLOT(close()));
    if(req == "yes")
    {
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(slot_restart_programm()));
        label->setStyleSheet("QLabel {color : green;}");
        label->setText("Successfully");
        lay->addWidget(label);
        lay->addWidget(button);
        win->setLayout(lay);
        win->show();
    }
    else
    {
        this->setEnabled(true);
        label->setStyleSheet("QLabel {color : red;}");
        label->setText("Unsuccessful");
        lay->addWidget(label);
        lay->addWidget(button);
        win->setLayout(lay);
        win->show();
    }
    this->current_login->clear();
    this->current_password->clear();
    this->new_login->clear();
    this->new_password->clear();
    soc->waitForDisconnected(1000);
}

void gui_user_settings::slot_restart_programm()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void gui_user_settings::slot_warning()
{
    this->setEnabled(false);
    QDialog *win = new QDialog();
    QObject::connect(this, SIGNAL(signal_exit_prog()), win, SLOT(close()));
    win->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();

    QVBoxLayout *lay = new QVBoxLayout();
    QVBoxLayout *lay2 = new QVBoxLayout();
    QLabel *label = new QLabel("Are you sure?");


    label->setStyleSheet("QLabel {color : red;}");

    QPushButton *button1 = new QPushButton("Delete");
    QPushButton *button2 = new QPushButton("Cancel");
    QObject::connect(button1, SIGNAL(clicked()), win, SLOT(close()));
    QObject::connect(button1, SIGNAL(clicked()), this, SLOT(slot_delete_request()));
    QObject::connect(button2, SIGNAL(clicked()), win, SLOT(close()));
    QObject::connect(button2, SIGNAL(clicked()), this, SLOT(slot_unlock_form()));
    if(this->current_login->text().isEmpty() || this->current_password->text().isEmpty())
    {
        label->setText("Please enter your current login\n and your current password");
        lay2->addWidget(button2);
        win->move(size.width()/2 - 140, size.height()/2 - 110 + 80);
    }
    else
    {
        lay2->addWidget(button1);
        lay2->addWidget(button2);
        win->move(size.width()/2 - 80, size.height()/2 - 110 + 80);
    }

    lay->addWidget(label);
    lay->addLayout(lay2);

    win->setLayout(lay);
    win->show();
}

void gui_user_settings::slot_unlock_form()
{
    this->setEnabled(true);
}
