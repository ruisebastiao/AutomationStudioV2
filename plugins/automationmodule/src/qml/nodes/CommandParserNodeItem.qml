
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

                    placeHolderText:"Command OK Regex"
                }
            }
            TextField{
                Layout.fillWidth: true

                text: root.node.commandToReset
                onTextChanged: {
                    root.node.commandToReset=text
                }


                selectByMouse:true
                GUI.MaterialPlaceHolder{

                    placeHolderText:"Command Reset Regex"
                }
            }

            Button{
                Layout.fillWidth: true
                text: "Validate"
                onClicked: {
                    root.node.validate()
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
        }
    }

}
