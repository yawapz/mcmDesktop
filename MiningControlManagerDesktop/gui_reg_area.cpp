#include "gui_reg_area.h"

gui_reg_area::gui_reg_area(QWidget *parent)
    : QWidget{parent}
{
    // Параметры отображения виджета
//-----------------------------------------------------------
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();
    this->move(size.width()/2 - 125, size.height()/2 - 110);
    this->setFocus();
    this->setFixedSize(220,165);
//-----------------------------------------------------------
    // Инициализация
    this->login = new QLineEdit();
    this->password = new QLineEdit();

    QLabel* login_label = new QLabel("Enter your email address");
    login_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

    this->login->setDragEnabled(true);
    this->login->setPlaceholderText("Email");
    this->login->setAlignment(Qt::AlignmentFlag::AlignCenter);

    QLabel* pw_label = new QLabel("Enter your new password");
    pw_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

    this->password->setDragEnabled(false);
    this->password->setPlaceholderText("Set your new password");
    this->password->setAlignment(Qt::AlignmentFlag::AlignCenter);
    this->password->setEchoMode(QLineEdit::Password);

    QVBoxLayout *main_lay = new QVBoxLayout();
    main_lay->setSpacing(5);
    QPushButton *send = new QPushButton("Send");
    QObject::connect(send, SIGNAL(clicked(bool)), this, SLOT(on_click_send_button()));

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setContentsMargins(0,0,0,0);

    QVBoxLayout *main_lay_top = new QVBoxLayout();
    QVBoxLayout *main_lay_bottom = new QVBoxLayout();

    main_lay_top->setAlignment      (Qt::AlignmentFlag::AlignTop);
    main_lay_bottom->setAlignment   (Qt::AlignmentFlag::AlignBottom);

    main_lay_top->addWidget(login_label);
    main_lay_top->addWidget(this->login);
    main_lay_top->addWidget(pw_label);
    main_lay_top->addWidget(this->password);

    main_lay_bottom->addWidget(line);
    main_lay_bottom->addWidget(send);

    main_lay->addLayout(main_lay_top);
    main_lay->addLayout(main_lay_bottom);

    this->setLayout(main_lay);
    QObject::connect(this, SIGNAL(signal_send_answer_resault(QString, QString)), this, SLOT(accept_result(QString, QString)));
}

gui_reg_area::~gui_reg_area()
{
    this->login->deleteLater();
    this->password->deleteLater();
}

void gui_reg_area::on_click_send_button()
{
    if(login->text().contains('@') && login->text().contains('.'))
    {
        emit signal_create_new_user(this->login->text(), this->password->text());
    }
    else
    {
        this->setEnabled(false);
        this->login->clear();
        this->password->clear();
        QDialog *win = new QDialog();
        win->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        QScreen *screen = QApplication::screens().at(0);
        QSize size = screen->availableSize();
        win->move(size.width()/2 - 125 + 33, size.height()/2 - 110 + 80);
        QVBoxLayout *lay = new QVBoxLayout();
        QLabel *label = new QLabel("Please enter Email!");
        label->setStyleSheet("QLabel {color : red;}");
        QPushButton *button = new QPushButton("OK");
        QObject::connect(button, SIGNAL(clicked()), win, SLOT(close()));
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(unlock_form()));
        lay->addWidget(label);
        lay->addWidget(button);
        win->setLayout(lay);
        win->show();
    }
}

void gui_reg_area::accept_result(QString req , QString cmd)
{
    if(cmd == "new_user")
    {
        QDialog *win = new QDialog();
        win->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        QScreen *screen = QApplication::screens().at(0);
        QSize size = screen->availableSize();
        win->move(size.width()/2 - 125 + 60, size.height()/2 - 110 + 80);
        QVBoxLayout *lay = new QVBoxLayout();
        QLabel *label = new QLabel();
        QPushButton *button = new QPushButton("OK");
        QObject::connect(button, SIGNAL(clicked()), win, SLOT(close()));
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
