#ifndef HELPER_H_
#define HELPER_H_

// Qt lib import
#include <QDebug>
#include <QDateTime>

class Helper: public QObject
{
    Q_OBJECT

public:
    Helper() = default;

    virtual ~Helper() override = default;

public slots:
    QString versionInfo();

    QString getWebPrompt(const QString &title, const QString &text);
};

#endif//HELPER_H_
