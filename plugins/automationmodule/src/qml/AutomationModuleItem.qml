import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0


import QuickQanava 2.0 as Qan

//import guimodule 1.0 as GUI

Item {
    id:root
    anchors.fill: parent

    property alias mainpagecontainer: mainpagecontainer


    property AutomationModule loadedmodule;


    Connections{
        target: loadedmodule

        onModuleLoadedChanged:{
            loadedmodule.loadConnections();
        }
    }


    onLoadedmoduleChanged: {

    }

    SwipeView{
        id: moduleview
        anchors.fill: parent
        visible: loadedmodule

        interactive: false
        clip: true

        currentIndex: loadedmodule.editMode?1:0
        onCurrentIndexChanged: {
            if(currentIndex==0 && loadedmodule.editMode){
                loadedmodule.editMode=false;
            }else if(currentIndex==1 && loadedmodule.editMode==false) {
                loadedmodule.editMode=true
            }
        }
        Item{
            id: mainpagecontainer

            //            Pane{
            //                anchors.fill: parent
            //                anchors.margins: 5
            //                Material.elevation:6
            //                id:mainpagecontainer

            //            }
        }

        Item {
            id: configurationspage
            Pane{
                anchors.fill: parent
                anchors.margins: 5
                Material.elevation:6
                GroupBox{
                    anchors.fill: parent
                    clip: true
                    title: "Module Configuration"
                    Item{
                        id:graphcontainer
                        property bool isMouseDown: false


                        anchors.fill: parent
                        PinchArea{
                            anchors.fill: parent
                            MouseArea{
                                scrollGestureEnabled: false
                                anchors.fill: parent

                            }

                            onPinchUpdated: {
                                var newzoom=graphView.zoom+(pinch.scale-pinch.previousScale);
                                graphView.zoomOn(pinch.center,newzoom)



                                graphView.panTo(pinch.center)
                            }

                            onPinchStarted: {
                                graphView.dragActive=true
                                graphView.viewPosition=pinch.center

                            }

                            onPinchFinished: {
                                graphView.dragActive=false
                                graphView.viewPosition=pinch.center

                            }
                        }

                        Qan.GraphView {
                            id: graphView
                            anchors.fill: parent
                            graph: dataflowGraph
                            navigable: true
                            clip: true

                            lockGridUpdate:true
                            grid: null
                            property real lastCenterX

                            property real lastCenterY

                            property real lastZoom

                            onRightClicked:{
                                //console.log("Right")
                                contextMenu.popup();
                            }

                            resizeHandlerColor: Material.accent
                            gridThickColor: Material.theme === Material.Dark ? "#4e4e4e" : "#c1c1c1"
                            CommonSceneGraph {
                                id: dataflowGraph



                                selectionPolicy :Qan.Graph.SelectOnClick
                                connectorCreateDefaultEdge: false
                                objectName: "graph"
                                anchors.fill: parent
                                clip: true
                                connectorEnabled: true
                                selectionColor: Material.accent
                                connectorColor: Material.accent
                                connectorEdgeColor: Material.accent


                                Component.onCompleted: {

                                    defaultEdgeStyle.lineType = Qan.EdgeStyle.Curved




                                }


                                Timer{
                                    id:docenterItem
                                    interval:250
                                    onTriggered: {
                                        var selectednode=dataflowGraph.selectedNode;
                                        graphView.lastCenterX=graphView.containerItem.x;
                                        graphView.lastCenterY=graphView.containerItem.y;
                                        graphView.lastZoom=graphView.zoom;
                                        graphView.fitInItem(selectednode.item,150)

                                    }
                                }


                                Connections{

                                    target:dataflowGraph.selectedNode

                                    onEditModeChanged:{

                                        if(dataflowGraph.selectedNode.centerOnEdit && dataflowGraph.selectedNode.editMode){

                                            docenterItem.start()
                                        }

                                        if(dataflowGraph.selectedNode.editMode==false && dataflowGraph.selectedNode.centerOnEdit){
                                            graphView.containerItem.x=graphView.lastCenterX;
                                            graphView.containerItem.y=graphView.lastCenterY;

                                            graphView.zoomOn(Qt.point(graphView.lastCenterX, graphView.lastCenterY),graphView.lastZoom)
                                        }
                                    }
                                }


                                //                                onConnectorRequestEdgeCreation:{

                                //                                }


                            }


                            Behavior on containerItem.scale{
                                NumberAnimation{
                                    duration: 500
                                }
                            }



                            Behavior on containerItem.x {
                                enabled: graphView.dragActive==false
                                NumberAnimation{

                                    duration: 250
                                }
                            }

                            Behavior on containerItem.y {
                                enabled:graphView.dragActive==false
                                NumberAnimation{
                                    duration: 250
                                }
                            }


                            Component.onCompleted: {

                                if(root.loadedmodule){
                                    root.loadedmodule.graphView=graphView
                                }




                            }



                            Menu {
                                id: contextMenu
                                width: 300
                                height: 300
                                contentItem:ColumnLayout{
                                    anchors.fill: parent
                                    TabBar {
                                        id: bar
                                        width: parent.width

                                        TabButton {
                                            width: implicitWidth
                                            text: qsTr("Common")
                                        }
                                        TabButton {
                                            width: implicitWidth
                                            text: root.loadedmodule.moduleName
                                        }
                                    }
                                    StackLayout {
                                        width: parent.width

                                        currentIndex: bar.currentIndex
                                        Item {
                                            id: commonTab

                                            Layout.fillWidth:true
                                            Layout.fillHeight:true
                                            Rectangle{
                                                anchors.fill: parent
                                                anchors.margins: 5
                                                ListView {
                                                    id: listView_common
                                                    clip: true
                                                    anchors.fill: parent
                                                    model: root.loadedmodule.commonNodeTypes
                                                    delegate:Item {
                                                        id:common_delegate
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
                                                            horizontalAlignment:Text.AlignHCenter
                                                            verticalAlignment: Text.AlignVCenter
                                                            //                     fontSizeMode:Text.Fit
                                                        }
                                                        MouseArea{
                                                            anchors.fill: parent
                                                            hoverEnabled: true
                                                            onEntered:{
                                                                common_delegate.ListView.view.currentIndex = index;

                                                            }

                                                            onClicked: {


                                                                root.loadedmodule.addCommonNode(Qt.point(contextMenu.x,contextMenu.y),modelData,graphView)
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

                                        Item {
                                            id: moduleTab

                                            Layout.fillWidth:true
                                            Layout.fillHeight:true
                                            Rectangle{
                                                anchors.fill: parent
                                                anchors.margins: 5
                                                ListView {
                                                    id: listView_module
                                                    clip: true
                                                    anchors.fill: parent
                                                    model: root.loadedmodule.moduleNodeTypes
                                                    delegate:Item {
                                                        id:module_delegate
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
                                                            horizontalAlignment:Text.AlignHCenter
                                                            verticalAlignment: Text.AlignVCenter
                                                            //                     fontSizeMode:Text.Fit
                                                        }
                                                        MouseArea{
                                                            anchors.fill: parent
                                                            hoverEnabled: true
                                                            onEntered:{
                                                                module_delegate.ListView.view.currentIndex = index;

                                                            }

                                                            onClicked: {


                                                                root.loadedmodule.addModuleNode(Qt.point(contextMenu.x,contextMenu.y),modelData,graphView)
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
                            }



                        }
                    }
                }
            }
        }

        contentItem: ListView {
            model: moduleview.contentModel
            interactive: moduleview.interactive
            currentIndex: moduleview.currentIndex

            spacing: moduleview.spacing
            orientation: moduleview.orientation
            snapMode: ListView.SnapOneItem
            boundsBehavior: Flickable.StopAtBounds

            highlightRangeMode: ListView.StrictlyEnforceRange
            preferredHighlightBegin: 0
            preferredHighlightEnd: 0
            highlightMoveDuration: 250
            //                    min:10

            maximumFlickVelocity: 4 * (moduleview.orientation === Qt.Horizontal ? width : height)
        }


    }


    PageIndicator {
        id: indicator
        visible: loggedUser && loggedUser.role==User.AdminRole
        count: moduleview.count
        currentIndex: moduleview.currentIndex

        anchors.bottom: moduleview.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

}


