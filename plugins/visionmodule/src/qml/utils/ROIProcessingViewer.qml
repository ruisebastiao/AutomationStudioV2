import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import QuickQanava 2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0

Item{
    id:root
    property alias roiEditorGraphView: roieditorgraphView

    property ROINode roinode

    anchors.fill: parent



    visible: true
    PinchArea{
        anchors.fill: parent
        enabled: editMode
        MouseArea{
            scrollGestureEnabled: false
            anchors.fill: parent

        }

        onPinchUpdated: {
            var newzoom=roieditorgraphView.zoom+(pinch.scale-pinch.previousScale);
            roieditorgraphView.zoomOn(pinch.center,newzoom)



            roieditorgraphView.panTo(pinch.center)
        }

        onPinchStarted: {
            roieditorgraphView.dragActive=true
            roieditorgraphView.viewPosition=pinch.center


        }

        onPinchFinished: {
            roieditorgraphView.dragActive=false
        }
    }


    Qan.GraphView {
        id: roieditorgraphView
        height:parent.height
        anchors.fill: parent

        graph: roieditorGraph
        navigable: true
        clip: true

        grid: null
        lockGridUpdate:true



        onRightClicked:{
            //console.log("Right")
            contextMenu.popup();
        }

        //        grid:null

        resizeHandlerColor: Material.accent
        gridThickColor: Material.theme === Material.Dark ? "#4e4e4e" : "#c1c1c1"
        SceneGraph {
            id: roieditorGraph


            selectionPolicy :Qan.Graph.SelectOnClick
            connectorCreateDefaultEdge: false
            objectName: "roigraph"
            anchors.fill: parent
            clip: true
            connectorEnabled: true
            selectionColor: Material.accent
            connectorColor: Material.accent
            connectorEdgeColor: Material.accent



            Component.onCompleted: {

                defaultEdgeStyle.lineType = Qan.EdgeStyle.Curved




            }
        }
    }

    Menu {
        id: contextMenu
        width: 200
        height: 300
        contentItem:Rectangle{
            color: "transparent"
            border.width: 2
            border.color: Material.color(Material.accent)
            anchors.fill: parent
            GroupBox{
                anchors.fill: parent
                anchors.margins: 5
                title: "Add processing node"
                ListView {
                    id: listView1
                    clip: true
                    anchors.fill: parent
                    model: root.roinode.processingNodeTypes
                    delegate:Item {
                        id:proc_delegate
                        width: parent.width
                        height: 40
                        property var modelDataObject: modelData
                        property var key;
                        property string value
                        onModelDataObjectChanged: {
                            for (var prop in modelDataObject) {
                                key=prop
                                value= modelDataObject[prop]
                            }
                        }

                        Label{

                            text: value
                            anchors.fill: parent
                            font.pixelSize: 16
                            horizontalAlignment:Text.AlignHLeft
                            verticalAlignment: Text.AlignVCenter
                            //                     fontSizeMode:Text.Fit
                        }
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered:{
                                proc_delegate.ListView.view.currentIndex = index;

                            }

                            onPressed: {


                                root.roinode.addProcNode(Qt.point(contextMenu.x,contextMenu.y),modelData)
                                contextMenu.dismiss()
                            }
                        }
                    }
                    highlight: Rectangle {
                        color: "lightsteelblue";
                        radius: 5
                    }
                    focus: true
                }
            }
        }
    }

}


