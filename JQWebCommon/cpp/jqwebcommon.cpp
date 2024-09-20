#include "jqwebcommon.h"

// Qt lib import
#include <QGuiApplication>
#include <QFontDatabase>
#include <QCommandLineParser>
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

QMap< QString, QString > urlQueryParser(const QString url)
{
    const auto indexForQueryStart = url.indexOf( "?" );
    if ( indexForQueryStart < 0 ) { return { }; }

    QMap< QString, QString > result;

    auto lines = QUrl::fromEncoded( url.mid( indexForQueryStart + 1 ).toUtf8() ).toString().split( "&" );

    for ( const auto &line_: std::as_const( lines ) )
    {
        auto line = line_;
        line.replace( "%5B", "[" );
        line.replace( "%5D", "]" );
        line.replace( "%7B", "{" );
        line.replace( "%7D", "}" );
        line.replace( "%5E", "^" );
        line.replace( "%3A", ":" );
        line.replace( "%2F", "/" );

        auto indexOf = line.indexOf( "=" );
        if ( indexOf > 0 )
        {
            result[ line.mid( 0, indexOf ) ] = line.mid( indexOf + 1 );
        }
    }

    return result;
}

QString commandLineParser(const QString &key)
{
#ifdef Q_OS_WASM
    return urlQueryParser( emscripten::val::global( "location" )[ "href" ].as<std::string>().c_str() )[ key ];
#else
    QCommandLineParser parser;
    parser.parse( qApp->arguments() );

    const auto positionalArguments = parser.positionalArguments();

    for ( const auto &argument: positionalArguments )
    {
        auto key_ = key + "=";

        if ( argument.startsWith( key_ ) )
        {
            return argument.mid( key_.size() );
        }

        key_ = key + "://";

        if ( argument.startsWith( key_ ) )
        {
            return argument.mid( key_.size() );
        }
    }

    return { };
#endif
}

}
