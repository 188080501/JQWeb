// .h include
#include "helper.h"

// WASM lib iport
#ifdef Q_OS_WASM
#   include <emscripten.h>
#   include <emscripten/html5.h>
#endif

// 定义JS的一个调用函数
#ifdef Q_OS_WASM
EM_JS(const char*, getWebPrompt2, (const char *titleStr, const char *textStr), {
    val = prompt( UTF8ToString( titleStr ), UTF8ToString( textStr ) );
    if(val == null)
    {
        val = ""
    }

    var jstring          = val;
    var lengthBytes      = lengthBytesUTF8( jstring ) + 1;
    var stringOnWasmHeap = _malloc( lengthBytes );

    stringToUTF8( jstring, stringOnWasmHeap, lengthBytes );

    return stringOnWasmHeap;
})
#endif

QString Helper::versionInfo()
{
    return qVersion();
}

QString Helper::getWebPrompt(const QString &title, const QString &text)
{
#ifdef Q_OS_WASM
    return getWebPrompt2( title.toUtf8().data(), text.toUtf8().data() );
#else
    return currentText;
#endif
}
