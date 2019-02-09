import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import guimodule 1.0

import automationmodule 1.0


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
            visible: root.node.inputType!=StringNode.InputSerialize

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
                Component.onCompleted: {
                    placeHolderText=Qt.binding(function(){
                        if(root.node.inputType==StringNode.InputJoin)
                            return "Separator"
                        if(root.node.inputType==StringNode.InputExtract)
                            return "Extract Regex"

                        if(root.node.inputType==StringNode.InputExtract)
                            return "Compare"

                        if(root.node.inputType==StringNode.InputSerialize)
                            return "Serialize"


                        return "String";
                    })


                }


            }
        }
        RowLayout{



            TextArea{

                Layout.fillWidth: true
                text:node.stringOutput

                readOnly: true
                visible: root.node.inputType!=StringNode.InputCompare


                wrapMode: TextEdit.WordWrap


                selectByMouse:true
                MaterialPlaceHolder{
                    placeHolderText:"Output"
                }
            }


            TextArea{

                Layout.fillWidth: true
                text:node.storedValue

                readOnly: true
                visible: root.node.storedValue!=""


                wrapMode: TextEdit.WordWrap


                selectByMouse:true
                MaterialPlaceHolder{
                    placeHolderText:"Stored Value"
                }
            }


        }

        GroupBox{
            //            Layout.fillHeight: true
            Layout.fillWidth: true
            title: "Input is"

            Flow{
                anchors.fill: parent
                RadioButton{
                    checked: root.node.inputType==StringNode.InputNone
                    text: "None"
                    onCheckedChanged: {
                        if(checked){
                            root.node.inputType=StringNode.InputNone
                        }

                    }
                }

                RadioButton{
                    Layout.fillWidth: true
                    text: "Prefix"
                    checked: root.node.inputType==StringNode.InputPrefix

                    onCheckedChanged: {
                        if(checked){
                            root.node.inputType=StringNode.InputPrefix
                        }
                    }


                }
                RadioButton{
                    Layout.fillWidth: true
                    text: "Suffix"
                    checked: root.node.inputType==StringNode.InputSuffix


                    onCheckedChanged: {
                        if(checked){
                            root.node.inputType=StringNode.InputSuffix
                        }
                    }

                }
                RadioButton{
                    Layout.fillWidth: true
                    text: "Regex Extract"
                    checked: root.node.inputType==StringNode.InputExtract


                    onCheckedChanged: {
                        if(checked){
                            root.node.inputType=StringNode.InputExtract
                        }
                    }


                }
                RadioButton{
                    Layout.fillWidth: true
                    text: "Compare"
                    checked: root.node.inputType==StringNode.InputCompare


                    onCheckedChanged: {
                        if(checked){
                            root.node.inputType=StringNode.InputCompare
                        }
                    }


                }
                RadioButton{
                    Layout.fillWidth: true
                    text: "Join"
                    checked: root.node.inputType==StringNode.InputJoin


                    onCheckedChanged: {
                        if(checked){
                            root.node.inputType=StringNode.InputJoin
                        }
                    }


                }
                RadioButton{
                    Layout.fillWidth: true
                    text: "Serialize"
                    checked: root.node.inputType==StringNode.InputSerialize


                    onCheckedChanged: {
                        if(checked){
                            root.node.inputType=StringNode.InputSerialize
                        }
                    }


                }

                RadioButton{
                    Layout.fillWidth: true
                    text: "Parse"
                    checked: root.node.inputType==StringNode.InputParse


                    onCheckedChanged: {
                        if(checked){
                            root.node.inputType=StringNode.InputParse
                        }
                    }


                }
            }





        }

        Button{
            Layout.fillWidth: true
            text: "Store Output"
            highlighted: true
            onClicked: {
                root.node.storedValue=root.node.stringOutput
            }
        }




    }
}
