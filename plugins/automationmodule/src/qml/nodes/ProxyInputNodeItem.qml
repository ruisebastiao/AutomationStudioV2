import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import QtQuick.Layouts 1.3
import com.novares 1.0

FlowNode{
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
        Connections{
            target:root.node
            onSelectedBindedNodeChanged:{
                if(selectedBindedNode){
                    proxynode.currentIndex=proxynode.model.indexOf(selectedBindedNode)
                }

            }

        }
        Connections{
            target:proxynode.model
            onLengthChanged:{
                if(length>0 && root.node.selectedBindedNode){
                    proxynode.currentIndex=proxynode.model.indexOf(root.node.selectedBindedNode)
                }
            }

        }




        ComboBox{
            id:proxynode
            enabled: root.node.proxyType=="Output"

            Connections{
                target:root.node.selectedBindedNode
                onProxyTypeChanged:{
                    if(root.node.selectedBindedNode.proxyType===root.node.proxyType){
                        proxynode.currentIndex=-1
                    }

                }

            }


            onCurrentIndexChanged: {
                if(currentIndex==-1){
                    root.node.selectedBindedNode=null;
                }
            }

            Layout.fillWidth: true
            Layout.preferredHeight: 60

            model: root.node.proxyNodes

            //            on: {
            //                if(root.node.selectedBindedNode){
            //                    proxynode.currentIndex=proxynode.model.indexOf(root.node.selectedBindedNode)
            //                }
            //            }

            delegate:ItemDelegate{
                width: parent.width
                text: nodeName
                visible: node.proxyType!==proxytype.currentText && node.id!==root.node.id
                height: visible ? 60 : 0
                property bool isCurrentItem: proxynode.currentIndex==index
                onIsCurrentItemChanged: {
                    if(isCurrentItem){

                        root.node.selectedBindedNode=node;
                    }
                }
                //                Component.onCompleted: {
                //                    if(root.node.selectedBindedNode){
                //                        proxynode.currentIndex=proxynode.model.indexOf(root.node.selectedBindedNode)
                //                    }


                //                }

            }


            textRole: "nodeName"



        }


    }


}
