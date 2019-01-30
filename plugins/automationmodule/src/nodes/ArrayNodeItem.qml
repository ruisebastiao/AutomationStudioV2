
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0

import automationmodule 1.0 as Module

FlowNodeItem{

    id:root

    property var nodeArrayList: root.node.arrayList


    onNodeArrayListChanged: {

        if(nodeArrayList && nodeArrayList.length>0){
            console.log("nodeArray:"+nodeArrayList[0])
            //arryindex.to=nodeArrayList.length-1
        }
    }

    //property bool isValidArray:

    property bool initialized: false
    resizable:true;
    expandOnEdit:true;

    contentItem:  Rectangle{

        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent
            SpinBox{
                id:arryindex
                enabled: nodeArrayList.length>0
                from:-1
//                to:nodeArrayList?nodeArrayList.length-1:0
                value: root.node.arrayIndex
                onValueModified: {
                    if(value<nodeArrayList.length){
                        root.node.arrayIndex=value
                    }
                    else{
                        value=nodeArrayList.length-1
                    }


                }

//                onValueChanged: {
//
//                }
            }
        }
    }
}
