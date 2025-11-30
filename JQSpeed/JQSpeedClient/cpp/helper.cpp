#include "helper.h"

// Qt lib import
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>

// Project lib import
#include "jqwebcommon.h"
#include "config.h"

// WASM lib import
#ifdef Q_OS_WASM
#   include <emscripten.h>
#   include <emscripten/val.h>
#endif

Helper::Helper()
{
    connect( &checkTimer_, &QTimer::timeout, this, &Helper::onCheck );
    checkTimer_.start( 2000 );

    connect( &socket_, &QWebSocket::connected, this, &Helper::onCheck );
    connect( &socket_, &QWebSocket::textMessageReceived, this, &Helper::onTextMessageReceived );
    connect( &socket_, &QWebSocket::binaryMessageReceived, this, &Helper::onBinaryMessageReceived );

    QTimer::singleShot( 0, this, &Helper::onCheck );

#ifdef Q_OS_WASM
    this->setServerHost( QUrl( emscripten::val::global( "location" )[ "href" ].as<std::string>().c_str() ).host() );
#else
    this->setServerHost( "127.0.0.1" );
#endif

    if ( const auto host = JQWebCommon::commandLineParser( "serverHost" ); !host.isEmpty() )
    {
        this->setServerHost( host );
    }

    qDebug() << "serverHost:" << this->serverHost();
}

void Helper::startMeasureDownloadSpeed()
{
    this->setIsMeasuringSpeed( true );
    this->setDownloadSpeed( -1.0f );
    this->setDownloadSpeedTestProgress( 0.0f );
    this->setUploadSpeed( -1.0f );
    this->setUploadSpeedTestProgress( 0.0f );

    binaryReceivedCounter_ = 0;

    QJsonObject requestData;
    requestData[ "action" ]     = "downloadSpeedTest";
    requestData[ "clientTime" ] = QString::number( QDateTime::currentMSecsSinceEpoch() );

    this->sendJsonTextMessage( requestData );
}

void Helper::startMeasureUploadSpeed()
{
    this->setIsMeasuringSpeed( true );
    this->setUploadSpeed( -1.0f );
    this->setUploadSpeedTestProgress( 0.0f );

    binaryReceivedCounter_ = 0;

    // 生成空数据
    QByteArray data;
    data.resize( uploadTestBlockSize );

    for ( auto sendIndex = 0; sendIndex < uploadTestBlockCount; ++sendIndex )
    {
        socket_.sendBinaryMessage( data );
    }

    QJsonObject replyData;
    replyData[ "action" ]     = "uploadSpeedTest";
    replyData[ "clientTime" ] = QString::number( QDateTime::currentMSecsSinceEpoch() );
    replyData[ "byteCount" ]  = uploadTestBlockSize * uploadTestBlockCount;

    socket_.sendTextMessage( QJsonDocument( replyData ).toJson( QJsonDocument::Compact ) );
}

void Helper::onCheck()
{
    if ( socket_.state() == QAbstractSocket::UnconnectedState )
    {
        socket_.open( QUrl( QString( "ws://%1:%2" ).arg( this->serverHost(), QString::number( defaultWebSocketPort ) ) ) );
    }
    else if ( socket_.state() == QAbstractSocket::ConnectedState )
    {
        if ( !this->isMeasuringSpeed() )
        {
            QJsonObject requestData;
            requestData[ "action" ]     = "ping";
            requestData[ "clientTime" ] = QString::number( QDateTime::currentMSecsSinceEpoch() );

            this->sendJsonTextMessage( requestData );
        }
    }

    if ( socket_.state() == QAbstractSocket::ConnectedState )
    {
        this->setIsConnected( true );
    }
    else
    {
        this->setIsConnected( false );
        this->setLatency( -1 );
    }
}

void Helper::sendJsonTextMessage(const QJsonObject &requestData)
{
    socket_.sendTextMessage( QJsonDocument( requestData ).toJson( QJsonDocument::Compact ) );
}

void Helper::onTextMessageReceived(const QString &message)
{
    // qDebug() << "onTextMessageReceived:" << message.toUtf8().constData();

    auto responseData = QJsonDocument::fromJson( message.toUtf8() ).object();
    if ( responseData.isEmpty() ) { return; }

    const auto action = responseData .value( "action" ).toString();
    if ( action.isEmpty() ) { return; }

    if ( action == "ping" )
    {
        const auto clientTime  = responseData.value( "clientTime" ).toString().toLongLong();
        const auto currentTime = QDateTime::currentMSecsSinceEpoch();
        const auto latency     = currentTime - clientTime;

        // qDebug() << "ping latency:" << latency;

        if ( ( latency < 0 ) || ( latency > 10000000 ) )
        {
            socket_.close();

            this->setIsConnected( false );
            this->setLatency( -1 );

            return;
        }

        this->setLatency( latency );
    }
    else if ( action == "downloadSpeedTest" )
    {
        const auto clientTime  = responseData.value( "clientTime" ).toString().toLongLong();
        const auto currentTime = QDateTime::currentMSecsSinceEpoch();
        const auto elapsedTime = currentTime - clientTime;

        const auto byteCount     = responseData.value( "byteCount" ).toInt();
        const auto mbitPerSecond = byteCount * 8.0f / 1000.0f / 1000.0f / ( elapsedTime / 1000.0 );

        qDebug().noquote() << "download test result: data" << byteCount << "bytes, elapsed:" << elapsedTime << "ms, speed:" << QString::number( mbitPerSecond, 'f', 1 ) << "Mbps";

        this->setDownloadSpeed( mbitPerSecond );
        this->setDownloadSpeedTestProgress( 1.0f );

        this->startMeasureUploadSpeed();
    }
    else if ( action == "uploadSpeedTest" )
    {
        const auto clientTime  = responseData.value( "clientTime" ).toString().toLongLong();
        const auto currentTime = QDateTime::currentMSecsSinceEpoch();
        const auto elapsedTime = currentTime - clientTime;

        const auto byteCount     = responseData.value( "byteCount" ).toInt();
        const auto mbitPerSecond = byteCount * 8.0f / 1000.0f / 1000.0f / ( elapsedTime / 1000.0 );

        qDebug().noquote() << "upload test result: data" << byteCount << "bytes, elapsed:" << elapsedTime << "ms, speed:" << QString::number( mbitPerSecond, 'f', 1 ) << "Mbps";

        this->setUploadSpeed( mbitPerSecond );
        this->setUploadSpeedTestProgress( 1.0f );

        this->setIsMeasuringSpeed( false );
    }
    else if ( action == "binaryReceivedConfirm" )
    {
        if ( this->isMeasuringSpeed() )
        {
            binaryReceivedCounter_ += responseData[ "messageSize" ].toInt();

            this->setUploadSpeedTestProgress( binaryReceivedCounter_ / static_cast< float >( uploadTestBlockSize * uploadTestBlockCount ) );
        }
    }
    else
    {
        // qDebug() << "unknown action:" << action;
    }
}

void Helper::onBinaryMessageReceived(const QByteArray &message)
{
    if ( this->isMeasuringSpeed() )
    {
        binaryReceivedCounter_ += message.size();

        this->setDownloadSpeedTestProgress( binaryReceivedCounter_ / static_cast< float >( downloadTestBlockSize * downloadTestBlockCount ) );
    }
}
