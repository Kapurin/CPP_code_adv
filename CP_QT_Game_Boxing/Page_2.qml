import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


// === окно №1 - окно меню выбора ===
Page {
    title: "Page 2"

    background: Rectangle {
        color: "#E6E6E6"
    }

    // фоновое изображение
    Image {
        id: imageBack
        source: "qrc:/images/boxing.jpg"
        opacity: 0.4
    }

    Rectangle {
        id: rectButtGame
        width: buttonCreateGame.width + buttonJoinGame.width + buttonJoinGame.anchors.leftMargin
        anchors.centerIn: parent

        // == кнопка создания игры (СЕРВЕР) ==
        CustomButton {
            id: buttonCreateGame
            width: 150
            height: 30
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            textButton: "Create game"
            onClicked: {
                sideCPPBackend.buttGWCreateGame()
                generalStack.currentIndex = 2
            }
        }


        // == кнопка подключения к игре (КЛИЕНТ) ==
        CustomButton {
            id: buttonJoinGame
            width: 150
            height: 30
            anchors {
                left: buttonCreateGame.right
                leftMargin: 20
            }
            anchors.verticalCenter: parent.verticalCenter
            textButton: "Join game"
            onClicked: {
                sideCPPBackend.userNameCl = sideCPPBackend.userNameSrv
                sideCPPBackend.userNameSrv = "0"
                generalStack.currentIndex = 3
            }
        }
    }
}
