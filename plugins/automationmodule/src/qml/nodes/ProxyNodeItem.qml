import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import QtQuick.Layouts 1.3

import guimodule 1.0
import SortFilterProxyModel 1.0
import automationmodule 1.0

FlowNodeItem{
    //    normalWidth: 200
    //    normalHeight: 100

    Connections{
        target: root.node

        onProxyTypeChanged:{
            proxytype.currentIndex= proxytype.model.indexOf(proxyType)

        }
    }


    expandOnEdit: true


    resizable:true;

    id:root
    contentItem:  ColumnLayout{
        anchors.fill: parent
        ComboBox{
            id:proxytype
            Layout.fillWidth: true
            Layout.preferredHeight: 60

            model: ["Input", "Output"]



            onCurrentIndexChanged: {
                if(currentIndex>-1){
                    root.node.proxyType=model[currentIndex]
                }

                proxynode.currentIndex=-1
            }


        }

        SortFilterProxyModel {
            id: proxyModel

            property int bindedNodeId: root.node.selectedBindedNodeID
            onBindedNodeIdChanged: {
                for(var i=0;i<proxyModel.count;i++){
                    var nodeModel=proxyModel.get(i);

                    if(nodeModel){
                        if(nodeModel.node.id==proxyModel.bindedNodeId){
                            proxynode.currentIndex=i;
                            break;
                        }
                    }
                }

            }

            //            onCountChanged: {


            //            }

            sourceModel: root.node.flowNodes

            onCountChanged: {
                for(var i=0;i<proxyModel.count;i++){
                    var nodeModel=proxyModel.get(i);

                    if(nodeModel){
                        if(nodeModel.node.id==proxyModel.bindedNodeId){
                            proxynode.currentIndex=i;
                            break;
                        }
                    }
                }
            }

            filters: [
                ValueFilter {
                    enabled: true
                    roleName: "nodeTypeRole"
                    value: FlowNode.ProxyNode
                },
                ExpressionFilter {
                    enabled: true
                    expression: {
                        return node.id !=root.node.id
                    }
                },
                ExpressionFilter {
                    enabled: true
                    expression: {
                        return node.proxyType==="Input"
                    }
                }
            ]

        }




        ComboBox{
            id:proxynode
            visible: root.node.proxyType=="Output"



            Layout.fillWidth: true
            Layout.preferredHeight: 60

            model: proxyModel


            onCurrentIndexChanged:{
                var item=model.get(currentIndex);
                if(item){
                    root.node.setBindedFlowNode(item.node)
                }
            }


            Component.onCompleted: {
                currentIndex:-1
            }

            delegate:ItemDelegate{
                width: parent.width
                text: node.name

                Component.onCompleted:  {
                    //                    if(node.id==root.node.selectedBindedNodeID){
                    //                        proxynode.currentIndex=index
                    //                    }
                }

                property bool isCurrentItem: node.id==root.node.selectedBindedNodeID
                onIsCurrentItemChanged: {
                    if(isCurrentItem){
                        proxynode.currentIndex=index
                    }


                    //                    if(root.node.configsLoaded){


                    //                        if(isCurrentItem){

                    //                            root.node.setBindedFlowNode(node);
                    //                        }
                    //                    }
                }
            }




            textRole: "nodeName"



        }


    }


}
