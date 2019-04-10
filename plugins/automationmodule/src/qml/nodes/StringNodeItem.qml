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
            visible: root.node.inputType!=StringNode.InputSerialize && root.node.inputType!=StringNode.InputReadFile

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

            ListModel{
                id:inputTypes

                function getTypeIndex(inputTypeValue){
                    for (var i = 0; i < inputTypes.count; i++){
                        var inType=inputTypes.get(i)
                        if(inType && inType.inputType==inputTypeValue){
                            return i;
                        }
                    }
                }

                ListElement {
                    name: "None"
                    inputType:StringNode.InputNone
                }

                ListElement {
                    name: "Prefix"
                    inputType: StringNode.InputPrefix
                }

                ListElement {
                    name: "Suffix"
                    inputType: StringNode.InputSuffix
                }

                ListElement {
                    name: "Regex Extract"
                    inputType: StringNode.InputExtract
                }

                ListElement {
                    name: "Compare"
                    inputType:StringNode.InputCompare
                }

                ListElement {
                    name: "Join"
                    inputType:StringNode.InputJoin
                }

                ListElement {
                    name: "Serialize"
                    inputType: StringNode.InputSerialize
                }

                ListElement {
                    name: "Parse"
                    inputType: StringNode.InputParse
                }
                ListElement {
                    name: "Read File"
                    inputType: StringNode.InputReadFile
                }
                ListElement {
                    name: "Write File"
                    inputType: StringNode.InputWriteFile
                }


            }

            ComboBox{
                width: parent.width
                model:inputTypes
                textRole:"name"
                currentIndex: inputTypes.getTypeIndex(root.node.inputType)
                onActivated: {
                    root.node.inputType=inputTypes.get(index).inputType
                }

            }



        }

        Flow{
            padding: 15
            Layout.fillWidth: true
            Button{

                text: "Store Output"
                highlighted: true
                onClicked: {
                    root.node.storedValue=root.node.stringOutput
                }
            }
            Button{

                text: "Process"
                //                visible: root.node.inputType==StringNode.InputReadFile

                highlighted: true
                onClicked: {
                    root.node.processInputs=true
                }
            }
            CheckBox{

                text: "Process on input change"

                checked: root.node.processOnInput
                onCheckedChanged: {
                    root.node.processOnInput=checked
                }
            }

        }






    }
}
