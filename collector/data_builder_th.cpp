#include "data_builder_th.h"

data_builder_th::data_builder_th()
{
}

void data_builder_th::run()
{
    //while(true)
    {
        worker_data_builder *builder = new worker_data_builder();
        connect(builder, SIGNAL(signal_send_worker_data(WORKER)), this, SIGNAL(signal_send_worker_data(WORKER)));
        builder->get_new_data();

        builder->deleteLater();
        this->wait(2 * 1000);
    }
}
