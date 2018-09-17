import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0

import automationmodule 1.0 as Module

Module.FlowNodeItem{

    id:root

    resizable:true;
    expandOnEdit:true;


//    Connections{
//        target: root.node

//        onBsOKChanged:{
//            console.log("pass 1")
//            if(bsvalidationmodule){
//               bsvalidationmodule.bsokSignal(root.node.bsOK)
//            }


//        }
//    }

    contentItem:  Rectangle{
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            ScrollView {
                id: view
                Layout.fillHeight: true
                Layout.fillWidth: true

                TextArea {
                    font.pixelSize: 12
                    readOnly: true
                    text: node.datain
                }
            }
        }

    }


}
