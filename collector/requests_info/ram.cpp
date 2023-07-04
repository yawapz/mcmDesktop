#include "ram.h"
#include "qdebug.h"

ram::ram()
{
    try
    {
        this->request = "inxi -m | grep total";

        std::string RAM_total = this->linux_terminal(this->request).toStdString();
        while (RAM_total.find("\u0003") != -1)
        {
            RAM_total.erase(RAM_total.find("\u0003"), 1);
        }

        int pos1 = RAM_total.find("12total") + 8;
        RAM_total.erase(0, pos1);

        int pos2 = RAM_total.find("12used") - 1;
        RAM_total.erase(pos2);

        this->ram_total = QString::fromStdString(RAM_total);

        std::string RAM_used = this->linux_terminal(this->request).toStdString();
        while (RAM_used.find("\u0003") != -1)
        {
            RAM_used.erase(RAM_used.find("\u0003"), 1);
        }

        int pos3 = RAM_used.find("12used") + 7;
        RAM_used.erase(0, pos3);

        int pos4 = RAM_used.find('(') - 1;
        RAM_used.erase(pos4);
        this->ram_used = QString::fromStdString(RAM_used);

        std::string num_str1 = this->ram_total.toStdString();
        num_str1.erase(num_str1.find(" GiB"));

        std::string num_str2 = this->ram_used.toStdString();
        num_str2.erase(num_str2.find(" GiB"));

        double num = QString::fromStdString(num_str1).toDouble() - QString::fromStdString(num_str2).toDouble();
        if (num < 1)
            this->ram_free = QString::number((num * 1024), 'f', 2) + " MiB";
        else
            this->ram_free = QString::number(num, 'f', 2) + " GiB";
    }
    catch (std::exception ex)
    {
        qDebug() << "ram module - " << ex.what();
    }
}

QString ram::get_ram_total()
{
    return this->ram_total;
}

QString ram::get_ram_used()
{
    return this->ram_used;
}

QString ram::get_ram_free()
{
    return this->ram_free;
}

QString ram::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
