import QtQuick 2.15

Rectangle {
    id: gameButton
    property string buttonColor: "#FFBA49"
    property string buttonColorPressed: "#BF8C39"
    property string buttonText: ""
    property int buttonTextPixelSize: 72

    signal buttonClicked()

    radius: 5
    color: buttonColor
    Text {
        anchors.centerIn: parent
        color: "white"
        text: buttonText
        font.pixelSize: buttonTextPixelSize
    }

    MouseArea {
        anchors.fill: parent
        onPressed: gameButton.color = gameButton.buttonColorPressed
        onReleased: gameButton.color = gameButton.buttonColor
        onClicked: gameButton.buttonClicked()
    }
}
