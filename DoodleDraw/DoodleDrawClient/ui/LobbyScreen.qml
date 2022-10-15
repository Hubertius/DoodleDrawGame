import QtQuick 2.15

Item {

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#23001E"
    }

    Text {
        id: titleText
        font.pixelSize: 72
        font.bold: true
        anchors {
            top: parent.top
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        color: "white"
        text: "Lobby code: " + gameManager.roomLobbyCode
    }

    Rectangle {
        id: roomLobbyListBackground
        radius: 5
        color: "#A4A9AD"
        anchors {
            top: titleText.bottom
            left: parent.left
            topMargin: 20
            leftMargin: 20

        }

    }
}
