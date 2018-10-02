import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import com.novares 1.0
import com.novares.flow.graph 1.0
import QuickQanava 2.0 as Qan
import "qrc:/QuickQanava"   as Qan
import "../graph"
import com.novares.cv 1.0
import com.novares.utilities 1.0
import com.novares.nodes 1.0

import "../gui" as GUI


FlowNode{
    id:root


    expandOnEdit:true



    resizable:editMode;


    onResizeEndChanged: {
        if(resizeEnd){
            //         fittimer.start()
            visionGraphView.fitInView()
        }
    }

    onEditModeChanged: {



    }




    contentItem:Item{
        id:maincontainer
        property ROINode selectedROINode:visionGraph.selectedNode

        state: selectedROINode&&selectedROINode.editMode?"editroi":"normal"

        anchors.fill: parent
        Item{
            id:content
            anchors.fill: parent

            Item{
                id:controls

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                clip:true
                height: root.editMode?60:0
                Behavior on height{
                    SequentialAnimation{
                        id:heightAnimation
                        NumberAnimation { duration: 150 }

                    }
                }
                Item{
                    anchors.fill: parent
                    visible: opacity!=0
                    opacity: maincontainer.state=="editroi"?1:0
                    Behavior on opacity{
                        SequentialAnimation{

                            NumberAnimation { duration: 250 }

                        }
                    }
                    Button{

                        highlighted: true
                        width: 120
                        height: parent.height
                        //                        anchors.left: parent.

                        text:"Back"
                        onPressed: maincontainer.selectedROINode.editMode=false;
                    }
                }

                RowLayout {
                    opacity: maincontainer.state=="normal"?1:0
                    visible: opacity!=0
                    Behavior on opacity{
                        SequentialAnimation{

                            NumberAnimation { duration: 250 }

                        }
                    }

                    anchors.fill: parent
                    Label{
                        text: "Zoom:"
                    }

                    Slider {
                        id: zoomSlider
                        Layout.fillWidth: true
                        // Layout.minimumWidth: 200
                        to: 40
                        from:0
                        stepSize: 0.1
                        value:visionGraphView.zoom

                        onValueChanged: {
                            if(pressed){
                                visionGraphView.zoom=value
                            }

                            // vision_graphview.zoom = value
                        }
                        property real rtValue: from + position * (to - from)
                        onPositionChanged: {

                            //  navigable.zoom = rtValue
                        }
                        //Component.onCompleted: value = vision_graphview.zoom
                    }


                    Button {
                        text: "Fit in view"
                        onClicked: visionGraphView.fitInView()
                    }
                } // RowLayout options

            }

            Item{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: controls.bottom
                anchors.bottom: parent.bottom
                enabled: root.editMode
                Rectangle{
                    id:navigable_container

                    border.color: Material.color(Material.accent)
                    border.width: 3

                    anchors.fill: parent

                    PinchArea{
                        anchors.fill: parent
                        enabled: editMode
                        MouseArea{
                            scrollGestureEnabled: false
                            anchors.fill: parent

                        }

                        onPinchUpdated: {
                            var newzoom=visionGraphView.zoom+(pinch.scale-pinch.previousScale);
                            visionGraphView.zoomOn(pinch.center,newzoom)



                            visionGraphView.panTo(pinch.center)
                        }

                        onPinchStarted: {
                            visionGraphView.dragActive=true
                            visionGraphView.viewPosition=pinch.center

                        }

                        onPinchFinished: {
                            visionGraphView.dragActive=false
                        }
                    }

                    Qan.GraphView {
                        id: visionGraphView
                        clip: true

                        enabled:roieditor.visible==false
                        property real lastCenterX

                        property real lastCenterY

                        property real lastZoom

                        property bool doFit: false


                        resizeHandlerColor:"transparent"

                        resizeHandlerWidth:0
                        resizeHandlerRadius:resizeHandlerWidth
                        resizeHandlerSize: "0x0"

                        anchors.fill: parent
                        containerSizeLocked:true

                        graph:visionGraph

                        Rectangle {
                            anchors.right: visionGraphView.right
                            anchors.bottom: visionGraphView.bottom
                            width: 0.2 * parent.width
                            height: 0.2 * parent.height
                            opacity: 0.8
                            color: "red"
                            border.width: 2
                            border.color: Material.accent
                            Qan.NavigablePreview {
                                anchors.fill: parent; anchors.margins: 1
                                source: visionGraphView
                                visible: true
                            }
                        }

                        Component.onCompleted: {
                            node.visionGraphView=visionGraphView
                            node.centerOnEdit= true

                        }



                        onNodeDoubleClicked:{

                            visionGraphView.doFit=!visionGraphView.doFit;

                            if(visionGraphView.doFit){
                                visionGraphView.lastCenterX=visionGraphView.containerItem.x;
                                visionGraphView.lastCenterY=visionGraphView.containerItem.y;
                                visionGraphView.lastZoom=visionGraphView.zoom;
                                visionGraphView.fitInItem(visionGraph.selectedNode.item,250)


                            }
                            else{
                                visionGraphView.containerItem.x=visionGraphView.lastCenterX;
                                visionGraphView.containerItem.y=visionGraphView.lastCenterY;
                                visionGraphView.zoomOn(Qt.point(visionGraphView.lastCenterX, visionGraphView.lastCenterY),visionGraphView.lastZoom)
                            }

                        }

                        Behavior on containerItem.scale{
                            enabled: visionGraphView.dragActive==false
                            NumberAnimation{
                                duration: 500
                            }
                        }



                        Behavior on containerItem.x {
                            enabled: visionGraphView.dragActive==false
                            NumberAnimation{

                                duration: 250
                            }
                        }

                        Behavior on containerItem.y {
                            enabled:visionGraphView.dragActive==false
                            NumberAnimation{
                                duration: 250
                            }
                        }



                    }


                    SceneGraph {
                        id: visionGraph

                        connectorCreateDefaultEdge: false
                        selectionPolicy :Qan.Graph.SelectOnClick
                        objectName: "visiongraph"
                        anchors.fill: visionGraphView
                        clip: true
                        connectorEnabled: false
                        selectionColor: Material.accent
                        connectorColor: Material.accent
                        connectorEdgeColor: Material.accent



                    }


                    QMatView{
                        id:viewer
                        anchors.fill: parent
                        parent: visionGraphView.containerItem
                        mat:node.frameSource


                        onImplicitWidthChanged: {
                            visionGraphView.containerItem.width=viewer.implicitWidth;
                        }

                        onImplicitHeightChanged:  {
                            visionGraphView.containerItem.height=viewer.implicitHeight;
                        }

                        onSizeUpdatedChanged: {
                            if(sizeUpdated){
                                visionGraphView.fitInView()
                            }
                        }

                    }

                }

                FastBlur {
                    anchors.fill: navigable_container
                    source: navigable_container
                    visible: radius!=0
                    radius: maincontainer.state=="editroi"?32:0
                    Behavior on radius{
                        SequentialAnimation{

                            NumberAnimation { duration: 250 }

                        }
                    }

                }

                GUI.ROIEditor{
                    id:roieditor

                    selectedROINode:visionGraph.selectedNode

                    anchors.fill: parent
                    opacity: maincontainer.state=="editroi"?1:0
                    visible: opacity!=0
                    Behavior on opacity{
                        SequentialAnimation{

                            NumberAnimation { duration: 250 }

                        }
                    }


                }
            }
        }




    }


}
