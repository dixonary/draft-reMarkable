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
            clock.location.x = mouseX;
            clock.location.y = mouseY;
            console.log(mouseX);
        }
        onPressed: {
            clock.clickStatus = "pressed";
        }
        onReleased: {
            clock.clickStatus = "released";
        }
    }
    Rectangle {
        id: clock
        width: 500
        height: 500
        y: screenGeometry.height- clock.height
        x: screenGeometry.width - clock.width
        
        property string timeStr
        property point location
        property string clickStatus

        Text {
            id: time
            text: clock.timeStr + "\n" + clock.location + "\n" + clock.clickStatus
        }

        Timer {
            interval: 500
            running: true
            repeat: true
            onTriggered: {
                parent.timeStr = MainJS.displayDateAsHHMMSS();
            }
        }
    }
}
