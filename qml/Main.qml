import QtQuick 2.4
import QtQuick.Window 2.2

Rectangle {
    id: page
    width: 500
    height: 200
    x: screenGeometry.width - page.width
    y: screenGeometry.height - page.height
    z: 10
    color: "lightgray"

    Text {
        id: helloText
        text: "Hello world!"
        y: 30
        anchors.horizontalCenter: page.horizontalCenter
        font.pointSize: 24; font.bold: true
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: console.log("QML Mouse event");
    }

    MultiPointTouchArea {
        anchors.fill: parent
        onTouchUpdated: console.log("QML Touch event");
    }
}
