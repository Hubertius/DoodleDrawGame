import QtQuick 2.15

Item {
    id: mainMenuScreen

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
        id: playButton
        anchors.centerIn: parent
        buttonText: "Play"
        width: 336
        height: 106
        onButtonClicked:  mainLoader.source = "qrc:/ui/GameSelectScreen.qml"
    }

    GameButton {
        id: quitButton
        anchors {
            top: playButton.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        buttonText: "Quit"
        width: 336
        height: 106
        onButtonClicked: Qt.quit()
    }
}
