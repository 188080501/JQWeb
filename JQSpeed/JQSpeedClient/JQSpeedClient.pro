PRO_PATH = $$PWD
TARGET = JQSpeed

QT *= websockets

include( $$PWD/../../JQWebCommon/JQWebCommon.pri )

HEADERS += \
    $$PWD/cpp/helper.h \
    $$PWD/cpp/config.h

SOURCES += \
    $$PWD/cpp/helper.cpp \
    $$PWD/cpp/main.cpp

RESOURCES += \
    $$PWD/qml/qml.qrc \
    $$PWD/images/images.qrc

win32-msvc {
    RC_ICONS = $$PWD/icon/icon.ico
}
