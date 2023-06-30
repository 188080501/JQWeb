// Qt lib import
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Project lib import
#include "jqwebcommon.h"

int main(int argc, char **argv)
{
    QGuiApplication app( argc, argv );
    JQWebCommon::initFont( &app );

    QQmlApplicationEngine engine;
    engine.load( QUrl( QStringLiteral( "qrc:/qml/main.qml" ) ) );

    return app.exec();
}
