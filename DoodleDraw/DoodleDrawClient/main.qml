import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("DoodleDrawClient")

    Connections {
        target: gameManager
        onChangeOfGameLobby: mainLoader.source = "qrc:/ui/LobbyScreen.qml"
        onNewGameBegins: mainLoader.source = "qrc:/ui/DoodleScreen.qml"
        onClientDrawingForAddedImageStarted: mainLoader.source = "qrc:/ui/DrawingInstructionScreen.qml"
    }

    Loader {
        id: mainLoader
        anchors.fill: parent
        source: "qrc:/ui/MainMenuScreen.qml"
    }
}
