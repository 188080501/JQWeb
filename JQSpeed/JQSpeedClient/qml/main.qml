import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window {
    id: window
    width: 640
    height: 480
    visible: true
    color: "#131a24"

    Rectangle {
        id: serverHostContains
        width: 300
        height: 85
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -140
        color: "#00000000"
        border.width: 2
        border.color: ( Helper.isConnected ) ? ( "#4CAF50" ) : ( "#9E9E9E" )
        radius: 10

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 20
            color: "#ffffff"
            font.pixelSize: 18
            text: Helper.serverHost
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 50
            color: serverHostContains.border.color
            font.pixelSize: 14
            text: ( Helper.isConnected ) ? ( "已连接" ) : ( "连接中" )
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: serverHostContains.bottom
        anchors.topMargin: 40
        spacing: 20

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 65
            width: 190
            color: "#ffffff"
            text: {
                if ( Helper.isConnected && ( Helper.latency >= 0 ) )
                {
                    if ( Helper.latency === 0 )
                    {
                        return "延迟: <1 ms";
                    }

                    return "延迟: " + Helper.latency + " ms";
                }
                else
                {
                    return "延迟: N/A";
                }
            }

            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.left
                anchors.rightMargin: 12
                source: "qrc:/images/Latency.png"
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 10
            spacing: 100

            Text {
                color: "#ffffff"
                text: "下载"

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.left
                    anchors.rightMargin: 12
                    source: "qrc:/images/Download.png"
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: -20
                    anchors.top: parent.bottom
                    anchors.topMargin: 10
                    color: "#ffffff"
                    text: {
                        if ( Helper.isConnected && ( Helper.downloadSpeed >= 0 ) )
                        {
                            return Helper.downloadSpeed.toFixed( 1 ) + " Mbps";
                        }
                        else
                        {
                            return "--";
                        }
                    }
                }
            }

            Text {
                color: "#ffffff"
                text: "上传"

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.left
                    anchors.rightMargin: 12
                    source: "qrc:/images/Upload.png"
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: -20
                    anchors.top: parent.bottom
                    anchors.topMargin: 10
                    color: "#ffffff"
                    text: {
                        if ( Helper.isConnected && ( Helper.uploadSpeed >= 0 ) )
                        {
                            return Helper.uploadSpeed.toFixed( 1 ) + " Mbps";
                        }
                        else
                        {
                            return "--";
                        }
                    }
                }
            }
        }

        Item {
           width: 1
           height: 30
        }

        MouseArea {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 100
            height: 100
            enabled: Helper.isConnected && !Helper.isMeasuringSpeed

            onClicked: {
                Helper.startMeasureDownloadSpeed();
            }

            Rectangle {
                anchors.fill: parent
                color: "#00000000"
                border.width: 2
                radius: 50
                border.color: {
                    if ( !enabled ) { return "#9E9E9E"; }

                    if ( !Helper.isConnected )
                    {
                        return "#9E9E9E";
                    }

                    if ( Helper.isMeasuringSpeed )
                    {
                        return "#FFC107";
                    }
                    else
                    {
                        return "#4CAF50";
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                color: ( Helper.isConnected ) ? ( "#ffffff" ) : ( "#9E9E9E" )
                text: ( Helper.isMeasuringSpeed ) ? ( "测试中" ) : ( "测试" )
            }
        }
    }

    Item {
        id: progressColumn
        anchors.bottom: parent.bottom
        width: parent.width
        height: 20

        Item {
            width: progressColumn.width * Math.max( 0, Helper.downloadSpeedTestProgress )
            height: 10
            clip: true

            Image {
                width: progressColumn.width
                height: 10
                source: "qrc:/images/DownloadProgress.png"
            }
        }

        Item {
            y: 10
            width: progressColumn.width * Math.max( 0, Helper.uploadSpeedTestProgress )
            height: 10
            clip: true

            Image {
                width: progressColumn.width
                height: 10
                source: "qrc:/images/UploadProgress.png"
            }
        }
    }
}
