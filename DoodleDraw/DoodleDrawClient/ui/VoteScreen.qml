import QtQuick 2.15

Item {
    id: votingScreen
    property string votedImage: ""
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
        text: "Vote for best work!"
    }


    GridView {
        id: imagesGrid
        anchors {
            top: titleText.bottom
            bottom: voteButton.top
            left: parent.left
            right: parent.right
            margins: 40
        }

        model: gameManager.finishedDrawingsList
        cellWidth: 585
        cellHeight: 410
        clip: true
        delegate: Rectangle {
            color: "#C4C4C4"
            width: 575
            height: 402
            border.color: "#FFBA49"
            border.width: {
                if(votingScreen.votedImage === modelData)
                    return 5;
                else
                    return 0;
            }

            Image {
                source: modelData
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit

            }

            MouseArea {
                anchors.fill: parent
                onClicked: votingScreen.votedImage = modelData
            }
        }
    }

    GameButton {
        id: voteButton
        width: 174
        height: 80
        buttonColor: "#20A39E"
        buttonColorPressed: "#126663"
        buttonText: "Vote"
        buttonTextPixelSize: 36

        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 80
            bottomMargin: 40
        }

        onButtonClicked: {
            gameManager.voteOfUser(votingScreen.votedImage);
            mainLoader.source = "ui/WaitingForPlayersScreen.qml";
        }
    }
}
