#include "motherboard.h"

motherboard::motherboard()
{
    this->request1 = "inxi -M | grep model";
    this->request2 = "inxi -M | grep date";

    std::string result_MB1 = this->linux_terminal(this->request1).toStdString();
    while (result_MB1.find("\u0003") != -1)
    {
        result_MB1.erase(result_MB1.find("\u0003"), 1);
    }
    while(result_MB1[0] == ' ')
        result_MB1.erase(result_MB1.begin());
    result_MB1.erase(0, result_MB1.find_first_of(' ') + 1);
    result_MB1.erase(result_MB1.find("12model"), 9);
    result_MB1.erase(result_MB1.find("12v"));
    result_MB1.erase(result_MB1.rfind(' '));

    std::string result_MB2 = this->linux_terminal(this->request2).toStdString();
    result_MB2.erase(result_MB2.find('\n'));
    while (result_MB2.find("\u0003") != -1)
    {
        result_MB2.erase(result_MB2.find("\u0003"), 1);
    }
    while(result_MB2[0] == ' ')
        result_MB2.erase(result_MB2.begin());
    result_MB2.erase(0, result_MB2.find("12v") + 5);
    result_MB2.erase(result_MB2.find("12date"), 8);

    std::string result_MB = std::string(result_MB1.data()) + " BIOS " + result_MB2.data();
    this->info = QString::fromStdString(result_MB);
}

QString motherboard::get_info()
{
    return this->info;
}

QString motherboard::linux_terminal(QString &request)
{
    QProcess *cmd = new QProcess();
    cmd->start("bash", QStringList() << "-c" << request);
    cmd->waitForFinished();
    return cmd->readAll().data();
}
