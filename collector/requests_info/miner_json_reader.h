#ifndef MINER_JSON_READER_H
#define MINER_JSON_READER_H

#include <QObject>
#include <QProcess>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>

class miner_json_reader : public QObject
{
    Q_OBJECT
public:
    explicit miner_json_reader(QObject *parent = nullptr);
    void get_miner_json();
    ~miner_json_reader();
private:
    int port = 10050;
    QNetworkAccessManager* manager;
    QJsonObject main_json_file;
    QString linux_terminal(QString &request);
signals:
    void signal_transport_json(QJsonObject);
private slots:
    void read_reply(QNetworkReply*);
};

#endif // MINER_JSON_READER_H
