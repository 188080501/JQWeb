// Qt lib import
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

// Project lib import
#include "jqwebcommon.h"
#include "helper.h"

int main(int argc, char **argv)
{
    QGuiApplication app( argc, argv );

    JQWebCommon::init( &app );

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty( "Helper", new Helper );
    engine.load( QUrl( QStringLiteral( "qrc:/qml/main.qml" ) ) );

    return app.exec();
}
