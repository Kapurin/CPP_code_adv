import QtQuick 2.0
import QtQuick.Controls 2.12

Button {

    property string textButton: "default"
    property string colorTextButton: "#000000"

    width: 80
    height: 30

    background: Rectangle {
        id: background_button_3
        radius: 5

        color: enabled ? (pressed ? "green" : "transparent") : "#696969"
        border {
            color: "#000000"
            width: 2

        }
    }

    contentItem: Text {
        text: textButton
        color: colorTextButton

        //font.family:
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
    }

   // bottomPadding: 0
}

