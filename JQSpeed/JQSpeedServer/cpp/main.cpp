// Qt lib import
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

// Project lib import
#include "helper.h"

int main(int argc, char **argv)
{
    QCoreApplication app( argc, argv );

    qSetMessagePattern( "%{time hh:mm:ss.zzz}: %{message}" );

    Helper helper;
    if ( !helper.init() )
    {
        qDebug() << "init error";
        return -1;
    }

    qDebug() << "server init succeed";

    return app.exec();
}
