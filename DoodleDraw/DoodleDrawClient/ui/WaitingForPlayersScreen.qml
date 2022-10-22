import QtQuick 2.15

Item {

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#23001E"
    }

    Component.onCompleted: {
        gameManager.doodleDone();
    }

    Text {
        id: titleText
        font.pixelSize: 72
        font.bold: true
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
        color: "white"
        text: "Waiting for other players<br> to finish :)"
        horizontalAlignment: Text.AlignHCenter
    }
}
