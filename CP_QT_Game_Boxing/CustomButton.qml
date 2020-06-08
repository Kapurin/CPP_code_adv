import QtQuick 2.0
import QtQuick.Controls 2.12

Button {

    property string textButton: "default"
    property string colorTextButton: "#000000"

    width: 200
    height: 40

    background: Rectangle {
        id: background_button_3
        radius: 15

        color: enabled ? (pressed ? "red" : "transparent") : "#696969"

//        color: {
//            if (enabled) {
//                if (pressed) {
//                    "red"
//                }
//                else {
//                    "transparent"
//                }
//            }else {
//                "#696969"
//            }

//        }

        border {
            color: "#000000"
            width: 2

        }
    }

    contentItem: Text {
        text: textButton
        color: colorTextButton

        //font.family:
        font.pixelSize: width < 80 ? 10 : 16

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.bold: true
    }

    bottomPadding: 0
}
