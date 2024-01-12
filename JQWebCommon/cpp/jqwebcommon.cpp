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

    QFont font( "MiSans", 12 );
    font.setHintingPreference( QFont::PreferFullHinting );
    app->setFont( font );
}

}
