#include "jqwebcommon.h"

// Qt lib import
#include <QGuiApplication>
#include <QFontDatabase>

namespace JQWebCommon
{

void initFont(QGuiApplication *app)
{
    QFontDatabase::addApplicationFont( ":/qml/NotoMono.ttf" );
    QFontDatabase::addApplicationFont( ":/jqwebcommonfonts/MiSans-Regular.ttf" );
    app->setFont( QFont( "MiSans", 11 ) );
}

}
