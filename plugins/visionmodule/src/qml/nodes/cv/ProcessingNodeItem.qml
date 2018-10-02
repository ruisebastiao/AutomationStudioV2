
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0

import com.novares.cv 1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import com.novares.flow.nodes 1.0
import com.novares.utilities 1.0

import QuickQanava          2.0 as Qan
import "qrc:/QuickQanava"   as Qan
import "../"

import "../../gui" as GUI
FlowNode {
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

    GUI.ROISideContainer{
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


    GUI.ROISideContainer{
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

        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.margins: 5
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
