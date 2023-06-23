#ifndef THREAD_REFRESH_DATA_H
#define THREAD_REFRESH_DATA_H

#include "user_data.h"
#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QEventLoop>
#include <QTimer>

class thread_refresh_data : public QThread
{
    Q_OBJECT
public:
    explicit thread_refresh_data(QObject *parent = nullptr);
    ~thread_refresh_data();
public slots:
    void run() override;
private:
    user_data data;
    QString login;
    QString password;
    QTcpSocket *soc;
private slots:
    void slot_accept_data(QString, QString, user_data);
    void slot_accept_json();
signals:
    void signal_send_new_data(user_data);
    void signal_accept_data(QString, QString, user_data);
    void signal_start();
};

#endif // THREAD_REFRESH_DATA_H
