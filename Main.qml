import QtQuick 2.11
import QtQuick.Controls 2.0
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3

Window {

    id: canvas
    width: screenGeometry.width
    height: screenGeometry.height
    visible: true

    Rectangle{
        id:r
        anchors.fill: parent

        Timer{
            id: redraw_timer
            interval: 300
            repeat: false

            onTriggered:
            {
                canvas.visible = true
                r.update()
                console.log("update trigger")
            }
        }
        Rectangle {
            id:header
            height: 80
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            Text{
                text: "reDrift"
                anchors.centerIn: parent

                font.family:"Noto Serif"
                font.pixelSize:30
                font.bold: true
            }
        }
        Item {

            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            ListView {
                id:optionsArea
                spacing: 15
                anchors.fill:parent
                interactive: false
                model: options

                delegate: Rectangle{
                    height:150
                    border.color: "black"
                    border.width: 2

                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 10

                    Text{
                        font.pixelSize: 70
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.margins: 10
                        text:model.modelData.name
                    }

                    Text {
                        id:tdesc
                        anchors.bottom:parent.bottom
                        anchors.left:parent.left
                        anchors.right:parent.right
                        anchors.leftMargin:20
                        anchors.bottomMargin:10
                        text:model.modelData.desc
                        font.family:"Noto Serif"
                        font.pixelSize:30
                        font.italic: true
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //disable events
                            canvas.visible = false
                            //blocking call
                            model.modelData.execute()
                            redraw_timer.start()
                        }
                    }
                }
            }
        }
    }
}
