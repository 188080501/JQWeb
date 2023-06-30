PRO_PATH = $$PWD
TARGET = JQRing

include( $$PWD/../JQWebCommon/JQWebCommon.pri )

SOURCES += \
    $$PWD/cpp/main.cpp

RESOURCES += \
    $$PWD/qml/qml.qrc \
    $$PWD/images/images.qrc
