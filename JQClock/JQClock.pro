PRO_PATH = $$PWD
TARGET = JQClock

include( $$PWD/../JQWebCommon/JQWebCommon.pri )

HEADERS += \
    $$PWD/cpp/helper.hpp

SOURCES += \
    $$PWD/cpp/main.cpp

RESOURCES += \
    $$PWD/qml/qml.qrc

win32-msvc {
    RC_ICONS = $$PWD/icon/icon.ico
}
