QT -= gui
QT += network
CONFIG += c++20
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        config.cpp \
        config_struct.cpp \
        data_builder_th.cpp \
        requests_info/cpu.cpp \
        requests_info/disk.cpp \
        gpu_struct.cpp \
        requests_info/gpu_collector.cpp \
        requests_info/ip.cpp \
        requests_info/kernel.cpp \
        requests_info/load_average.cpp \
        requests_info/mac.cpp \
        main.cpp \
        requests_info/miner_json_reader.cpp \
        requests_info/motherboard.cpp \
        requests_info/nvidia.cpp \
        requests_info/radeon.cpp \
        requests_info/ram.cpp \
        requests_info/startup_timer.cpp \
        socket.cpp \
        socket_thread.cpp \
        worker_data_builder.cpp \
        worker_struct.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    config.h \
    data_builder_th.h \
    requests_info/cpu.h \
    requests_info/disk.h \
    requests_info/gpu_collector.h \
    requests_info/ip.h \
    requests_info/kernel.h \
    requests_info/load_average.h \
    requests_info/mac.h \
    requests_info/miner_json_reader.h \
    requests_info/motherboard.h \
    requests_info/nvidia.h \
    requests_info/radeon.h \
    requests_info/ram.h \
    requests_info/startup_timer.h \
    socket.h \
    socket_thread.h \
    worker_data_builder.h
