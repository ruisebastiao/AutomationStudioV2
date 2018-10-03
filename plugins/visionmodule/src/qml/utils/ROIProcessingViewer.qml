import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import QuickQanava 2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0

Item{
    property alias roiEditorGraphView: roieditorgraphView


    visible: true
    anchors.fill: parent
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
        anchors.fill: parent
        graph: roieditorGraph
        navigable: true
        clip: true

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


}
