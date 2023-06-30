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
    QString currentHourString()
    {
        return QDateTime::currentDateTime().toString( "hh" );
    }

    QString currentMinuteString()
    {
        return QDateTime::currentDateTime().toString( "mm" );
    }

    QString currentSecondString()
    {
        return QDateTime::currentDateTime().toString( "ss" );
    }
};

#endif//HELPER_HPP_
