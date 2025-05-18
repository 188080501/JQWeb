// .h include
#include "helper.h"

// Qt lib import
#include <QSettings>

// WASM lib iport
#ifdef Q_OS_WASM
#   include <emscripten.h>
#   include <emscripten/html5.h>
#endif

#ifdef Q_OS_WASM
EM_JS(void, wasmEnterFullScreen, (), {
    // Qt for WASM 默认把渲染目标放在 Module['canvas'] 上；
    // 如果你改过 canvasId，这里改成 document.getElementById('yourCanvasId')
    var elem = Module['canvas'] || document.body;

    if (elem.requestFullscreen)            elem.requestFullscreen();
    else if (elem.webkitRequestFullscreen) elem.webkitRequestFullscreen();
    else if (elem.mozRequestFullScreen)    elem.mozRequestFullScreen();
    else if (elem.msRequestFullscreen)     elem.msRequestFullscreen();
});

EM_JS(void, wasmExitFullScreen, (), {
    if (document.fullscreenElement ||
        document.webkitFullscreenElement ||
        document.mozFullScreenElement ||
        document.msFullscreenElement)
    {
        if (document.exitFullscreen)            document.exitFullscreen();
        else if (document.webkitExitFullscreen) document.webkitExitFullscreen();
        else if (document.mozCancelFullScreen)  document.mozCancelFullScreen();
        else if (document.msExitFullscreen)     document.msExitFullscreen();
    }
});
#endif

void Helper::showFullScreen(QQuickWindow *window)
{
#ifdef Q_OS_WASM
    Q_UNUSED(window);
    wasmEnterFullScreen();
#else
    window->showFullScreen();
#endif
}

void Helper::showNormal(QQuickWindow *window)
{
#ifdef Q_OS_WASM
    Q_UNUSED(window);
    wasmExitFullScreen();
#else
    window->showNormal();
#endif
}

QString Helper::currentHourString()
{
    return QDateTime::currentDateTime().toString( "hh" );
}

QString Helper::currentMinuteString()
{
    return QDateTime::currentDateTime().toString( "mm" );
}

QString Helper::currentSecondString()
{
    return QDateTime::currentDateTime().toString( "ss" );
}
