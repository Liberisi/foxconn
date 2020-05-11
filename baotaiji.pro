#-------------------------------------------------
#
# Project created by QtCreator 2019-08-13T10:17:05
#
#-------------------------------------------------
QT       += axcontainer
QT       += core gui
QT       += serialport
QT       += winextras
QT       += network
QT       += sql
QT       += xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = baotaiji
TEMPLATE = app

INCLUDEPATH += $$(HALCONROOT)/include/
INCLUDEPATH += $$(OPENCV_PATH)/build/include/
INCLUDEPATH += $$(PYLON_DEV_DIR)/include/
INCLUDEPATH += $$(MELSEC_PATH)/Act/Include/
INCLUDEPATH += ./ssvision/

contains(QT_ARCH, i386) {
    message("Win32")

LIBS += -lOle32 -lOleAut32

LIBS += -L$$(HALCONROOT)/lib/x86sse2-win32/ \
        -lhalconcpp

LIBS += -L$$(PYLON_DEV_DIR)/lib/Win32/ \
        -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0

CONFIG( Debug ) {
    LIBS += -L./ssvision/debug/ \
            -lssvision
    LIBS += -L$$(OPENCV_PATH)/build/x86/vc12/lib/ \
            -lopencv_world300d
} else {
    LIBS += -L./ssvision/release/ \
            -lssvision
    LIBS += -L$$(OPENCV_PATH)/build/x86/vc12/lib/ \
            -lopencv_world300
}

} else {
    message("x64")

LIBS += -L$$(HALCONROOT)/lib/$$(HALCONARCH)/ \
        -lhalconcpp

LIBS += -L$$(PYLON_DEV_DIR)/lib/x64/ \
        -lGenApi_MD_VC120_v3_0_Basler_pylon_v5_0

CONFIG( Debug ) {
    LIBS += -L./ssvision/debug/ \
            -lssvision
    LIBS += -L$$(OPENCV_PATH)/build/x64/vc12/lib/ \
            -lopencv_world300d
} else {
    LIBS += -L./ssvision/release/ \
            -lssvision
    LIBS += -L$$(OPENCV_PATH)/build/x64/vc12/lib/ \
            -lopencv_world300
}
}



SOURCES += main.cpp\
    product.cpp \
    about.cpp \
    baojitai.cpp \
    saveconfig.cpp \
    save_config_dialog.cpp \
    communication.cpp \
    ActUtlType.cpp \
    frame_dialog.cpp \
    datetime_filesystem.cpp \
    item_information_center.cpp \
    halcon_tools.cpp \
    reading_code_config.cpp \
    position_calibrate.cpp \
    halcon_widget.cpp \
    camera_config_dialog.cpp \
    plc_config_dialog.cpp \
    main_window.cpp \
    location_config.cpp \
    fidparser.cpp \
    frameparam.cpp \
    fid_cmc_socket.cpp \
    material_product_map.cpp \
    material_product_dialog.cpp \
    msleepsetting.cpp \
    serial_port_manager.cpp \
    support_location_select_region.cpp

HEADERS  += \
    product.h \
    resource.h \
    about.h \
    baojitai.h \
    saveconfig.h \
    save_config_dialog.h \
    communication.h \
    serial_port_manager.h \
    ActUtlType.h \
    frame_dialog.h \
    datetime_filesystem.h \
    item_information_center.h \
    halcon_tools.h \
    reading_code_config.h \
    position_calibrate.h \
    halcon_widget.h \
    camera_config_dialog.h \
    plc_config_dialog.h \
    main_window.h \
    location_config.h \
    fidparser.h \
    frameparam.h \
    fid_cmc_socket.h \
    material_product_map.h \
    material_product_dialog.h \
    msleepsetting.h \
    xlsx.h \
    support_location_select_region.h

FORMS    += \
    config_save.ui \
    about.ui \
    communication.ui \
    frame_dialog.ui \
    reading_code_config.ui \
    camera_config_dialog.ui \
    position_calibrate.ui \
    plc_config_dialog.ui \
    main_window.ui \
    location_config.ui \
    material_product_dialog.ui

DISTFILES +=

RESOURCES +=
