import QtQuick              2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0
import epsonmodule 1.0
import guimodule 1.0 as GUI

FlowNodeItem{

    id:root
    expandOnEdit: true

    resizable: true
    contentItem:  Rectangle{
        enabled:editMode
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            TextField{
                id:command_lbl
                Layout.fillWidth: true

                text: root.node.commandToSend
                onTextChanged: {
                    root.node.commandToSend=text
                }


                selectByMouse:true
                GUI.MaterialPlaceHolder{

                    placeHolderText:"Command"
                }
            }
            Button{
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                highlighted: true
                text: "Send"
                onClicked: {
                    root.node.doSendCommand()
                }
            }
        }
    }

}
