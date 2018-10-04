
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

            Flickable {
                id: f
                anchors.fill: parent
                boundsBehavior: Flickable.StopAtBounds
                contentHeight: iContainer.height;
                contentWidth: iContainer.width;
                clip: true



                property bool fitToScreenActive: false

                property real minZoom: 1;
                property real maxZoom: 8

                property real zoomStep: 0.05

                onWidthChanged: {
                    if (fitToScreenActive)
                        fitToScreen();
                }
                onHeightChanged: {
                    if (fitToScreenActive)
                        fitToScreen();
                }

                Item {
                    id: iContainer
                    width: Math.max(viewer.width * viewer.scale, f.width)
                    height: Math.max(viewer.height * viewer.scale, f.height)


                    QMatView{

                        id:viewer

                        property real prevScale: 1.0;


                        smooth: f.moving
                        anchors.centerIn: parent

                        transformOrigin: Item.Center

                        onScaleChanged: {

                            if ((width * scale) > f.width) {
                                var xoff = (f.width / 2 + f.contentX) * scale / prevScale;
                                f.contentX = xoff - f.width / 2
                            }
                            if ((height * scale) > f.height) {
                                var yoff = (f.height / 2 + f.contentY) * scale / prevScale;
                                f.contentY = yoff - f.height / 2
                            }
                            prevScale=scale;
                        }



                        Behavior on opacity{

                            NumberAnimation{
                                duration: 250
                            }
                        }

                    }


                }
                function fitToScreen() {
                    var s = Math.min(f.width / viewer.width, f.height / viewer.height, 1)
                    viewer.scale = s;
                    f.minZoom = s;
                    viewer.prevScale = scale
                    fitToScreenActive=true;
                    f.returnToBounds();
                }
                function zoomIn() {
                    if (viewer.scale<f.maxZoom)
                        viewer.scale*=(1.0+zoomStep)

                    f.returnToBounds();
                    fitToScreenActive=false;
                    f.returnToBounds();
                }
                function zoomOut() {
                    console.log("f.scale:"+f.scale)
                    if (viewer.scale>f.minZoom)
                        viewer.scale*=(1.0-zoomStep)


                    f.returnToBounds();

                }
                function zoomFull() {
                    viewer.scale=1;
                    fitToScreenActive=false;
                    f.returnToBounds();
                }


                ScrollIndicator.vertical: ScrollIndicator { }
                ScrollIndicator.horizontal: ScrollIndicator { }

                MouseArea{
                    anchors.fill: parent
                    scrollGestureEnabled: false

                    onWheel: {
                        if (wheel.modifiers & Qt.ControlModifier) {
                            //                            console.log("wheel")

                            if(wheel.angleDelta.y>0){
                                f.zoomIn()
                            }
                            else{
                                f.zoomOut()
                            }

                            wheel.accepted=true
                            //                            f.contentX=mouseX
                            //                            f.contentY=-mouseY
                            //                             f.returnToBounds();
                        }
                        else{
                            wheel.accepted=false
                        }



                    }

                    //                    propagateComposedEvents: true
                }


            }


            PinchArea {
                id: p
                anchors.fill: f

                property bool started: started;
                onStartedChanged: {

                }

                pinch.target: viewer
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
            viewer.mat=output

        }

    }


}
