import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


// === окно №3 - окно ввода IP адреса сервера (если роль "КЛИЕНТ") ===
Page {
    title: "Page 4"

    background: Rectangle {
        color: "#E6E6E6"
    }

    // == поле ввода IP адреса сервера ==
    Rectangle {
        id: rectInpIPadd
        width: 150
        height: 30
        border.color: "black"
        border.width: 3
        anchors {
            bottom: buttonEnterInpIPadd.top
            bottomMargin: 25
        }
        anchors.horizontalCenter: parent.horizontalCenter
        TextInput {
            id: textInpIPadd
            anchors.centerIn: parent
            color: "black"
            text: "Enter IP server..."
            font.pixelSize: 14
            focus: true
        }
    }


    // == кнопка ввода IP адреса сервера ==
    CustomButton {
        id: buttonEnterInpIPadd
        width: 150
        height: 30
        anchors {
            bottom: parent.bottom
            bottomMargin: 150
        }
        anchors.horizontalCenter: parent.horizontalCenter
        textButton: "ENTER"
        onClicked: {
            if (textInpIPadd.text != "Enter IP server...")
            {
                sideCPPBackend.ipAddress = textInpIPadd.text
                sideCPPBackend.buttJoinGame()
                generalStack.currentIndex = 4
            }
            else
                textInpIPadd.text = "Вы не ввели IP!"
        }
    }
}
