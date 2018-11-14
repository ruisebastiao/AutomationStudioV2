
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

    //    onPreProcessingConfigItemChanged: {
    //        if(preProcessingConfigItem){
    //            preProcessingConfigItem.parent=preprocessing
    //        }
    //    }

    //    property Item postProcessingConfigItem

    //    onPostProcessingConfigItemChanged: {
    //        if(postProcessingConfigItem){
    //            postProcessingConfigItem.parent=postprocessing
    //        }
    //    }


    expandOnEdit: true
    onEditModeChanged:{
        if(editMode==false){
            f.fitToScreen();
        }

        console.log("editmode:"+editMode)
    }

    resizable:true

    ROISideContainerItem{
        id:right_container
        z:999999
        containerSize:450
        side:"right"
        roiPressed: root.isPressed
        show: root.selected==true && root.editMode==true
        //        visible: postProcessingConfigItem
        contentItem: ColumnLayout{
            anchors.fill: parent
            //            Item{
            //                id:right_common
            //                Layout.preferredHeight: 60
            //                Layout.fillWidth: true

            //                CheckBox{
            //                    anchors.fill: parent
            //                    text: "Draw Results in source"
            //                    checked: root.node.drawInSource
            //                    onCheckedChanged: {
            //                        root.node.drawInSource=checked
            //                    }
            //                }
            //            }


            Item{
                id:postprocessing
                GroupBox{
                    anchors.fill: parent
                    title: "Post Processing"

                    ListView{
                        clip:true
                        id:postprocessing_list
                        onCurrentIndexChanged: {
                            //console.log("index:"+currentIndex)
                        }

                        anchors.fill: parent
                        model: root.node.postProcessors

                        onModelChanged: {
                            postprocessing_list.currentIndex=0
                        }

                        Component {
                            id: postprocessors_Delegate

                            Rectangle{

                                anchors.horizontalCenter: parent.horizontalCenter
                                id: postprocessor_wrapper

                                width: postprocessing_list.width-10
                                height: postprocessor_loader.height+10

                                Loader{
                                    id:postprocessor_loader
                                    anchors.top: parent.top
                                    source:visualItem
                                    width: parent.width-10
                                    onLoaded: {
                                        item.processor=processor
                                    }

                                }

                            }

                        }

                        focus: true

                        delegate:postprocessors_Delegate


                    }

                }

                Layout.fillHeight: true
                Layout.fillWidth: true
            }

        }

    }


    ROISideContainerItem{
        id:left_container
        z:999999
        side:"left"
        containerSize:450
        roiPressed: root.isPressed
        show: root.selected && root.editMode==true
        //        visible: preProcessingConfigItem
        contentItem: ColumnLayout{
            anchors.fill: parent
            //            Item{
            //                id:left_common
            //                Layout.preferredHeight: 60
            //                Layout.fillWidth: true
            //                CheckBox{
            //                    anchors.fill: parent
            //                    checked: root.node.showOriginal
            //                    text:"Show original"
            //                    onCheckedChanged: {
            //                        root.node.showOriginal=checked;
            //                        if(root.node.configsLoaded){
            //                            root.node.reProcess();
            //                        }

            //                    }
            //                }
            //            }


            Item{
                id:preprocessing
                GroupBox{
                    anchors.fill: parent
                    title: "Pre Processing"

                    ListView{
                        clip:true
                        id:preprocessing_list
                        onCurrentIndexChanged: {

                        }

                        anchors.fill: parent
                        model: root.node.preProcessors

                        onModelChanged: {
                            preprocessing_list.currentIndex=0
                        }

                        Component {
                            id: preprocessing_Delegate




                            Rectangle{
                                //

                                anchors.horizontalCenter: parent.horizontalCenter
                                id: preprocessing_wrapper
                                //                                width: parent.width; height:
                                width: preprocessing_list.width-10
                                height: preprocessing_loader.height+10
                                Loader{
                                    id:preprocessing_loader
                                    anchors.top: parent.top
                                    source:visualItem
                                    width: parent.width-10
                                    onLoaded: {
                                        item.processor=processor
                                    }

                                }

                            }

                        }

                        focus: true


                        delegate:preprocessing_Delegate




                    }


                    //                    ColumnLayout{
                    //                        anchors.fill: parent
                    //                    }
                }

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
