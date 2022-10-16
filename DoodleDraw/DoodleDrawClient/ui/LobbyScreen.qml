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
            leftMargin: 40
        }
        width: 358
        height: 415
    }

    Rectangle {
        id: messageWindowBackground
        radius: 5
        color: "#A4A9AD"
        anchors {
            top: roomLobbyListBackground.top
            bottom: roomLobbyListBackground.bottom
            left: roomLobbyListBackground.right
            leftMargin: 20
            right: parent.right
            rightMargin: 40
        }
    }

    GameButton {
        id: readyButton
        buttonText: "Ready"
        buttonTextPixelSize: 36
        width: 314
        height: 80
        anchors {
            top: roomLobbyListBackground.bottom
            topMargin: 20
            horizontalCenter: roomLobbyListBackground.horizontalCenter
        }
    }

    GameButton {
        id: sendButton
        buttonText: "Send"
        buttonTextPixelSize: 36
        width: 174
        anchors {
            top: messageWindowBackground.bottom
            right: messageWindowBackground.right
            bottom: readyButton.bottom
            topMargin: 20
        }
    }

    Rectangle {
        id: sendTextFileBackground
        radius: 5
        color: "#A4A9AD"

        anchors {
            top: messageWindowBackground.bottom
            topMargin: 20
            right: sendButton.left
            rightMargin: 10
            left: messageWindowBackground.left
            bottom: readyButton.bottom
        }
    }

    TextEdit {
        id: sendTextEdit
        anchors.fill: sendTextFileBackground
        font.pixelSize: 36
        color: "white"
        clip: true
    }
}
