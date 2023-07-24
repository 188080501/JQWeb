PRO_PATH = $$PWD
TARGET = JQText

include( $$PWD/../JQWebCommon/JQWebCommon.pri )

HEADERS += \
    $$PWD/cpp/helper.hpp

SOURCES += \
    $$PWD/cpp/main.cpp

RESOURCES += \
    $$PWD/qml/qml.qrc
