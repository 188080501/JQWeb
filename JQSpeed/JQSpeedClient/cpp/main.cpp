// Qt lib import
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QNetworkProxyFactory>

// Project lib import
#include "jqwebcommon.h"
#include "helper.h"

int main(int argc, char **argv)
{
    QGuiApplication app( argc, argv );

    JQWebCommon::init( &app );
    QNetworkProxyFactory::setUseSystemConfiguration( false );

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty( "Helper", new Helper );
    engine.load( QUrl( QStringLiteral( "qrc:/qml/main.qml" ) ) );

    return app.exec();
}
