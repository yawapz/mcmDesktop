#include "miner_json_reader.h"

miner_json_reader::miner_json_reader(QObject *parent)
    : QObject{parent}
{

}

QString miner_json_reader::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    return cmd->readAll().data();
}

void miner_json_reader::get_miner_json()
{
    this->manager = new QNetworkAccessManager();
    QObject::connect(this->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(read_reply(QNetworkReply*)));
    QUrl url("http://127.0.0.1");
    url.setPort(this->port);

    // process name
    QString gminer = "pidof miner";
    QString lolminer = "pidof lolMiner";

    if(!linux_terminal(gminer).isEmpty())
    {
        url.setPath("/stat");
    }
    QNetworkRequest req(url);
    this->manager->get(req);
}

void miner_json_reader::read_reply(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        return;
    }

    QByteArray bArrayReply = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(bArrayReply);

    if(json.isNull())
    {
        return;
    }
    this->main_json_file = json.object();
    emit this->signal_transport_json(this->main_json_file);
}
