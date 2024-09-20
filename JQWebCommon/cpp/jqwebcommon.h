#ifndef JQWEBCOMMON_H_
#define JQWEBCOMMON_H_

// Qt lib import
#include <QDebug>

class QGuiApplication;

namespace JQWebCommon
{

void init(QGuiApplication *app);

QString commandLineParser(const QString &key);

}

#endif//JQWEBCOMMON_H_
