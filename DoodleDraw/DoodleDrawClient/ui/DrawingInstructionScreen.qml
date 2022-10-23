import QtQuick 2.15

Item {

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#23001E"
    }

    Component.onCompleted: {
        drawCanvas.loadImage(gameManager.doodleFilePath());
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
        text: "Draw: " + gameManager.drawingInstruction

    }

    GameButton {
        id: clearButton
        width: 174
        height: 80
        buttonColor: "#EF5B5B"
        buttonColorPressed: "#B34444"
        buttonText: "Clear"
        buttonTextPixelSize: 36

        anchors {
            left: parent.left
            bottom: parent.bottom
            leftMargin: 80
            bottomMargin: 40
        }

        onButtonClicked: drawCanvas.clearPainting()
    }


    GameButton {
        id: finishButton
        width: 174
        height: 80
        buttonColor: "#20A39E"
        buttonColorPressed: "#126663"
        buttonText: "Send"
        buttonTextPixelSize: 36

        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 80
            bottomMargin: 40
        }
        onButtonClicked: {
            drawCanvas.save("tmp.png");
            mainLoader.source = "qrc:/ui/WaitingForPlayersScreen.qml";
        }
    }

    Rectangle {
        id: canvasBackground
        color: "#C4C4C4"
        anchors {
            top: titleText.bottom
            bottom: clearButton.top
            topMargin: 20
            bottomMargin: 20
            left: parent.left
            right: parent.right
            leftMargin: 80
            rightMargin: 80
        }
    }

    Canvas {
        id: drawCanvas
        anchors.fill: canvasBackground
        property int startX: -1
        property int startY: -1
        property int finishX: -1
        property int finishY: -1

        function clearPainting() {
            var ctx = drawCanvas.getContext("2d");
            ctx.reset();
            drawCanvas.requestPaint();
        }

        onImageLoaded: {
            console.log("Loadng image on which client will continue drawing");
            var ctx = drawCanvas.getContext("2d");
            console.log(gameManager.doodleFilePath());
            ctx.drawImage(gameManager.doodleFilePath(), 0,0);
            drawCanvas.requestPaint();
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                drawCanvas.startX = mouseX
                drawCanvas.startY = mouseY
            }
            onPositionChanged: {
                drawCanvas.finishX = mouseX
                drawCanvas.finishY = mouseY
                drawCanvas.requestPaint()
            }
        }

        onPaint: {
            var ctx = drawCanvas.getContext("2d");
            ctx.beginPath();
            ctx.strokeStyle = "red"
            ctx.lineJoin = "round";
            ctx.lineWidth = 5;
            ctx.moveTo(startX, startY);
            ctx.lineTo(finishX, finishY);
            ctx.closePath();
            ctx.stroke();
            startX = finishX;
            startY = finishY;
        }

    }
}
