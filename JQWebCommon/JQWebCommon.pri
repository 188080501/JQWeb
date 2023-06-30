TEMPLATE = app

QT *= core gui qml quick

INCLUDEPATH *= \
    $$PWD/cpp

HEADERS *= \
    $$PWD/cpp/jqwebcommon.h

SOURCES *= \
    $$PWD/cpp/jqwebcommon.cpp

RESOURCES *= \
    $$PWD/fonts/jqwebcommonfonts.qrc

wasm : !isEmpty( PRO_PATH ) {

    equals( QT_VERSION, 6.5.1 ) {

        exists( $$PRO_PATH/shell/copy_wasm_release.bat ) : CONFIG( release, debug | release ) {

            QMAKE_POST_LINK *= $$PRO_PATH/shell/copy_wasm_release.bat $$escape_expand(\\n\\t)
        }
    }
}
