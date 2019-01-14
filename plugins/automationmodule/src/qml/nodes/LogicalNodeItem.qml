
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import guimodule 1.0 as GUI

import automationmodule 1.0



FlowNodeItem{
    id:root
    expandOnEdit: true

    resizable: true


    contentItem:  ColumnLayout{
        anchors.fill: parent
        GroupBox{

            Layout.fillHeight: true
            Layout.fillWidth: true

            //        title: root.node.logicalType==LogicNode.OR?"OR":"AND"
            label:RowLayout{


                CheckBox {
                    Layout.fillWidth: true

                    checked: root.node.logicalType==LogicNode.OR
                    onCheckedChanged: {
                        if(checked){
                            root.node.logicalType=LogicNode.OR
                        }
                    }

                    text: qsTr("OR")
                }
                CheckBox {
                    Layout.fillWidth: true

                    checked: root.node.logicalType==LogicNode.AND
                    onCheckedChanged: {
                        if(checked){
                            root.node.logicalType=LogicNode.AND
                        }
                    }

                    text: qsTr("AND")
                }
            }


            Flow{
                clip: true
                anchors.fill: parent
                RadioButton{
                    checked: root.node.logicalInput1
                    text: "1"
                    enabled: root.node.in1Enabled

                }

                RadioButton{
                    checked: root.node.logicalInput2
                    text: "2"
                    enabled: root.node.in2Enabled

                }
                RadioButton{
                    checked: root.node.logicalInput3
                    text: "3"
                    enabled: root.node.in3Enabled

                }
                RadioButton{
                    checked: root.node.logicalInput4
                    enabled: root.node.in4Enabled
                    text: "4"

                }
            }
        }
        GroupBox{
            Layout.fillWidth: true
            RadioButton{
                checked: root.node.logicalOutput
//                enabled: false
//                onCheckedChanged: {
//                    if(checked!=logicalOutput){
//                        checked=logicalOutput;
//                    }
//                }

                //                text: "4"
//                checkable: false
            }
        }
    }

    GUI.SideContainerItem{

        //        nodePressed: root.isPressed
        show: root.selected && editMode

        side: "left"

        containerSize: 250

        contentItem:Item {
            anchors.fill: parent

            GroupBox{
                id:set
                anchors.fill: parent
                title: "Settings"
                anchors.margins: 10



                Flickable{
                    clip: true
                    anchors.fill: parent
                    contentHeight: layout_.childrenRect.height
                    //                    contentWidth: layout_.childrenRect.width;

                    ColumnLayout{
                        id:layout_
                        anchors.fill: parent

                        CheckBox{
                            checked: root.node.processOnInput
                            text: "Process on Input"
                            onCheckedChanged: {
                                root.node.processOnInput=checked
                            }
                        }
                        CheckBox{
                            checked: root.node.in1Enabled
                            text: "Input 1 Enabled"
                            onCheckedChanged: {
                                root.node.in1Enabled=checked
                            }
                        }
                        CheckBox{
                            checked: root.node.in2Enabled
                            text: "Input 2 Enabled"
                            onCheckedChanged: {
                                root.node.in2Enabled=checked
                            }
                        }
                        CheckBox{
                            checked: root.node.in3Enabled
                            text: "Input 3 Enabled"
                            onCheckedChanged: {
                                root.node.in3Enabled=checked
                            }
                        }
                        CheckBox{
                            checked: root.node.in4Enabled
                            text: "Input 4 Enabled"
                            onCheckedChanged: {
                                root.node.in4Enabled=checked
                            }
                        }
                        Item{
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                        }

                        //                Item{
                        //                    Layout.fillHeight: true
                        //                    Layout.fillWidth: true
                        //                }
                    }

                }
            }
        }
    }

}
