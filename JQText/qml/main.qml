import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    id: window
    width: 640
    height: 480
    visible: true
    color: "#ededed"

    TextArea {
        id: textArea
        anchors.fill: parent
        anchors.margins: 10
        wrapMode: TextInput.WordWrap
        text:
"Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Aenean euismod bibendum laoreet.
Proin gravida dolor sit amet lacus accumsan et viverra justo commodo.
Proin sodales pulvinar sic tempor.
Sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.
Nam fermentum, nulla luctus pharetra vulputate, felis tellus mollis orci, sed rhoncus pronin sapien nunc accuan eget.
\n
我见过你们人类难以置信的事，我见过太空飞船在猎户星座的边缘被击中，燃起熊熊火光。我见过Ｃ射线，划过’唐怀瑟之门’那幽暗的宇宙空间。然而所有的这些时刻，都将湮没于时间的洪流，就像…泪水消失在雨中。
\n
Qt: " + Helper.versionInfo()

        background: Item { }
    }

    Row {
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        spacing: 10

        Button {
            width: 50
            height: 50
            text: "保存"

            onClicked: {
                Helper.setWebCookie( "Text", textArea.text );
            }
        }

        Button {
            width: 50
            height: 50
            text: "读取"

            onClicked: {
                textArea.text = Helper.getWebCookie( "Text" );
            }
        }

        Button {
            width: 50
            height: 50
            visible: Qt.platform.os === "wasm"
            text: "输入"

            onClicked: {
                textArea.text = Helper.getWebPrompt( "请输入文本", textArea.text );
            }
        }
    }
}
