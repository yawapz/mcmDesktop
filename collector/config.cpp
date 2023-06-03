#include "config.h"

config::config(QObject *parent)
    : QObject{parent}
{
    connect(this, SIGNAL(signal_accept_new_config(conf_data)), this, SLOT(slot_write_config(conf_data)));
    QString req_gpu_count = "nvidia-smi --query-gpu=name --format=csv,noheader | wc -l";
    this->gpu_count_in_system = this->linux_terminal(req_gpu_count).toInt();
    this->read_config();
    if(!this->conf.list.empty() && this->conf.list.size() < this->gpu_count_in_system)
    {
        while (this->conf.list.size() != this->gpu_count_in_system)
        {
            this->conf.list.push_back(this->conf.list[this->conf.list.size() - 1]);
        }
        this->slot_write_config(this->conf);
    }
}

conf_data config::get_conf()
{
    return this->conf;
}

void config::file_parcer(const QJsonObject &data)
{
    if(!data.empty())
    {
        this->conf.ID = data.value("ID").toString();
        this->conf.name = data.value("name").toString();
        this->conf.server_addr = data.value("server_addr").toString();
        this->conf.version = data.value("version").toString();
        this->conf.server_port = data.value("server_port").toInt();
        this->conf.miner_port = data.value("miner_port").toInt();
        this->conf.electricity_cost = data.value("electricity_cost").toDouble();
        this->conf.list.clear();
        QJsonArray arr = data.value("list").toArray();
        for (auto el : arr)
        {
            QJsonObject el_obj = el.toObject();
            gpu_conf_data el_data;
            el_data.set_core = el_obj.value("set_core").toInt();
            el_data.set_mem = el_obj.value("set_mem").toInt();
            el_data.set_fan_speed = el_obj.value("set_fan_speed").toInt();
            el_data.set_pl = el_obj.value("set_pl").toInt();
            this->conf.list.push_back(el_data);
        }
    }
    else
    {
        this->make_std_config();
    }
}

void config::make_std_config()
{
    int default_core = 1470;
    int default_mem = 7000;
    int default_fan = 60;

    QString repl = linux_terminal("nvidia-smi --query-gpu=power.default_limit --format=csv,noheader | gawk '{print $1}'");
    QList<int> def_pl;
    QString temp = "";
    for (int i = 0; i < repl.size(); ++i)
    {
        if(repl[i] == '\n')
        {
            def_pl.push_back(temp.toInt());
            temp.clear();
        }
        else
            temp += repl[i];
    }

    QJsonArray arr;
    for (int i = 0; i < this->gpu_count_in_system; ++i)
    {
        QJsonObject gpu;
        gpu.insert("set_core", default_core);
        gpu.insert("set_mem", default_mem);
        gpu.insert("set_fan_speed", default_fan);
        gpu.insert("set_pl", def_pl[i]);
        arr.push_back(gpu);
    }

    QJsonObject obj;
    obj.insert("ID", "");
    obj.insert("name", "new_farm");
    obj.insert("server_addr", "");
    obj.insert("version", this->version);
    obj.insert("server_port", 0);
    obj.insert("miner_port", 0);
    obj.insert("electricity_cost", 0.0);
    obj.insert("list", arr);

    this->write_conf_file(obj);
    this->read_config();
}

void config::write_conf_file(QJsonObject json)
{
    QJsonDocument document(json);
    //QFileInfo file_info(this->config_path);
    //QDir::setCurrent(file_info.path());
    QFile json_file(this->config_path);
    json_file.open(QIODevice::WriteOnly | QIODevice::Text);
    json_file.write(document.toJson(QJsonDocument::Indented));
    json_file.close();
}

QString config::linux_terminal(const QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    return cmd->readAll().data();
}

void config::read_config()
{
    QString open_file_name = this->config_path;
    QFileInfo fileinfo(open_file_name);
    QDir::setCurrent(fileinfo.path());
    QFile conf_file(open_file_name);
    if (!conf_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->make_std_config();
    }
    else
    {
        QByteArray barr = conf_file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(barr));
        file_parcer(doc.object());
    }
    conf_file.close();
}

void config::slot_write_config(conf_data data)
{
    this->conf = data;

    QJsonArray arr;
    for (int i = 0; i < this->gpu_count_in_system; ++i)
    {
        QJsonObject gpu;
        gpu.insert("set_core", this->conf.list[i].set_core);
        gpu.insert("set_mem", this->conf.list[i].set_mem);
        gpu.insert("set_fan_speed", this->conf.list[i].set_fan_speed);
        gpu.insert("set_pl", this->conf.list[i].set_pl);
        arr.push_back(gpu);
    }

    QJsonObject obj;
    obj.insert("ID", this->conf.ID);
    obj.insert("name", this->conf.name);
    obj.insert("server_addr", this->conf.server_addr);
    obj.insert("version", this->conf.version);
    obj.insert("server_port", this->conf.server_port);
    obj.insert("miner_port", this->conf.miner_port);
    obj.insert("electricity_cost", this->conf.electricity_cost);
    obj.insert("list", arr);

    this->write_conf_file(obj);
}
