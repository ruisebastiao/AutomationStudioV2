
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


                RadioButton {
                    Layout.fillWidth: true

                    checked: root.node.logicalType==LogicNode.OR
                    onCheckedChanged: {
                        if(checked){
                            root.node.logicalType=LogicNode.OR
                        }
                    }

                    text: qsTr("OR")
                }
                RadioButton {
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
                GUI.ReadOnlyItem{
                    readOnly:true
                    RadioButton{
                        checked: (root.node.in1Inverted==false && root.node.logicalInput1) || (root.node.in1Inverted && root.node.logicalInput1==false)
                        text: "1"
                        visible: root.node.in1Enabled
                        autoExclusive: false
                    }
                }

                GUI.ReadOnlyItem{
                    readOnly:true
                    RadioButton{
                        checked: (root.node.in2Inverted==false && root.node.logicalInput2) || (root.node.in2Inverted && root.node.logicalInput2==false)
                        text: "2"
                        visible: root.node.in2Enabled
                        autoExclusive: false
                    }
                }
                GUI.ReadOnlyItem{
                    readOnly:true
                    RadioButton{
                        checked: (root.node.in3Inverted==false && root.node.logicalInput3) || (root.node.in3Inverted && root.node.logicalInput3==false)
                        text: "3"
                        visible: root.node.in3Enabled
                        autoExclusive: false
                    }
                }
                GUI.ReadOnlyItem{
                    readOnly:true

                    RadioButton{
                        checked: (root.node.in4Inverted==false && root.node.logicalInput4) || (root.node.in4Inverted && root.node.logicalInput4==false)
                        visible: root.node.in4Enabled
                        text: "4"
                        autoExclusive: false
                    }
                }
            }
        }
        GroupBox{
            Layout.fillWidth: true
            Flow{
                anchors.fill: parent
                GUI.ReadOnlyItem{
                    readOnly:true
                    RadioButton{
                        checked: root.node.logicalOutput
                    }
                }

                TextField{

                    //                        Layout.fillHeight: true;
                    Layout.fillWidth: true;

                    text:root.node.outputValue
                    GUI.MaterialPlaceHolder{

                        placeHolderText:"Output string"

                    }
                    onTextChanged: {
                        root.node.outputValue=text
                    }
                }


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
                        Layout.margins: 2
                        GroupBox{
                            label:CheckBox{

                                checked: root.node.in1Enabled
                                text: "Input 1 Enabled"
                                onCheckedChanged: {
                                    root.node.in1Enabled=checked
                                }

                            }

                            CheckBox{
                                checked: root.node.in1Inverted
                                text: "Invert"
                                onCheckedChanged: {
                                    root.node.in1Inverted=checked
                                }
                            }
                        }

                        GroupBox{
                            label:CheckBox{
                                checked: root.node.in2Enabled
                                text: "Input 2 Enabled"
                                onCheckedChanged: {
                                    root.node.in2Enabled=checked
                                }
                            }
                            CheckBox{
                                checked: root.node.in2Inverted
                                text: "Invert"
                                onCheckedChanged: {
                                    root.node.in2Inverted=checked
                                }
                            }
                        }
                        GroupBox{
                            label:CheckBox{
                                checked: root.node.in3Enabled
                                text: "Input 3 Enabled"
                                onCheckedChanged: {
                                    root.node.in3Enabled=checked
                                }
                            }
                            CheckBox{
                                checked: root.node.in3Inverted
                                text: "Invert"
                                onCheckedChanged: {
                                    root.node.in3Inverted=checked
                                }
                            }
                        }
                        GroupBox{
                            label:CheckBox{
                                checked: root.node.in4Enabled
                                text: "Input 4 Enabled"
                                onCheckedChanged: {
                                    root.node.in4Enabled=checked
                                }
                            }
                            CheckBox{
                                checked: root.node.in4Inverted
                                text: "Invert"
                                onCheckedChanged: {
                                    root.node.in4Inverted=checked
                                }
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
