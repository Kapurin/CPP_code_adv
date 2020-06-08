import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


// === окно №0 - окно приветствия ===
Page {
    title: "Page 1"

    background: Rectangle {
        color: "#E6E6E6"
    }



    // == строчка приветствия ==
    Text {
        id: textTitle
        anchors {
            top: parent.top
            topMargin: 20
        }
        anchors.horizontalCenter: parent.horizontalCenter
        text: "WELCOME to 'Boxing Game' !!!"
        color: "blue"
        font.bold: true
        font.pixelSize: 20
    }


    // == поле ввода имени пользователя ==
    Rectangle {
        id: rectInpUserName
        width: 150
        height: 30
        border.color: "black"
        border.width: 3
        anchors {
            bottom: buttonEnterUserName.top
            bottomMargin: 25
        }
        anchors.horizontalCenter: parent.horizontalCenter
        TextInput {
            id: textInpUserName
            anchors.centerIn: parent
            color: "black"
            text: "Enter your name..."
            font.pixelSize: 14
            focus: true
        }
    }


    // == кнопка ввода имени пользователя ==
    CustomButton {
        id: buttonEnterUserName
        width: 150
        height: 30
        anchors {
            bottom: parent.bottom
            bottomMargin: 150
        }
        anchors.horizontalCenter: parent.horizontalCenter
        textButton: "ENTER"
        onClicked: {
            if ((textInpUserName.text != "Enter your name...") && (textInpUserName.text != "Вы не ввели свое имя!"))
            {
                sideCPPBackend.userNameSrv = textInpUserName.text
                generalStack.currentIndex = 1
            }
            else
                textInpUserName.text = "Вы не ввели свое имя!"
        }
    }
}
