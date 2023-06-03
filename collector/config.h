#ifndef CONFIG_H
#define CONFIG_H

#include "config_struct.cpp"

#include <QObject>
#include <QProcess>
#include <QString>
#include <QList>
#include <QFile>
#include <QDir>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class config : public QObject
{
    Q_OBJECT
public:
    explicit config(QObject *parent = nullptr);
    conf_data get_conf();
private:
    int gpu_count_in_system;
    conf_data conf;

    void read_config();
    void file_parcer(const QJsonObject&);
    void make_std_config();
    void write_conf_file(QJsonObject);

    QString linux_terminal(const QString &request);

    QString config_path = "worker.conf";
    QString version = "0.1";
private slots:

    void slot_write_config(conf_data);

signals:
    void signal_accept_new_config(conf_data);
    void signal_send_current_config(conf_data);

};

#endif // CONFIG_H
