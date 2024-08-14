TEMPLATE = app

QT *= core gui qml quick quickcontrols2

INCLUDEPATH *= \
    $$PWD/cpp

HEADERS *= \
    $$PWD/cpp/jqwebcommon.h

SOURCES *= \
    $$PWD/cpp/jqwebcommon.cpp

RESOURCES *= \
    $$PWD/fonts/jqwebcommonfonts.qrc

wasm : !isEmpty( PRO_PATH ) {

    versionAtLeast( QT_VERSION, 6.8.0 ) : versionAtMost( QT_VERSION, 6.8.3 ) {

        exists( $$PRO_PATH/shell/copy_wasm_release.bat ) : CONFIG( release, debug | release ) {

            QMAKE_POST_LINK *= $$PRO_PATH/shell/copy_wasm_release.bat $$escape_expand(\\n\\t)
        }
    }
}
