import QtQuick              2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import SortFilterProxyModel 1.0

import automationmodule 1.0
import epsonmodule 1.0
import guimodule 1.0 as GUI

FlowNodeItem{

    id:root
    expandOnEdit: true



    SortFilterProxyModel {
        id: ionodeModel




        sourceModel: root.node.flowNodes


        onCountChanged: {
            for(var i=0;i<ionodeModel.count;i++){
                var nodeModel=ionodeModel.get(i);

                if(nodeModel){
                    if(nodeModel.node.id==root.node.selectedBindedNodeID){
                        ionodes.currentIndex=i;
                        break;
                    }
                }
            }
        }

        filters: [

            ExpressionFilter {

                expression: {
                    return node.typeInfo.indexOf("IONode")>=0
                }
            }
        ]

    }


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


            ComboBox{
                id:ionodes

                Layout.fillWidth: true
                Layout.preferredHeight: 60

                model: ionodeModel

                onActivated: {
                    var item=model.get(currentIndex);
                    if(item){
                        root.node.setBindedIONode(item.node)
                    }
                }

                onCurrentIndexChanged:{

                }


                Component.onCompleted: {
                    currentIndex:-1
                }

                delegate:ItemDelegate{
                    width: parent.width
                    text: node.name



                }




                textRole: "nodeName"





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

        containerSize: 250

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
                CheckBox{
                    checked: root.node.sendOnData
                    text: "Send on Data"
                    onCheckedChanged: {
                        root.node.sendOnData=checked
                    }
                }
                CheckBox{
                    checked: root.node.invertSendInput
                    text: "Invert Send input"
                    onCheckedChanged: {
                        root.node.invertSendInput=checked
                    }
                }
                RowLayout{
                    Layout.fillWidth: true


                    Label{
                        text: "Send delay:"
                        Layout.preferredWidth: contentWidth
                    }

                    SpinBox{
                        Layout.fillWidth: true
                        value: root.node.delaySendTime
                        onValueChanged: {
                            root.node.delaySendTime=value
                        }
                        from:0
                        to:5000
                        stepSize: 100
                        editable: true
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
