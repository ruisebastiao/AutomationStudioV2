
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
                Layout.fillWidth: true
                readOnly: true
                text: root.node.dataReceived

                selectByMouse:true
                GUI.MaterialPlaceHolder{

                    placeHolderText:"Data"
                }
            }

            TextField{
                Layout.fillWidth: true

                text: root.node.commandToParse
                onTextChanged: {
                    root.node.commandToParse=text
                }


                selectByMouse:true
                GUI.MaterialPlaceHolder{

                    placeHolderText:"Command to receive"
                }
            }
//            Button{
//                Layout.fillWidth: true
//                Layout.preferredHeight: 50
//                highlighted: true
//                text: "Send"
//                onClicked: {
//                    root.node.doSendCommand()
//                }
//            }
        }
    }

}
