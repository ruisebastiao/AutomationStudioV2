
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import QuickQanava          2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0

FlowNodeItem {
    id: root

    property bool isPressed: false

    property Item preProcessingConfigItem

    onPreProcessingConfigItemChanged: {
        if(preProcessingConfigItem){
            preProcessingConfigItem.parent=preprocessing
        }
    }

    property Item postProcessingConfigItem

    onPostProcessingConfigItemChanged: {
        if(postProcessingConfigItem){
            postProcessingConfigItem.parent=postprocessing
        }
    }


    resizable:true

    ROISideContainerItem{
        id:right_container
        z:999999
        side:"right"
        roiPressed: root.isPressed
        roiSelected: root.selected
        visible: postProcessingConfigItem
        contentItem: ColumnLayout{
            anchors.fill: parent
            Item{
                id:right_common
                Layout.preferredHeight: 60
                Layout.fillWidth: true

                CheckBox{
                    anchors.fill: parent
                    text: "Draw Results in source"
                    checked: root.node.drawInSource
                    onCheckedChanged: {
                        root.node.drawInSource=checked
                    }
                }
            }
            Item{
                id:postprocessing
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

    }


    ROISideContainerItem{
        id:left_container
        z:999999
        side:"left"
        roiPressed: root.isPressed
        roiSelected: root.selected
        visible: preProcessingConfigItem
        contentItem: ColumnLayout{
            anchors.fill: parent
            Item{
                id:left_common
                Layout.preferredHeight: 60
                Layout.fillWidth: true
                CheckBox{
                    anchors.fill: parent
                    checked: root.node.showOriginal
                    text:"Show original"
                    onCheckedChanged: {
                        root.node.showOriginal=checked;
                        if(root.node.configsLoaded){
                            root.node.reProcess();
                        }

                    }
                }
            }
            Item{
                id:preprocessing
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }


    }

    contentItem: ColumnLayout{
        anchors.fill: parent

        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true

//            border.color: Material.primary
            Layout.margins: 5
            clip: true
            QMatView{

                id:viewer
                property real viewerRatio:implicitWidth/implicitHeight;
                height: parent.height
                width: height*viewerRatio
                anchors.centerIn: parent

                Behavior on opacity{

                    NumberAnimation{
                        duration: 250
                    }
                }

                MouseArea{
                    anchors.fill: parent
//                    onWheel: {
//                        console.log(wheel.y);
//                        viewer.scale+=0.05
//                    }
                }


            }
        }
    }
    Connections{

        target: node

        onOutputChanged:{
            viewer.mat=output

        }

    }


}
