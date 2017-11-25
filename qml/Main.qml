import QtQuick 2.4
import QtQuick.Window 2.2

Rectangle {
    id: page
    width: 500; height: 200
    color: "lightgray"

    Text {
        id: helloText
        text: "Hello world!"
        y: 30
        anchors.horizontalCenter: page.horizontalCenter
        font.pointSize: 24; font.bold: true
    }
}
