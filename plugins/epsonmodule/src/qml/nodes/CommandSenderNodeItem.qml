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
            TextArea{
                id:final_lbl
                visible: root.node.appendFromInput
                Layout.fillWidth: true

                text: root.node.finalCommand

                readOnly: true

                 wrapMode: TextEdit.WordWrap

                selectByMouse:true
                GUI.MaterialPlaceHolder{

                    placeHolderText:"Final command"
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


    GUI.SideContainerItem{

//        nodePressed: root.isPressed
        show: root.selected && editMode

        side: "left"

        containerSize: 400

        contentItem: GroupBox{
            anchors.fill: parent
            title: "Settings"
            anchors.margins: 10
            MouseArea{
                anchors.fill: parent


                onPressed: {
                    mouse.accepted=true

                }
            }

            ColumnLayout{
                anchors.fill: parent
                CheckBox{
                    checked: root.node.appendFromInput
                    text: "Append to command"
                    onCheckedChanged: {
                        root.node.appendFromInput=checked
                    }
                }

                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }

        }
    }


}
