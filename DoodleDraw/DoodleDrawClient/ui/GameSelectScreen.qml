import QtQuick 2.15

Item {
    id: gameSelectScreen

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
        text: "Doodle Drawer"
    }

    GameButton {
        id: createGameButton
        anchors {
            top: titleText.bottom
            topMargin: 160
            horizontalCenter: parent.horizontalCenter
        }
        buttonText: "Create Game"
        buttonTextPixelSize: 48
        width: 336
        height: 106
    }

    GameButton {
        id: joinGameButton
        anchors {
            top: createGameButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        buttonText: "Join Game"
        buttonTextPixelSize: 48
        width: 336
        height: 106
    }

    GameButton {
        id: backGameButton
        anchors {
            top: joinGameButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        buttonText: "Back"
        buttonTextPixelSize: 48
        width: 336
        height: 106
        onButtonClicked: mainLoader.source = "qrc:/ui/MainMenuScreen.qml"

    }

}
