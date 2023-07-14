#include "cpu.h"
#include "qdebug.h"

cpu::cpu()
{
    try
    {
        this->request1 = "cat /proc/cpuinfo | grep 'model name' | uniq";

        std::string result_cpu = this->linux_terminal(this->request1).toStdString();
        result_cpu.erase(0, result_cpu.find(':') + 2);
        result_cpu.erase(result_cpu.find('\n'));

        this->name = QString::fromStdString(result_cpu);

        this->request2 = "cat /sys/class/thermal/thermal_zone*/temp";
        std::string result_cpu_temperature = this->linux_terminal(this->request2).toStdString();
        result_cpu_temperature.erase(result_cpu_temperature.find('\n'));

        this->temperature = QString::number(QString::fromStdString(result_cpu_temperature).toInt() / 1000);
    } catch (std::exception ex)
    {
        qDebug() << "cpu module - " << ex.what();
    }
}

QString cpu::get_info()
{
    return this->name;
}

QString cpu::get_temperature()
{
    return this->temperature;
}

QString cpu::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    QString result = cmd->readAll().data();
    cmd->deleteLater();
    return result;
}
