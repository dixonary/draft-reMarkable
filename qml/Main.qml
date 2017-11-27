import QtQuick 2.0
import "../js/Main.js" as MainJS

Rectangle {
    id: canvas
    width: screenGeometry.width
    height: screenGeometry.height

    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            console.log("big: click detected");
        }
    }
    Rectangle {
        id: infoRect
        function toggleInfo() {
            infoRect.visible = !infoRect.visible;
            console.log("info set to " + infoRect.visible);
            // bad way to refresh the item
            clock.visible = false
            clock.visible = true
            view.requestUpdate();
        }
        width: 800
        height: 500
        anchors.centerIn: parent
        border.width: 10

        Text {
        anchors {
            fill: parent
            margins: 5
        }
        id: info
        text: (
            "pos: (" 
            + ma.mouseX.toFixed(2) + "," + ma.mouseY.toFixed(2) + ")"
            + "\n small Area is pressed: " + maSmall.pressed
            + "\n containsPress: " + ma.containsPress
        )
    }
    }
    Rectangle {
        id: clock
        width: 200
        height: 50
        y: screenGeometry.height- clock.height
        x: screenGeometry.width - clock.width
        color: !infoRect.visible ? "white" : "black"
        border.width: 2
        border.color: infoRect.visible ? "white" : "black"
        

        MouseArea {
            id: maSmall
            anchors.fill: parent
            hoverEnabled: true
            onClicked: console.log("small: click detected")
            onPressAndHold: {
                infoRect.toggleInfo();
                console.log("small: HOLD");
            }
        }

        Text {
            color: infoRect.visible ? "white" : "black"
            id: time
            anchors {
                left: parent.left
                leftMargin: 8
            }
            text: ""
        }

        Timer {
            interval: 500
            running: true
            repeat: true
            onTriggered: {
                time.text = MainJS.displayDateAsHHMMSS();
            }
        }
    }
}
