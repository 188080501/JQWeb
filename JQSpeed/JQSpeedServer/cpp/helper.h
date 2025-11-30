#ifndef HELPER_H_
#define HELPER_H_

// Qt lib import
#include <QDebug>
#include <QDateTime>
#include <QWebSocket>
#include <QWebSocketServer>

class Helper: public QObject
{
    Q_OBJECT

public:
    Helper();

    virtual ~Helper() override = default;

public:
    bool init();

private:
    void onNewConnection();

    void onDisconnected(QWebSocket *socket);

    void onTextMessageReceived(QWebSocket *socket, const QString &message);

    void onBinaryMessageReceived(QWebSocket *socket, const QByteArray &message);

private:
    QWebSocketServer server_;
};

#endif//HELPER_H_
