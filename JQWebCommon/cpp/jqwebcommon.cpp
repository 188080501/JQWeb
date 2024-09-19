#include "jqwebcommon.h"

// Qt lib import
#include <QGuiApplication>
#include <QFontDatabase>
#include <QQuickStyle>

// WASM lib import
#ifdef Q_OS_WASM
#   include <emscripten.h>
#   include <emscripten/val.h>
#endif

namespace JQWebCommon
{

#ifdef Q_OS_WASM
void messageHandler(
    QtMsgType                 type,
    const QMessageLogContext &context,
    const QString &           log )
{
    Q_UNUSED( type );
    Q_UNUSED( context );

    switch ( type )
    {
        case QtDebugMsg:
        case QtInfoMsg:
            EM_ASM({ console.info(UTF8ToString($0)); }, log.toUtf8().constData());
            break;
        case QtWarningMsg:
            EM_ASM({ console.warn(UTF8ToString($0)); }, log.toUtf8().constData());
            break;
        case QtCriticalMsg:
        case QtFatalMsg:
            EM_ASM({ console.error(UTF8ToString($0)); }, log.toUtf8().constData());
            if (type == QtFatalMsg) { abort(); }
    }
}
#endif

void init(QGuiApplication *app)
{
    qSetMessagePattern( "%{time hh:mm:ss.zzz}: %{message}" );

#ifdef Q_OS_WASM
    qInstallMessageHandler( messageHandler );
#endif

    QFontDatabase::addApplicationFont( ":/jqwebcommonfonts/NotoMono.ttf" );
    QFontDatabase::addApplicationFont( ":/jqwebcommonfonts/MiSans-Regular.ttf" );

    QFont font( "MiSans", 12 );
    font.setHintingPreference( QFont::PreferFullHinting );
    app->setFont( font );

    QQuickStyle::setStyle( "Basic" );
}

}
