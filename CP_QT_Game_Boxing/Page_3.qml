import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


// === окно №2 - окно ожидания подключения клиента (если роль "СЕРВЕР") ===
Page {
    title: "Page 3"

    background: Rectangle {
        color: "#E6E6E6"
    }

    // фоновое изображение
    Image {
        id: imageBack
        source: "qrc:/images/boxing.jpg"
        opacity: 0.4
    }

    // == статус подключения клиента ==
    Text {
        id: textStatusClient
        anchors.fill: parent
        text: "Ожидание подключения клиента-игрока..."
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "black"
        font.pixelSize: 20
        font.bold: true
    }

    Connections {
        target: sideCPPBackend
        onUpdUserNameCl: {
            if (sideCPPBackend.userNameCl === "Player Client")
                textStatusClient.text = "Ожидание подключения клиента-игрока..."
            else
            {
                textStatusClient.text = "Клиент-игрок подключился!"
                generalStack.currentIndex = 4
            }
        }
    }
}
