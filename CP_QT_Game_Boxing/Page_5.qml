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
    }

    // == поле вывода игрового процесса ==
    Rectangle {
        id: rectOutWin
        width: 300
        height: 380
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
           // property int intToStr2: sideCPPBackend.userHPSrv
            id: textOutHPPl1
            anchors.centerIn: parent
            color: "green"
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
        text: ":НР " + sideCPPBackend.userNameSrv //":НР игрока №1"
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
            //property int intToStr: sideCPPBackend.userHPCl
            id: textOutHPPl2
            anchors.centerIn: parent
            color: "green"
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
        text: ":НР " + sideCPPBackend.userNameCl//":НР игрока №2"
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
    //        width: 150
    //        height: 30
            anchors {
                top: textButtPunch.bottom
                left: rectOutWin.right
                topMargin: 5
                leftMargin: 10
            }
            textButton: "Голова"
            onClicked: {
//                if (sideCPPBackend.ipAddress === "0")
//                    sideCPPBackend.buttSrvPunchHead()
//                else
//                    sideCPPBackend.buttClPunchHead()

                sideCPPBackend.sendText2()
            }
        }

        CustomButtonSmall {
            id: buttonPunchBody
    //        width: 150
    //        height: 30
            anchors {
                left: buttonPunchHead.right
                leftMargin: 10
            }
            anchors.verticalCenter: buttonPunchHead.verticalCenter
            textButton: "Корпус"
            onClicked:{
                if (sideCPPBackend.ipAddress === "0")
                    sideCPPBackend.buttSrvPunchBody()
                else
                    sideCPPBackend.buttClPunchBody()
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
    //        width: 150
    //        height: 30
            anchors {
                top: textButtBlock.bottom
                left: rectOutWin.right
                topMargin: 5
                leftMargin: 10
            }
            textButton: "Голова"
            onClicked:{
                if (sideCPPBackend.ipAddress === "0")
                    sideCPPBackend.buttSrvBlockHead()
                else
                    sideCPPBackend.buttClBlockHead()
            }
        }

        CustomButtonSmall {
            id: buttonBlockBody
    //        width: 150
    //        height: 30
            anchors {
                left: buttonBlockHead.right
                leftMargin: 10
            }
            anchors.verticalCenter: buttonBlockHead.verticalCenter
            textButton: "Корпус"
            onClicked: {
//                if (sideCPPBackend.ipAddress === "0")
//                    sideCPPBackend.buttSrvBlockBody()
//                else
//                    sideCPPBackend.buttClBlockBody()
                sideCPPBackend.buttCreateGame()
            }
        }


//    CustomButtonSmall {
//        id: buttonSmall
////        width: 150
////        height: 30
//        anchors {
//            bottom: parent.bottom
//            bottomMargin: 10
//        }
//        anchors.horizontalCenter: parent.horizontalCenter
//        textButton: "TEST"
//        onClicked: {}
//    }
//    CustomButton {
//        id: startButton
//        enabled: true
//        width: 180
//        height: 50
//        anchors {
//            bottom: stopButton.top
//            right: parent.right

//            bottomMargin: 20
//            rightMargin: 20
//        }

//        textButton: "START SERVER"
//        onClicked: {
//            sideCPPBackend.buttCreateGame()
//            startButton.enabled = false
//            stopButton.enabled = true
//        }
//    }

//    CustomButton {
//        id: stopButton
//        enabled: false
//        width: 180
//        height: 50
//        anchors {
//            bottom: parent.bottom
//            right: parent.right

//            bottomMargin: 200
//            rightMargin: 20
//        }

//        textButton: "STOP SERVER"
//        onClicked:{
//            sideCPPBackend.buttDestroyGame()
//            stopButton.enabled = false
//            startButton.enabled = true
//        }
//    }


    CustomButton {
        id: startClButton
        enabled: true
        width: 100
        height: 50
        anchors {
            bottom: stopClButton.top
            right: parent.right
            bottomMargin: 20
            rightMargin: 20
        }

        textButton: "START CLIENT"
        onClicked: {
            sideCPPBackend.buttJoinGame()
            startClButton.enabled = false
            stopClButton.enabled = true
        }
    }

    CustomButton {
        id: stopClButton
        enabled: false
        width: 100
        height: 50
        anchors {
            bottom: parent.bottom
            right: parent.right
            bottomMargin: 20
            rightMargin: 20
        }

        textButton: "STOP CLIENT"
        onClicked:{
            sideCPPBackend.buttDisconGame()
            stopClButton.enabled = false
            startClButton.enabled = true
        }
    }

    CustomButton {
        id: testButton1
        enabled: true
        width: 100
        height: 30
        anchors {
            bottom: parent.bottom
            right: parent.right
            bottomMargin: 5
            rightMargin: 150
        }

        textButton: "SEND"
        onClicked:{
            sideCPPBackend.printTester()
        }
    }
}

