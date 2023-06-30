import QtQuick
import QtQuick.Window

Window {
    id: window
    visible: true
    width: 720
    height: 720
    title: "JQRing"
    color: "#000e27"

    property int fps: 0
    property int renderCount: 0

    Component.onCompleted: {
        Qt.callLater( function(){
            infoLabel.visible = true;
            loader.active = true;
        } );
    }

    Connections {
        target: window

        function onAfterRendering() {
            ++window.renderCount;
        }
    }

    Timer {
        interval: 1000
        repeat: true
        running: true

        onTriggered: {
            window.fps = window.renderCount;
            window.renderCount = 0;
        }
    }

    Loader {
        id: loader
        anchors.centerIn: parent
        width: 800
        height: 800
        active: false
        asynchronous: true

        sourceComponent: Ring {
            id: connecting
        }
    }

    Text {
        id: infoLabel
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        visible: false
        color: "#ffffff"
        renderType: Text.QtRendering
        font.pixelSize: 15

        text: {
            var result = "";

            result += "FPS: " + window.fps;
        }
    }
}
