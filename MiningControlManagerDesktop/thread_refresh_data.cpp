#include "thread_refresh_data.h"

//Q_DECLARE_METATYPE(QAbstractSocket::SocketState)

thread_refresh_data::thread_refresh_data(QObject *parent)
    : QThread{parent}
{
    //qRegisterMetaType <QAbstractSocket::SocketState> ("QAbstractSocket::SocketState");
    qRegisterMetaType <QAbstractSocket::SocketError> ("QAbstractSocket::SocketError");
    QObject::connect(this, SIGNAL(signal_accept_data(QString,QString,user_data)), this, SLOT(slot_accept_data(QString,QString,user_data)));
    QObject::connect(this, SIGNAL(signal_start()), this, SLOT(start()));
}

thread_refresh_data::~thread_refresh_data()
{
    this->soc->deleteLater();
}

void thread_refresh_data::run()
{
    this->soc = new QTcpSocket();
    QObject::connect(soc, SIGNAL(readyRead()), this, SLOT(slot_accept_json()));

    qDebug() << "Второй поток = " << QThread::currentThreadId();
    QByteArray *barr = new QByteArray();
    QDataStream stream(barr, QIODevice::Append);
    QString command = "get_user_data";

    stream << command;
    stream << this->login;
    if(!soc->isOpen())
        soc->connectToHost("127.0.0.1", 48048);
    soc->waitForConnected(1000);
    soc->write(*barr);
    soc->flush();
    delete barr;

    QEventLoop *loop = new QEventLoop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, loop, &QEventLoop::quit);
    t.connect(soc, SIGNAL(readyRead()), loop, SLOT(quit()));
    t.setSingleShot(true);
    t.start(5*1000); // 5 sec
    loop->exec();
    loop->deleteLater();
}

void thread_refresh_data::slot_accept_data(QString l, QString p, user_data d)
{
    this->login = l;
    this->password = p;
    this->data = d;
}

void thread_refresh_data::slot_accept_json()
{
    soc->waitForReadyRead(1000);
    QByteArray barr = soc->readAll();
    QDataStream stream(&barr, QIODevice::ReadOnly);
    QJsonObject jsonObject;
    stream >> jsonObject;
    soc->waitForDisconnected(1000);
    user_data inc_data;
    inc_data.main_json_file = jsonObject;
    inc_data.JSON_server_to_desktop_parcer();
    emit signal_send_new_data(inc_data);
    this->soc->deleteLater();
}
