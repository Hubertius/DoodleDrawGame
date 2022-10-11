import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        anchors.centerIn: parent
        text: "Click me!"
        onClicked: clientSocketHandler.connectToServer("www.google.com")
    }
}
