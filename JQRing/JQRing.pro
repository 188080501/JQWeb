PRO_PATH = $$PWD
TARGET = JQRing

include( $$PWD/../JQWebCommon/JQWebCommon.pri )

SOURCES += \
    $$PWD/cpp/main.cpp

RESOURCES += \
    $$PWD/qml/qml.qrc \
    $$PWD/images/images.qrc

win32-msvc {
    RC_ICONS = $$PWD/icon/icon.ico
}
