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
        text: gameManager.winnerClientID + " was the best!";
    }
    
    Rectangle {
        id: votedImageBackground
        anchors {
            top: titleText.bottom
            bottom: doneButton.top
            left: parent.left
            right: parent.right
            margins: 20
        }
        color: "#C4C4C4"
    }

    Image {
        id: votedImage
        anchors.fill: votedImageBackground
        source: gameManager.getWinnerImager();
        fillMode: Image.PreserveAspectFit
    }

    GameButton {
        id: doneButton
        width: 174
        height: 80
        buttonColor: "#20A39E"
        buttonColorPressed: "#126663"
        buttonText: "Done"
        buttonTextPixelSize: 36

        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 80
            bottomMargin: 40
        }

        onButtonClicked: {
            Qt.quit();
        }
    }
}
