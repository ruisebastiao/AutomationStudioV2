import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import guimodule 1.0

import automationmodule 1.0 as Module


FlowNodeItem{
    id:root

    expandOnEdit:true
    resizable: true
    onEditModeChanged: {
        if(editMode){
            editfield.forceActiveFocus()
        }
    }

    contentItem:   ColumnLayout{
        anchors.fill: parent

        TextArea{

            Layout.fillWidth: true
            text:node.stringValue
            onTextChanged: {
                if(node.stringValue!=text){
                    node.stringValue=text
                }


            }


            id:editfield

            wrapMode: TextEdit.WordWrap


            selectByMouse:true
            MaterialPlaceHolder{
                placeHolderText:"String"
            }
        }

        RowLayout{
            Layout.fillWidth: true

            CheckBox{
                Layout.fillWidth: true
                text: "Prefix From Input"
                checked: root.node.prefixFromInput

                onCheckedChanged: {
                    root.node.prefixFromInput=checked

                }


            }
            CheckBox{
                Layout.fillWidth: true
                text: "Suffix From Input"
                checked: root.node.suffixFromInput


                onCheckedChanged: {
                    root.node.suffixFromInput=checked
                }


            }
        }




    }
}
