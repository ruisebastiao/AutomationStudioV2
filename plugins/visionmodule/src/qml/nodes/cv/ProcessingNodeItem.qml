
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
        show: root.selected==true && root.editMode==true
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
                Layout.preferredHeight: 60
                Layout.fillWidth: true
                visible: root.node.baseNode===false
                RadioButton{
                    anchors.fill: parent
                    text: "End node"
                    checked: root.node.endNode
                    onCheckedChanged: {
                        root.node.endNode=checked;
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
        show: root.selected && root.editMode==true
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
                Layout.preferredHeight: 60
                Layout.fillWidth: true
                visible: root.node.endNode===false
                RadioButton{
                    anchors.fill: parent
                    text: "Base node"
                    checked: root.node.baseNode
                    onCheckedChanged: {
                        root.node.baseNode=checked;
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


            enabled: root.editMode

            QMatFlickable{
                id:f
                anchors.fill: parent
            }

            PinchArea {
                id: p
                anchors.fill: f

                property bool started: started;
                onStartedChanged: {

                }

                pinch.target: f.viewer
                pinch.maximumScale: f.maxZoom
                pinch.minimumScale: f.minZoom
                onPinchStarted: {

                }

                onPinchUpdated: {
                    f.contentX += pinch.previousCenter.x - pinch.center.x
                    f.contentY += pinch.previousCenter.y - pinch.center.y
                }

                onPinchFinished: {

                    f.returnToBounds();
                }



                MultiPointTouchArea {
                    anchors.fill: parent
                    mouseEnabled: false
                    id:mpa

                    property int pointsPressed:0
                    //                    property real start: value
                    touchPoints: [
                        TouchPoint {
                            id: point1

                            onPreviousXChanged: {
                                if(mpa.pointsPressed<2){
                                    f.contentX += previousX-x
                                }

                            }

                            onPreviousYChanged: {
                                if(mpa.pointsPressed<2){
                                    f.contentY += previousY-y
                                }
                            }

                        },

                        TouchPoint {
                            id: point2
                        }
                    ]

                    onReleased: {
                        f.returnToBounds();
                    }

                    onUpdated: {
                        //                        console.log(touchPoints.length)
                        pointsPressed=touchPoints.length
                    }
                }

            }

        }






    }
    Connections{

        target: node

        onOutputChanged:{
            f.viewer.mat=output
        }

    }


}
