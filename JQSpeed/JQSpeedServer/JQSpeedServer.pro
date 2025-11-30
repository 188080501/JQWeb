PRO_PATH = $$PWD
TARGET = JQSpeedServer

QT *= websockets

CONFIG += console

include( $$PWD/../../JQWebCommon/JQWebCommon.pri )

INCLUDEPATH *= \
    $$PWD/../JQSpeedClient/cpp

HEADERS += \
    $$PWD/cpp/helper.h \
    $$PWD/../JQSpeedClient/cpp/config.h

SOURCES += \
    $$PWD/cpp/helper.cpp \
    $$PWD/cpp/main.cpp

win32-msvc {
    RC_ICONS = $$PWD/icon/icon.ico
}
