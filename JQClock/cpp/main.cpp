﻿// Qt lib import
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// Project lib import
#include "jqwebcommon.h"
#include "helper.hpp"

int main(int argc, char **argv)
{
    QGuiApplication app( argc, argv );

    JQWebCommon::initFont( &app );

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty( "Helper", new Helper );
    engine.load( QUrl( QStringLiteral( "qrc:/qml/main.qml" ) ) );

    return app.exec();
}
