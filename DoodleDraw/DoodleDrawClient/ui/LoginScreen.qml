import QtQuick 2.15

Item {
    id: loginScreen

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
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        color: "white"
        text: "Login"
    }

    Rectangle {
        id: usernameLoginInputBackground
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
        id: usernameLoginInput
        anchors.fill: usernameLoginInputBackground
        color: "white"
        font.pixelSize: 48
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        maximumLength: 25
    }


    Text {
        id: usernameLabel
        font.pixelSize: 36
        font.bold: true
        anchors {
            left: usernameLoginInputBackground.left
            bottom: usernameLoginInputBackground.top
            bottomMargin: 20
        }
        color: "white"
        text: "Username:"
    }

    Rectangle {
        id: passwordLoginInputBackground
        color: "#A4A9AD"
        radius: 5
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: usernameLoginInputBackground.bottom
            topMargin: 100
        }
        width: 618
        height: 79
    }

    TextInput {
        id: passwordLoginInput
        anchors.fill: passwordLoginInputBackground
        color: "white"
        font.pixelSize: 48
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        maximumLength: 25
        echoMode: TextInput.Password
    }

    Text {
        id: passwordLabel
        font.pixelSize: 36
        font.bold: true
        anchors {
            left: passwordLoginInputBackground.left
            bottom: passwordLoginInputBackground.top
            bottomMargin: 20
        }
        color: "white"
        text: "Password:"
    }

    GameButton {
        id: loginButton
        width: 336
        height: 105
        buttonText: "Login"
        buttonTextPixelSize: 48
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: passwordLoginInput.bottom
            topMargin: 50

        }
        onButtonClicked: {
            if(usernameLoginInput !== "" && passwordLoginInput !== "") {
                gameManager.loginRequest(usernameLoginInput.text, passwordLoginInput.text);
            }
        }
    }

    GameButton {
        id: quitButton
        anchors {
            top: loginButton.bottom
            topMargin: 25
            horizontalCenter: parent.horizontalCenter
        }
        buttonText: "Quit"
        buttonTextPixelSize: 48
        width: 336
        height: 105
        onButtonClicked: Qt.quit()
    }

}
