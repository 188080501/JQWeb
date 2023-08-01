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
EM_JS(char*, getWebPromptJS, (const char *titleStr, const char *textStr), {
    var result = prompt( UTF8ToString( titleStr ), UTF8ToString( textStr ) );
    if ( !result )
    {
        return null;
    }

    var lengthBytes      = lengthBytesUTF8( result ) + 1;
    var stringOnWasmHeap = _malloc( lengthBytes );

    stringToUTF8( result, stringOnWasmHeap, lengthBytes );

    return stringOnWasmHeap;
});

EM_JS(char*, getWebCookieJS, (const char *name), {
    var result = document.cookie.match( new RegExp( UTF8ToString( name ) + '=([^;]+)' ) );
    if ( !result )
    {
        return null;
    }

    result = decodeURIComponent( result[ 1 ] );

    var lengthBytes      = lengthBytesUTF8( result ) + 1;
    var stringOnWasmHeap = _malloc( lengthBytes );

    stringToUTF8( result, stringOnWasmHeap, lengthBytes );

    return stringOnWasmHeap;
});

EM_JS(void, setWebCookieJS, (const char *name, const char *value, const int days), {
    var expires = "";
    if ( days )
    {
        var date = new Date();
        date.setTime( date.getTime() + (days * 24 * 60 * 60 * 1000) );
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = UTF8ToString( name ) + "=" + UTF8ToString( value ) + expires + "; path=/";
});
#endif

QString Helper::versionInfo()
{
    return qVersion();
}

QString Helper::getWebPrompt(const QString &title, const QString &text)
{
#ifdef Q_OS_WASM
    auto resultPtr = getWebPromptJS( title.toUtf8().data(), text.toUtf8().data() );
    if ( !resultPtr ) { return { }; }

    const QString result = resultPtr;
    free( reinterpret_cast< void * >( resultPtr ) );

    return result;
#else
    Q_UNUSED( title );
    return text;
#endif
}

QString Helper::getWebCookie(const QString &name)
{
#ifdef Q_OS_WASM
    auto resultPtr = getWebCookieJS( name.toUtf8().constData() );
    if ( !resultPtr ) { return { }; }

    const QString result = QByteArray::fromBase64( resultPtr );
    free( reinterpret_cast< void * >( resultPtr ) );

    return result;
#else
    QSettings settings( "JQWeb", "JQText" );
    return settings.value( name ).toString();
#endif
}

void Helper::setWebCookie(const QString &name, const QString &value, const int days)
{
#ifdef Q_OS_WASM
    return setWebCookieJS( name.toUtf8().constData(), value.toUtf8().toBase64().constData(), days );
#else
    Q_UNUSED( days );
    QSettings settings( "JQWeb", "JQText" );
    settings.setValue( name, value );
#endif
}
