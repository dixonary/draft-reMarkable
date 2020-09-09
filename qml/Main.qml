import QtQuick 2.0
import "../js/Main.js" as MainJS

Rectangle {
    property alias battery_level : batteryLevel.text
    property alias battery_icon : batteryIcon.source

    id: canvas
    width: 1404
    height: 1872

    Behavior on y {
        NumberAnimation {
            property:"y"
            to:0
            duration:1000
        }
    }

    Text {
        id: heading
        anchors.left:parent.left
        anchors.right:parent.right
        text: " <font size=8> draft</font> launcher"
        textFormat: Text.RichText
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 80
        font.family:"Noto Serif"
        font.italic:true
    }

    Text {
        id: credit
        anchors.right:parent.right
        anchors.bottom:parent.bottom
        anchors.margins: {bottom:10}
        text: qsTr("draft v0.2 created by @dixonary_")
        font.pixelSize: 30
        font.family:"Noto Serif"
        font.italic:true
    }

    Image {
        x: 19
        y: 1837
        id: batteryIcon
        fillMode: Image.PreserveAspectFit
        height: 10
        width: 50
        anchors.rightMargin: 1335
        anchors.bottomMargin: 5
        anchors.topMargin: 1841
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom:parent.bottom
        anchors.margins:15
        source: "../extra-files/draft/icons/batteryIcon.png"
    }

    Text {
        id: batteryLevel
        x: 75
        y: 1828
        width: 428
        height: 36
        text: "Unable to read battery level"
        anchors.rightMargin: 901
        anchors.bottomMargin: 8
        font.family: "Noto Serif"
        anchors.bottom: parent.bottom
        font.pixelSize: 30
        font.italic: true
        anchors.margins: {bottom:10}
        anchors.right: parent.right
    }


    Text {
        id: optionsHeading
        anchors.left:parent.left
        anchors.right:parent.right
        anchors.margins:50
        horizontalAlignment:Text.AlignLeft
        font.pixelSize: 40
        font.family:"Noto Serif"
        font.italic:true
        text: "Available Options"
        y: heading.y + heading.height + 50
    }
    Rectangle {
        id:optionsArea
        objectName: "optionsArea"
        y:optionsHeading.y + optionsHeading.height + 10
        anchors.left:parent.left
        anchors.right:parent.right
        height:credit.y - y - 5

        Rectangle {
            id:topBar
            color: "black"
            anchors.left:parent.left
            anchors.right:parent.right
            anchors.margins: 50
            anchors.topMargin: 0
            height:5
        }
        Rectangle {
            id:bottomBar
            color: "black"
            anchors.left:parent.left
            anchors.right:parent.right
            anchors.bottom:parent.bottom
            anchors.margins: 50
            anchors.bottomMargin:0
            height:5
        }

        MouseArea {
            anchors.fill:parent
        }

    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
