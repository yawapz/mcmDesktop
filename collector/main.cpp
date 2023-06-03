#include <QCoreApplication>
#include "worker_data_builder.h"
#include "config.h"
#include "config_struct.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //worker_data_builder *b = new worker_data_builder();
    //b->get_new_data();

    config conf;
    qDebug() << conf.get_conf().version;

    return a.exec();
}
