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
        text: "Enter Game Code"
    }

    Rectangle {
        id: joinLobbyTextBackground
        color: "#A4A9AD"
        radius: 5
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: titleText.bottom
            topMargin: 100
        }
        width: 618
        height: 79
    }

    TextInput {
        id: joinLobbyTextInput
        anchors.fill: joinLobbyTextBackground
        color: "white"
        font.pixelSize: 48
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        maximumLength: 4
        inputMask: "9999"
    }

    GameButton {
        id: joinButton
        width: 336
        height: 105
        buttonText: "Join Game"
        buttonTextPixelSize: 48
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: joinLobbyTextBackground.bottom
            topMargin: 100

        }
        onButtonClicked: {
            if(joinLobbyTextInput !== "") {
                gameManager.joinLobbyRequest(joinLobbyTextInput.text);
            }
        }
    }

    GameButton {
        id: backButton
        width: 336
        height: 105
        buttonText: "Back"
        buttonTextPixelSize: 48
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: joinButton.bottom
            topMargin: 20
        }
        onButtonClicked: mainLoader.source = "qrc:/ui/MainMenuScreen.qml"
    }
}
