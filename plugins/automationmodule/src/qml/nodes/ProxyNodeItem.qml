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

//                    value: FlowNode.ProxyNode

                    roleName: "nodeTypeRole"



                    value: root.node.type==FlowNode.ModuleProxyNode?FlowNode.ModuleProxyNode:FlowNode.ProxyNode
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

        SortFilterProxyModel {
            id: modulefilter
            filters: [
                ExpressionFilter {
                    enabled: true
                    expression: {
                        return module.id !=root.node.parentModule.id
                    }
                }
            ]

            sourceModel: root.node.parentModule.parentProject.modules
        }


        ComboBox{
            id:modules
            visible: root.node.proxyType=="Output" && root.node.type==FlowNode.ModuleProxyNode



            Layout.fillWidth: true
            Layout.preferredHeight: 60

            model: modulefilter


            onCurrentIndexChanged:{
                var item=model.get(currentIndex);
                if(item){
                    root.node.selectedBindedModuleID=item.module.id
                }
            }


            Component.onCompleted: {
                currentIndex:-1
            }

            delegate:ItemDelegate{
                width: parent.width
                text: module.name



            }




            textRole: "moduleName"



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



                property bool isCurrentItem: node.id==root.node.selectedBindedNodeID
                onIsCurrentItemChanged: {
                    if(isCurrentItem){
                        proxynode.currentIndex=index
                    }



                }
            }




            textRole: "nodeName"



        }


    }

}
