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
                placeHolderText:root.node.extractFromInput?"Regex":"String"
            }
        }

        TextArea{

            Layout.fillWidth: true
            text:node.stringOutput

            readOnly: true


            wrapMode: TextEdit.WordWrap


            selectByMouse:true
            MaterialPlaceHolder{
                placeHolderText:"Output"
            }
        }


        GroupBox{
            Layout.fillHeight: true
            Layout.fillWidth: true
            title: "Input is"

            Flow{
                anchors.fill: parent
                RadioButton{
                    text: "None"
                }

                RadioButton{
                    Layout.fillWidth: true
                    text: "Prefix"
                    checked: root.node.prefixFromInput

                    onCheckedChanged: {
                        root.node.prefixFromInput=checked

                    }


                }
                RadioButton{
                    Layout.fillWidth: true
                    text: "Suffix"
                    checked: root.node.suffixFromInput


                    onCheckedChanged: {
                        root.node.suffixFromInput=checked
                    }

                }
                RadioButton{
                    Layout.fillWidth: true
                    text: "Regex Extract"
                    checked: root.node.extractFromInput


                    onCheckedChanged: {
                        root.node.extractFromInput=checked
                    }


                }
                RadioButton{
                    Layout.fillWidth: true
                    text: "Compare"
                    checked: root.node.compareFromInput


                    onCheckedChanged: {
                        root.node.compareFromInput=checked
                    }


                }
            }




        }




    }
}
