#ifndef SERVER_TH_H
#define SERVER_TH_H

#include <QThread>
#include <QObject>
#include "server.h"

class server_th : public QThread
{
    Q_OBJECT
public:
    explicit server_th(QObject *parent = nullptr);
    void run() override;
};

#endif // SERVER_TH_H
