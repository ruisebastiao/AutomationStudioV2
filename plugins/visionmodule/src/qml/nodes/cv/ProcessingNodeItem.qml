import QtQuick              2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0
import visionmodule 1.0
import guimodule 1.0
import SortFilterProxyModel 1.0

FlowNodeItem {
    id: root

    property bool isPressed: false

    property Item processingConfigItem:null

    onProcessingConfigItemChanged:  {
        if(processingConfigItem){
            processingConfigItem.parent=processinigConfigContainer
        }
    }




    expandOnEdit: true
    onEditModeChanged:{
        if(editMode==false){
            f.fitToScreen();
        }

        console.log("editmode:"+editMode)
    }

    resizable:true


    SortFilterProxyModel {
        id: drawingnodesfilter
        filters: [
            ValueFilter {
                enabled: true


                roleName: "ProcessingTypeRole"



                value: FlowNode.ProcessingDrawingNode
            }
        ]

        sourceModel: root.node.processingnodes



    }


    SideContainerItem{
        id:left_container
        z:999999
        containerSize:450
        side:"left"
        nodePressed: root.isPressed
        show: root.processingConfigItem && root.selected==true && root.editMode==true
        visible: root.processingConfigItem
        contentItem: ColumnLayout{
            anchors.fill: parent
            GroupBox{
                title: "Common Settings"
                Layout.fillHeight: true
                Layout.fillWidth: true

                ColumnLayout{
                    anchors.fill: parent
                    CheckBox{
                        Layout.fillWidth: true
                        text: "Apply mask"
                        checked: root.node?root.node.applyMask:false
                        onCheckedChanged: {
                            if(root.node.configsLoaded){
                                root.node.applyMask=checked
                            }
                        }
                    }
                    GroupBox{
                        title: "Drawing"

                        Layout.fillWidth: true
                        ColumnLayout{
                            Layout.fillWidth: true

                            CheckBox{
                                Layout.fillWidth: true
                                text: "Draw on input source"
                                checked: root.node && root.node.drawOnSource
                                onCheckedChanged: {

                                    if(root.node.configsLoaded){
                                        root.node.drawOnSource=checked
                                    }
                                }
                            }
                            CheckBox{
                                Layout.fillWidth: true
                                text: "Show Port"
                                 enabled: root.node.drawOnSource
                                checked: root.node.drawOnSourcePortVisible
                                onCheckedChanged: {
                                    root.node.drawOnSourcePortVisible=checked
                                }
                            }

                            ComboBox{
                                Layout.fillWidth: true
                                enabled: root.node.drawOnSource


                            }
                        }

                    }
                    Item{

                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                }


            }

            Item{
                id:commonConfigContainer
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Item{

                Layout.fillHeight: true
                Layout.fillWidth: true
            }


        }

    }


    SideContainerItem{
        id:right_container
        z:999999
        containerSize:450
        side:"right"
        nodePressed: root.isPressed
        show: root.processingConfigItem && root.selected==true && root.editMode==true
        visible: root.processingConfigItem
        contentItem: ColumnLayout{
            anchors.fill: parent

            Item{
                id:processinigConfigContainer
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

        ignoreUnknownSignals: true
        onOutputChanged:{
            if(output){
                f.viewer.mat=output
            }
        }

    }


}
