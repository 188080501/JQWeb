import QtQuick
import Qt5Compat.GraphicalEffects

Rectangle {
    id: imConnecting
    width: imageSize
    height: imageSize
    opacity: 0
    color: "#000e27"

    property bool lightMode: false
    readonly property int imageSize: 800

    Component.onCompleted: {
        opacity = 1;
    }

    Behavior on opacity { NumberAnimation { duration: 1000 } }

    Item {
        id: ringContains
        width: imageSize
        height: imageSize
        visible: false

        property var ringProfile: [
            {
                source: "qrc:/images/Ring1.webp",
                horizontalCenterOffset: 8,
                verticalCenterOffset: -3
            },
            {
                source: "qrc:/images/Ring2.webp",
                horizontalCenterOffset: -3,
                verticalCenterOffset: 1
            },
            {
                source: "qrc:/images/Ring3.webp",
                horizontalCenterOffset: 0,
                verticalCenterOffset: -10
            },
            {
                source: "qrc:/images/Ring4.webp",
                horizontalCenterOffset: 1,
                verticalCenterOffset: -15
            },
            {
                source: "qrc:/images/Ring5.webp",
                horizontalCenterOffset: 77,
                verticalCenterOffset: -79
            },
            {
                source: "qrc:/images/Ring6.webp",
                horizontalCenterOffset: 1,
                verticalCenterOffset: -30
            },
            {
                source: "qrc:/images/Ring7.webp",
                horizontalCenterOffset: 6,
                verticalCenterOffset: 27
            },
            {
                source: "qrc:/images/Ring8.webp",
                horizontalCenterOffset: 10,
                verticalCenterOffset: -61
            },
            {
                source: "qrc:/images/Ring9.webp",
                horizontalCenterOffset: 3,
                verticalCenterOffset: 11
            },
            {
                source: "qrc:/images/Ring10.webp",
                horizontalCenterOffset: 1,
                verticalCenterOffset: -20
            },
            {
                source: "qrc:/images/Ring11.webp",
                horizontalCenterOffset: 4,
                verticalCenterOffset: 19
            },
            {
                source: "qrc:/images/Ring12.webp",
                horizontalCenterOffset: -16,
                verticalCenterOffset: -33
            }
        ]

        Repeater {
            model: ( imConnecting.lightMode ) ? ( 1 ) : ( ringContains.ringProfile.length )

            Item {
                id: imageContains
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                z: index

                NumberAnimation on rotation {
                    easing.type: Easing.InOutQuad
                    from: 0
                    to: ( ( Math.random() > 0.5 ) ? ( 360 ) : ( -360 ) ) * Math.random() / 2 + 180
                    duration: 10000 + Math.random() * 20000
                    loops: 1
                    running: true

                    onStopped: {
                        if ( ringImage.opacity < 0.01 )
                        {
                            ringImage.opacity = 0.42;
                        }
                        else
                        {
                            ringImage.opacity = ( Math.random() > 0.2 ) ? ( 0.42 ) : ( 0 );
                        }

                        from = imageContains.rotation;
                        to = ( ( Math.random() > 0.5 ) ? ( 360 ) : ( -360 ) ) * ( Math.random() / 2 ) + 180;
                        duration = 10000 + Math.random() * 20000;
                        start();
                    }
                }

                Image {
                    id: ringImage
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: ringContains.ringProfile[ index ][ "horizontalCenterOffset" ]
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: ringContains.ringProfile[ index ][ "verticalCenterOffset" ]
                    source: ringContains.ringProfile[ index ][ "source" ]
                    opacity: ( Math.random() > 0.2 ) ? ( 0.42 ) : ( 0 )

                    Behavior on opacity { NumberAnimation { duration: 300 } }
                }
            }
        }

        Image {
            id: ring0Image
            anchors.centerIn: parent
            source: "qrc:/images/Ring0.webp"
        }
    }

    Image {
        id: backgroundImage
        width: imageSize
        height: imageSize
        source: "qrc:/images/Background.webp"
        visible: false
    }

    Blend {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: imageSize
        height: imageSize
        source: backgroundImage
        foregroundSource: ringContains
        mode: "colorDodge"
    }
}
