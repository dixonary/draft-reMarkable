import QtQuick 2.11
import QtQuick.Controls 2.0
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3

Window {

    id: canvas
    width: screenGeometry.width
    height: screenGeometry.height
    visible: true
    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("window")
            //popup.open()
        }

    }


    Rectangle{
        id:r
        anchors.fill: parent

    Timer{
        id: timer
        interval: 300
        repeat: false

        onTriggered:
        {
            canvas.show()
            r.update()
            console.log("update trigger")
        }
    }
    Timer {
        id:timer2
        repeat: false
        interval: 100
        onTriggered: {
            popup.close()
        }


    }

    ListView {

        id:optionsArea
        objectName: "optionsArea"
        spacing: 10
        anchors.fill: parent

        interactive: false

        model: options

        delegate: Rectangle{
            height:200
            border.color: "black"
            border.width: 1
            width: parent.width - 100

            anchors.horizontalCenter: parent.horizontalCenter

            Text{
                anchors.margins: 10
                anchors.left: parent.left
                text:model.modelData.name
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("tap")
                    canvas.visible = false
                    //canvas.opacity = 0
                    model.modelData.execute()
                    timer.start()
                }

            }
        }




    }

    Popup {
        id:popup
        width: parent.width
        height: parent.height

        Text {
            anchors.centerIn: parent
            text: "redraw"
        }

        MouseArea {
            anchors.fill:parent
            onClicked: {
                popup.close()
            }

        }

    }

}}
