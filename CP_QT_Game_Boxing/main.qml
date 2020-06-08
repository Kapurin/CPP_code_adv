import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: generalWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Game Boxing")


    StackLayout {
        id: generalStack

        currentIndex: 0

        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
            right: parent.right

            bottomMargin: 60
        }
        // нумерация страниц с нуля!
        // окно №0 - окно приветствия
        Page_1 {
            id: win_1
        }
        // окно №1 - окно меню выбора
        Page_2 {
            id: win_2
        }
        // окно №2 - окно ожидания подключения клиента (если роль "СЕРВЕР")
        Page_3 {
            id: win_3
        }
        // окно №3 - окно ввода IP адреса сервера (если роль "КЛИЕНТ")
        Page_4 {
            id: win_4
        }
        // окно №4 - окно процесса игры
        Page_5 {
            id: win_5
        }
    }

    Rectangle {
        id: buttons_rect

        height: 40

        anchors {
            left: parent.left
            bottom: parent.bottom
            right: parent.right

            bottomMargin: 10
        }

        CustomButton {
            id: generalButton_1

            enabled: true //generalStack.currentIndex === 1

            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter

                leftMargin: 100
            }

            textButton: "Back"

            onClicked:{
                if (generalStack.currentIndex > 0)
                {
                    generalStack.currentIndex--
              }
            }
        }

        CustomButton {
            id: generalButton_2

            enabled: true//generalStack.currentIndex === 0

            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter

                rightMargin: 100
            }

            textButton: "Next"

            onClicked:{
                if (generalStack.currentIndex < (generalStack.count - 1))
                {
                generalStack.currentIndex++

              }
            }
         }
    }
}
