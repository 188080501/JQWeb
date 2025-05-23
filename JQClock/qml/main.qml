﻿import QtQuick
import QtQuick.Window

Window {
    id: window
    width: 640
    height: 480
    visible: true
    color: "#000000"

    property real fontSize: window.width * 0.2

    MouseArea {
        anchors.fill: parent

        property bool flag: false

        onDoubleClicked: {
            flag = !flag;
            if ( flag )
            {
                Helper.showFullScreen( window );
            }
            else
            {
                Helper.showNormal( window );
            }
        }
    }

    Row {
        anchors.centerIn: parent
        spacing: fontSize * 0.08

        Text {
            id: hourLabel
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: fontSize
            font.family: "Noto Mono"
            color: "#ffffff"
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: fontSize * -0.08
            font.pixelSize: fontSize
            color: "#ffffff"
            text: ":"
        }

        Text {
            id: minuteLabel
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: fontSize
            font.family: "Noto Mono"
            color: "#ffffff"
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: fontSize * -0.08
            font.pixelSize: fontSize
            color: "#ffffff"
            text: ":"
        }

        Text {
            id: secondLabel
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: fontSize
            font.family: "Noto Mono"
            color: "#ffffff"
        }
    }

    Timer {
        interval: 500
        repeat: true
        triggeredOnStart: true
        running: true

        onTriggered: {
            hourLabel.text   = Helper.currentHourString();
            minuteLabel.text = Helper.currentMinuteString();
            secondLabel.text = Helper.currentSecondString();
        }
    }
}
