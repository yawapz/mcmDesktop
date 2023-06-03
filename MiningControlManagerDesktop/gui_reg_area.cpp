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
}

void gui_reg_area::on_click_send_button()
{
    qDebug() << "Реализовать ограничения по знакам и паролю!";
    qDebug() << "Реализовать отправку и регистрацию юзера на сервере!";
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}
