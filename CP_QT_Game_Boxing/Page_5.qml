import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


// === окно №4 - окно процесса игры ===
Page {
    title: "Page 5"

    background: Rectangle {
        color: "#E6E6E6"
    }

    // фоновое изображение
    Image {
        id: imageBack
        source: "qrc:/images/boxing.jpg"
        opacity: 0.4
    }


    // == текст над полем вывода игрового процесса ==
    Text {
        id: textOutWin
        anchors {
            top: parent.top
            topMargin: 5
        }
        anchors.horizontalCenter: rectOutWin.horizontalCenter
        text: "Текущий игровой процесс:"
        color: "black"
        font.pixelSize: 15
        font.bold: true
    }

    // == поле вывода игрового процесса ==
    Rectangle {
        id: rectOutWin
        width: 300
        height: 440//380
        border.color: "black"
        anchors {
            top: parent.top
            left: parent.left
            topMargin: 30
            leftMargin: 10
        }
        ScrollView {
            id: scrollViewOutWin
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            anchors.fill:parent

            TextArea {
                id: textAreaOutWin
                anchors.fill:parent
                text: append(sideCPPBackend.txTextToQML)
            }
        }
    }

    // == поле вывода НР игрока №1 ==
    Rectangle {
        id: rectOutHPPl1
        width: 35
        height: 20
        border.color: "black"
        border.width: 1.5
        anchors {
            top: parent.top
            left: rectOutWin.right
            topMargin: 5
            leftMargin: 10
        }
        Text {
            property int userHPSrvINT: sideCPPBackend.userHPSrv
            id: textOutHPPl1
            anchors.centerIn: parent
            color:{
                if (userHPSrvINT > 20)
                    "green"
                else
                    "red"
            }
            text: sideCPPBackend.userHPSrv
            font.pixelSize: 14
            font.bold: true
        }
    }

    // == текст возле поля вывода НР игрока №1 ==
    Text {
        id: textHPPl1
        anchors {
            left: rectOutHPPl1.right
            leftMargin: 3
        }
        anchors.verticalCenter: rectOutHPPl1.verticalCenter
        text: ":НР " + sideCPPBackend.userNameSrv
        color: "black"
        font.pixelSize: 14
    }



    // == поле вывода НР игрока №2 ==
    Rectangle {
        id: rectOutHPPl2
        width: 35
        height: 20
        border.color: "black"
        border.width: 1.5
        anchors {
            top: rectOutHPPl1.bottom
            left: rectOutWin.right
            topMargin: 10
            leftMargin: 10
        }
        Text {
            property int userHPClINT: sideCPPBackend.userHPCl
            id: textOutHPPl2
            anchors.centerIn: parent
            color:{
                if (userHPClINT > 20)
                    "green"
                else
                    "red"
            }
            text: sideCPPBackend.userHPCl
            font.pixelSize: 14
            font.bold: true
        }
    }

    // == текст возле поля вывода НР игрока №2 ==
    Text {
        id: textHPPl2
        anchors {
            left: rectOutHPPl2.right
            leftMargin: 3
        }
        anchors.verticalCenter: rectOutHPPl2.verticalCenter
        text: ":НР " + sideCPPBackend.userNameCl
        color: "black"
        font.pixelSize: 14
    }


    // == текст возле текущего статуса игры ==
    Text {
        id: text1StatusGame
        anchors {
            top: rectOutHPPl2.bottom
            left: rectOutWin.right
            topMargin: 30
            leftMargin: 10
        }
        text: "Статус:"
        color: "black"
        font.pixelSize: 16
        font.bold: true
    }

    // == поле вывода текущего статуса игры ==
    Text {
        id: text2StatusGame
        anchors {
            left: text1StatusGame.right
            leftMargin: 10
        }
        anchors.verticalCenter: text1StatusGame.verticalCenter
        text: sideCPPBackend.statusGame
        color: "black"
        font.pixelSize: 16
    }


    // == КНОПКИ ==


    // == текст возле кнопок выбора ударов ==
    Text {
        id: textButtPunch
        anchors {
            top: text1StatusGame.bottom
            left: rectOutWin.right
            topMargin: 40
            leftMargin: 10
        }
        text: "Кнопки выбора ударов:"
        color: "black"
        font.pixelSize: 14
        font.bold: true
    }

    // == кнопки выбора ударов ==
    CustomButtonSmall {
        id: buttonPunchHead
        anchors {
            top: textButtPunch.bottom
            left: rectOutWin.right
            topMargin: 5
            leftMargin: 10
        }
        textButton: "Голова"
        onClicked: {
            if (sideCPPBackend.ipAddress === "0")
                sideCPPBackend.buttGWSrvPunchHead()
            else
                sideCPPBackend.buttGWClPunchHead()
            buttonPunchHead.enabled = false
            buttonPunchBody.enabled = false
        }
    }

    CustomButtonSmall {
        id: buttonPunchBody
        anchors {
            left: buttonPunchHead.right
            leftMargin: 10
        }
        anchors.verticalCenter: buttonPunchHead.verticalCenter
        textButton: "Корпус"
        onClicked:{
            if (sideCPPBackend.ipAddress === "0")
                sideCPPBackend.buttGWSrvPunchBody()
            else
                sideCPPBackend.buttGWClPunchBody()
            buttonPunchHead.enabled = false
            buttonPunchBody.enabled = false
        }
    }


    // == текст возле кнопок выбора блоков защиты от ударов ==
    Text {
        id: textButtBlock
        anchors {
            top: buttonPunchHead.bottom
            left: rectOutWin.right
            topMargin: 40
            leftMargin: 10
        }
        text: "Кнопки выбора блоков защиты:"
        color: "black"
        font.pixelSize: 14
        font.bold: true
    }


    // == кнопки выбора блоков защиты от ударов ==
    CustomButtonSmall {
        id: buttonBlockHead
        anchors {
            top: textButtBlock.bottom
            left: rectOutWin.right
            topMargin: 5
            leftMargin: 10
        }
        textButton: "Голова"
        onClicked:{
            if (sideCPPBackend.ipAddress === "0")
                sideCPPBackend.buttGWSrvBlockHead()
            else
                sideCPPBackend.buttGWClBlockHead()
            buttonBlockHead.enabled = false
            buttonBlockBody.enabled = false
        }
    }

    CustomButtonSmall {
        id: buttonBlockBody
        anchors {
            left: buttonBlockHead.right
            leftMargin: 10
        }
        anchors.verticalCenter: buttonBlockHead.verticalCenter
        textButton: "Корпус"
        onClicked: {
            if (sideCPPBackend.ipAddress === "0")
                sideCPPBackend.buttGWSrvBlockBody()
            else
                sideCPPBackend.buttGWClBlockBody()
            buttonBlockHead.enabled = false
            buttonBlockBody.enabled = false
        }
    }



    // == кнопки управления игрой ==
    CustomButtonSmall {
        id: buttonRestartGame
        width: 150
        height: 30
        anchors {
            top: buttonBlockHead.bottom
            left: rectOutWin.right
            topMargin: 100
            leftMargin: 10
        }
        textButton: "Перезапустить игру"
        onClicked:{
            textAreaOutWin.clear()
            sideCPPBackend.initData()
        }
    }

    CustomButtonSmall {
        id: buttonExitGame
        width: 150
        height: 30
        anchors {
            top: buttonRestartGame.bottom
            left: rectOutWin.right
            topMargin: 10
            leftMargin: 10
        }
        textButton: "Завершить игру"
        onClicked: {
            if (sideCPPBackend.ipAddress === "0")
                sideCPPBackend.buttGWDestroyGame()
            else
                sideCPPBackend.buttGWDisconGame()
            Qt.quit()
        }
    }


    // активация/деактивация кнопок ударов и блоков
    // в зависимости от текущего статуса в игре (атака или защита)
    Connections {
        target: sideCPPBackend
        onUpdStatusGame: {
            if (sideCPPBackend.statusGame === "Вы атакуете!")
            {
                buttonPunchHead.enabled = true
                buttonPunchBody.enabled = true
                buttonBlockHead.enabled = false
                buttonBlockBody.enabled = false
            }
            else if (sideCPPBackend.statusGame === "Вы защищаетесь!")
            {
                buttonPunchHead.enabled = false
                buttonPunchBody.enabled = false
                buttonBlockHead.enabled = true
                buttonBlockBody.enabled = true
            }
            else if (sideCPPBackend.statusGame === "[пусто]" || sideCPPBackend.statusGame === "Вы победили :)"
                     || sideCPPBackend.statusGame === "Вы проиграли :(")
            {
                buttonPunchHead.enabled = false
                buttonPunchBody.enabled = false
                buttonBlockHead.enabled = false
                buttonBlockBody.enabled = false
            }

        }
    }
}
