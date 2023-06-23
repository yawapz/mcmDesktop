QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui_controller.cpp \
    gui_farm_info_area.cpp \
    gui_farm_info_worker.cpp \
    gui_farm_list_area.cpp \
    gui_farm_list_worker.cpp \
    gui_login_area.cpp \
    gui_reg_area.cpp \
    gui_user_settings.cpp \
    gui_worker_settings.cpp \
    logger/prog_logger.cpp \
    logger/thread_logger.cpp \
    main.cpp \
    mainwindow.cpp \
    thread_farm_info.cpp \
    thread_refresh_data.cpp \
    user_data.cpp

HEADERS += \
    gui_controller.h \
    gui_farm_info_area.h \
    gui_farm_info_worker.h \
    gui_farm_list_area.h \
    gui_farm_list_worker.h \
    gui_login_area.h \
    gui_reg_area.h \
    gui_user_settings.h \
    gui_worker_settings.h \
    logger/prog_logger.h \
    logger/thread_logger.h \
    mainwindow.h \
    thread_farm_info.h \
    thread_refresh_data.h \
    user_data.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
