#-------------------------------------------------
#
# Project created by QtCreator 2019-08-13T11:40:57
#
#-------------------------------------------------

QT       += testlib
QT       += serialport
QT       += network
QT       -= gui

TARGET = ssvision
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ./
INCLUDEPATH += $$(PYLON_DEV_DIR)/include/
INCLUDEPATH += $$(OPENCV_PATH)/build/include/
INCLUDEPATH += $$(MELSEC_PATH)/Act/Include/

contains(QT_ARCH, i386) {
    message("Win32")
} else {
    message("x64")
}

SOURCES += \
    camera.cpp \
    baslercamera.cpp \
    datefilelogger.cpp \
    logger.cpp \
    serialport.cpp \
    qtserialport.cpp \
    datacode.cpp \
    robotictcpserver.cpp

HEADERS += \
    datefilelogger.h \
    logger.h \
    ssvision \
    camera.h \
    baslercamera.h \
    serialport.h \
    qtserialport.h \
    datacode.h \
    robotictcpserver.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
