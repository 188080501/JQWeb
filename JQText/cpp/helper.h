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

    QString getWebCookie(const QString &name);

    void setWebCookie(const QString &name, const QString &value, const int days = 7);
};

#endif//HELPER_H_
