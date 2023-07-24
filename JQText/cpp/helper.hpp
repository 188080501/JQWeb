#ifndef HELPER_HPP_
#define HELPER_HPP_

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
    QString versionInfo()
    {
        return qVersion();
    }
};

#endif//HELPER_HPP_
