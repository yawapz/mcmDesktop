#include "gui_reg_area.h"

gui_reg_area::gui_reg_area(QWidget *parent)
    : QWidget{parent}
{
    // Параметры отображения виджета
//-----------------------------------------------------------
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()/2, size.height()/2 - 110);
    this->setFocus();
    this->setFixedSize(220,220);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setStyleSheet("QWidget {color: white; background-color: #22262b};");
//-----------------------------------------------------------
    // Инициализация
    int block_height = 30;

    login = new QLineEdit();
    login->setFixedHeight(block_height);
    password = new QLineEdit();
    password->setFixedHeight(block_height);

    login->setDragEnabled(true);
    login->setPlaceholderText("Enter Email");
    login->setStyleSheet("QLineEdit {color: white; padding: 5px; font-size: 16px;};");

    password->setDragEnabled(false);
    password->setPlaceholderText("Enter password");
    password->setStyleSheet("QLineEdit {color: white; padding: 5px; font-size: 16px;};");
    password->setEchoMode(QLineEdit::Password);

    QVBoxLayout *main_lay = new QVBoxLayout();
    main_lay->setSpacing(5);

    QLabel* text = new QLabel("<H1> Registration </H1>");
    text->setAlignment(Qt::AlignmentFlag::AlignCenter);
    text->setContentsMargins(0,0,0,10);

    QPushButton *send = new QPushButton("Join");
    send->setFixedHeight(block_height);
    QObject::connect(send, SIGNAL(clicked(bool)), this, SLOT(on_click_send_button()));

    QPushButton *back = new QPushButton("Back");
    back->setFixedHeight(block_height);
    QObject::connect(back, SIGNAL(clicked(bool)), this, SIGNAL(signal_back()));

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setContentsMargins(0,0,0,0);

    QVBoxLayout *main_lay_top = new QVBoxLayout();
    QVBoxLayout *main_lay_bottom = new QVBoxLayout();

    main_lay_top->setAlignment      (Qt::AlignmentFlag::AlignTop);
    main_lay_bottom->setAlignment   (Qt::AlignmentFlag::AlignBottom);

    main_lay_top->addWidget(text);
    main_lay_top->addWidget(login);
    main_lay_top->addWidget(password);

    main_lay_bottom->addWidget(line);
    main_lay_bottom->addWidget(send);
    main_lay_bottom->addWidget(back);

    main_lay->addLayout(main_lay_top);
    main_lay->addLayout(main_lay_bottom);

    this->setLayout(main_lay);
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString, QString)), this, SLOT(accept_result(QString, QString)));
}

gui_reg_area::~gui_reg_area()
{
    login->deleteLater();
    password->deleteLater();
}

void gui_reg_area::on_click_send_button()
{
    if(login->text().contains('@') && login->text().contains('.'))
    {
        emit signal_create_new_user(this->login->text(), this->password->text());
    }
    else
    {
        QTimer *t = new QTimer();
        t->start(300);
        QObject::connect(t, SIGNAL(timeout()), this, SLOT(slot_red()));

        QTimer *t2 = new QTimer();
        t2->start(500);
        QObject::connect(t2, SIGNAL(timeout()), this, SLOT(slot_white()));

        QTimer *t3 = new QTimer();
        t3->start(1000);
        QObject::connect(t3, SIGNAL(timeout()), t, SLOT(stop()));
        QObject::connect(t3, SIGNAL(timeout()), t2, SLOT(stop()));
        QObject::connect(t3, SIGNAL(timeout()), t, SLOT(deleteLater()));
        QObject::connect(t3, SIGNAL(timeout()), t2, SLOT(deleteLater()));
        QObject::connect(t3, SIGNAL(timeout()), t3, SLOT(deleteLater()));
        QObject::connect(t3, SIGNAL(timeout()), this, SLOT(slot_white()));
    }
}

void gui_reg_area::accept_result(QString req , QString cmd)
{
    if(cmd == "new_user")
    {
        QDialog *win = new QDialog();
        win->setStyleSheet("QWidget {color: white; background-color: #22262b};");
        win->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        QScreen *screen = QApplication::screens().at(0);
        QSize size = screen->availableSize();
        win->move(size.width()/2, size.height()/2);
        QVBoxLayout *lay = new QVBoxLayout();
        QLabel *label = new QLabel();
        label->setFixedHeight(30);
        QPushButton *button = new QPushButton("OK");
        button->setFixedHeight(30);
        QObject::connect(button, SIGNAL(clicked()), win, SLOT(close()));
        this->hide();
        if(req == "yes")
        {
            QObject::connect(button, SIGNAL(clicked()), this, SLOT(restart_programm()));
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
            this->login->clear();
            this->password->clear();
            label->setStyleSheet("QLabel {color : red;}");
            label->setText("Unsuccessful");
            lay->addWidget(label);
            lay->addWidget(button);
            win->setLayout(lay);
            win->show();
        }
    }
}

void gui_reg_area::restart_programm()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void gui_reg_area::unlock_form()
{
    this->setEnabled(true);
}

void gui_reg_area::slot_red()
{
    login->setStyleSheet("QLineEdit {color: red; padding: 5px; font-size: 16px;};");
    //password->setStyleSheet("QLineEdit {color: red; padding: 5px; font-size: 16px;};");
}

void gui_reg_area::slot_white()
{
    login->setStyleSheet("QLineEdit {color: white; padding: 5px; font-size: 16px;};");
    //password->setStyleSheet("QLineEdit {color: white; padding: 5px; font-size: 16px;};");
}
