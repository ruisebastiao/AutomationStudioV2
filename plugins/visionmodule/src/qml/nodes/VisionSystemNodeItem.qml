import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QuickQanava 2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0

import guimodule 1.0 as GUI


FlowNodeItem{
    id:root


    expandOnEdit:true



    resizable:true;


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
                    RowLayout {

                        anchors.fill: parent

                        Button{

                            highlighted: true
                            Layout.preferredWidth: 120
                            height: parent.height
                            Layout.fillHeight: true

                            text:"Back"
                            onPressed: maincontainer.selectedROINode.editMode=false;

                        }
                        Button{

                            highlighted: true
                            Layout.preferredWidth: 120
                            Layout.fillHeight: true

                            text:"Process"
                            onPressed: maincontainer.selectedROINode.reProcess();

                        }
                        CheckBox{
                            text: "HighPerformanceMode"
                            checked: visionGraphView.highPerformanceMode
                            onCheckedChanged:{
                                visionGraphView.highPerformanceMode=checked
                            }
                        }
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

                    opacity: maincontainer.state=="editroi"?0:1
                    visible: opacity!=0
                    Behavior on opacity{
                        SequentialAnimation{

                            NumberAnimation { duration: 250 }

                        }
                    }

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

                        property bool highPerformanceMode:true


                        enabled:roieditor.visible==false
                        property real lastCenterX

                        property real lastCenterY

                        property real lastZoom

                        property bool doFit: false

                        lockGridUpdate:true

                        resizeHandlerColor:"transparent"
                        zoomMax:0.9
                        resizeHandlerWidth:0
                        resizeHandlerRadius:resizeHandlerWidth
                        resizeHandlerSize: "0x0"

                        anchors.fill: parent
                        containerSizeLocked:true

                        grid: null

                        graph:visionGraph

                        property point rightClickPos
                        onRightClicked:{
                            var mapped=mapToItem(graphView.containerItem,pos.x,pos.y);
                            rightClickPos=mapped
                            contextMenu.popup();
                        }

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


                    VisionGraph {
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
                                        text: qsTr("Vision")
                                    }

                                }
                                StackLayout {
                                    width: parent.width

                                    currentIndex: bar.currentIndex
                                    Item {
                                        id: visionTab

                                        Layout.fillWidth:true
                                        Layout.fillHeight:true
                                        Rectangle{
                                            anchors.fill: parent
                                            anchors.margins: 5
                                            ListView {
                                                id: listView_visiom
                                                clip: true
                                                anchors.fill: parent
                                                model: visionGraph.visionNodeTypes
                                                delegate:Item {
                                                    id:vision_delegate
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
                                                            vision_delegate.ListView.view.currentIndex = index;

                                                        }

                                                        onClicked: {


                                                            visionGraph.addNode(visionGraphView.rightClickPos,modelData)
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

                //                FastBlur {
                //                    anchors.fill: navigable_container
                //                    source: navigable_container
                //                    visible: radius!=0
                //                    radius: maincontainer.state=="editroi"?32:0
                //                    Behavior on radius{
                //                        SequentialAnimation{

                //                            NumberAnimation { duration: 250 }

                //                        }
                //                    }

                //                }

                ROIEditorItem{
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
