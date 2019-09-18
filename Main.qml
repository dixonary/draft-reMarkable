import QtQuick 2.11
import QtQuick.Controls 2.0
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3

Window {
    id: canvas
    width: screenGeometry.width
    height: screenGeometry.height
    visible: true

    Rectangle {
        id:body
        anchors.fill: parent

        Timer{
            id: redraw_timer
            interval: 300
            repeat: false

            onTriggered:
            {
                canvas.visible = true
                body.update()
            }
        }
        Item {
            id:header
            height: 80
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            Text{
                text: "draft launcher"
                anchors.centerIn: parent

                font.family:"Noto Serif"
                font.pixelSize:30
                font.bold: true
            }
            Rectangle{
                anchors.left:parent.left
                anchors.right:parent.right
                anchors.bottom:parent.bottom
                anchors.margins: 10
                height: 5
                color: "black"
            }
        }
        Item {
            id:footer
            height:40

            anchors{
                bottom: parent.bottom
                left:parent.left
                right:parent.right
            }

            Rectangle{
                anchors.left:parent.left
                anchors.right:parent.right
                anchors.top:parent.top
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                height: 5
                color: "black"
            }

            Text{
                text: controller.getVersion()
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins:10

                font.family:"Noto Serif"
                font.pixelSize:15
                font.bold: true
            }
        }


        Item {

            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 15

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
