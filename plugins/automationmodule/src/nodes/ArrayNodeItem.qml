
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0

import automationmodule 1.0 as Module

FlowNodeItem{

    id:root

    property var nodeArray: root.node.array


    onNodeArrayChanged: {
        console.log("type:"+typeof(nodeArray))
        if(nodeArray){
            console.log("nodeArray:"+nodeArray.value)
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

            }
        }
    }
}
