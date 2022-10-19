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

    ListView {
        id: roomLobbyList
        model: gameManager.lobbyClientsIDs
        delegate: Text {
            id: userID
            anchors.horizontalCenter: parent.horizontalCenter
            text: modelData
            font.pixelSize: 36
            color: "white"
            font.bold: true

            Image {
                id: checkImage
                visible: gameManager.isClientReady(modelData);
                Connections {
                    target: gameManager
                    onUpdatedClientsListReadinees: checkImage.visible = gameManager.isClientReady(modelData);
                }

                anchors {
                    left: userID.right
                    leftMargin: 10
                    verticalCenter: userID.verticalCenter
                }

                source: "qrc:/ui/assets/check.png"
                width: 40
                height: 40
                fillMode: Image.PreserveAspectFit
            }
        }
        anchors.fill: roomLobbyListBackground
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

    TextEdit {
        id: messageWindow
        anchors.fill: messageWindowBackground
        font.pixelSize: 24
        readOnly: true
    }

    Connections {
        target: gameManager
        onNewMessageForLobby: function(messageForDisplaying) { messageWindow.append(messageForDisplaying); }
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
        onButtonClicked: gameManager.readyToPlay();
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
        onButtonClicked: {
            gameManager.sendMessageToLobby(sendTextInput.text);
            sendTextInput.text = "";
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

    TextInput {
        id: sendTextInput
        anchors.fill: sendTextFileBackground
        font.pixelSize: 36
        color: "white"
        clip: true
        onAccepted: {
            gameManager.sendMessageToLobby(sendTextInput.text)
            sendTextInput.text = "";
        }
    }

}
