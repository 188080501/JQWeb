#ifndef HELPER_H_
#define HELPER_H_

// Qt lib import
#include <QDebug>
#include <QDateTime>
#include <QQuickWindow>

class Helper: public QObject
{
    Q_OBJECT

public:
    Helper() = default;

    virtual ~Helper() override = default;

public slots:
    void showFullScreen(QQuickWindow *window);

    void showNormal(QQuickWindow *window);


    QString currentHourString();

    QString currentMinuteString();

    QString currentSecondString();
};

#endif//HELPER_H_
