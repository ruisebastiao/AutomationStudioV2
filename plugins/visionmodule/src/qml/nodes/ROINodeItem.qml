import QtQuick 2.8

import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QuickQanava 2.0 as Qan
import "qrc:/QuickQanava"   as Qan
import com.novares.utilities 1.0
import com.novares.cv 1.0

import "../gui" as GUI
//import com.novares.cv.preprocessing 1.0

Qan.NodeItem {
    id:root
    property bool isPressed: false
    property bool roiChanged: false

    Component.onCompleted: {
        root.node.centerOnEdit=true;
    }


    //  selected:true
    selectable:true

    //property var roiProcessingGraph: value

    draggable:root.node.locked==false
    resizable:root.node.locked==false && selected



    Connections{

        target: node

        onProcessedFrameChanged:{
            //roi.input=sourceFrame
            viewer.mat=processedFrame

        }


    }




    Item{

        clip: true

        anchors.horizontalCenter: parent.horizontalCenter
        width:parent.width
        y:-configcontainer_top.height
        height: configcontainer_top.height


        Item{

            id:configcontainer_top
            width: root.width
            height:200
            Item{

            }

            RoundButton{
                highlighted: true
                width: 96
                height: 96

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                Material.background:  root.node.editMode?Material.Green:Material.accent
                anchors.margins:  30
                Image {
                    width: 64
                    height: 64
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/images/pencil.png"
                }

                onPressed: {
                    root.node.editMode=!root.node.editMode
                }

            }


            RoundButton{
                highlighted: true
                width: 96
                height: 96

                anchors.bottom: parent.bottom
                anchors.right: parent.right
                Material.background:  root.node.locked===false?Material.Green:Material.Red
                anchors.margins:  30
                Image {
                    width: 64
                    height: 64
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    source: root.node.locked===false?"qrc:/components/images/lock-open-outline.png":"qrc:/components/images/lock-outline.png"
                }

                onPressed: {
                    root.node.locked=!root.node.locked
                }

            }

            y:root.selected?5:configcontainer_top.height+5


            Behavior on y{
                enabled: root.isPressed==false
                NumberAnimation {
                    duration: 250
                    easing.type: Easing.InOutBack
                }
            }
        }



    }

    GUI.ROISideContainer{

        roiPressed: root.isPressed
        roiSelected: root.selected

        contentItem: ColumnLayout{
            anchors.fill: parent
            id:preprocessingmaincontainer
            Item{
                Layout.fillWidth: true;
                Layout.preferredHeight: 60
                Button{
                    anchors.fill: parent
                    highlighted: true;
                    text:"Process"
                    onClicked: {
                        roi.processROI();
                    }
                }
            }
            Item{

                Layout.fillWidth: true;
                Layout.preferredHeight: 40
                RowLayout{
                    anchors.fill: parent
                    Item {
                        Layout.fillWidth: true;
                        Layout.fillHeight: true;
                        CheckBox{
                            id:liveproc
                            anchors.fill: parent
                            onCheckedChanged: {
                                node.liveProcessing=checked
                            }

                            text:"Live processing"

                        }
                    }
                }
            }

            Item{
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

        }


    }

    GUI.ROISideContainer{

        roiPressed: root.isPressed
        roiSelected: root.selected

        side: "left"

        containerSize: 400

        contentItem: GroupBox{
            anchors.fill: parent
            title: "ROI Settings"
            anchors.margins: 10
            MouseArea{
                anchors.fill: parent


                onPressed: {
                    mouse.accepted=true

                }
            }

            ColumnLayout{
                anchors.fill: parent

                GridLayout{
                    enabled: !root.node.locked
                    Layout.fillWidth: true
                    rows:2
                    columns: 4
                    rowSpacing: 5
                    columnSpacing: 10
                    Text {
                        text: "X:"
                    }
                    TextField {
                        text: Math.round(root.x)
                        Layout.preferredWidth: 80
                        inputMethodHints:Qt.ImhFormattedNumbersOnly
                        onFocusChanged: {
                            if(focus){
                                selectAll()
                            }
                        }

                        onAccepted: {
                            root.x=parseInt(text, 10)
                        }

                        Keys.onUpPressed:  {
                            root.x++
                        }

                        Keys.onDownPressed:  {
                            root.x--
                        }
                    }
                    Text {
                        text: "Y:"
                    }
                    TextField {
                        text: Math.round(root.y)
                        Layout.preferredWidth: 80
                        inputMethodHints:Qt.ImhFormattedNumbersOnly
                        onFocusChanged: {
                            if(focus){
                                selectAll()
                            }
                        }

                        onAccepted: {
                            root.y=parseInt(text, 10)
                        }

                        Keys.onUpPressed:  {
                            root.y++
                        }

                        Keys.onDownPressed:  {
                            root.y--
                        }
                    }
                    Text {
                        text: "Width:"
                    }
                    TextField {
                        text: Math.round(root.width)
                        Layout.preferredWidth: 80
                        inputMethodHints:Qt.ImhFormattedNumbersOnly
                        onFocusChanged: {
                            if(focus){
                                selectAll()
                            }
                        }

                        onAccepted: {
                            root.width=parseInt(text, 10)
                        }

                        Keys.onUpPressed:  {
                            root.width++
                        }

                        Keys.onDownPressed:  {
                            root.width--
                        }
                    }
                    Text {
                        text: "Height:"
                    }
                    TextField {
                        text: Math.round(root.height)
                        Layout.preferredWidth: 80
                        inputMethodHints:Qt.ImhFormattedNumbersOnly
                        onFocusChanged: {
                            if(focus){
                                selectAll()
                            }
                        }

                        onAccepted: {
                            root.height=parseInt(text, 10)
                        }

                        Keys.onUpPressed:  {
                            root.height++
                        }

                        Keys.onDownPressed:  {
                            root.height--
                        }
                    }


                }
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }

        }
    }


    GUI.ROIProcessingViewer{
        id:processingviewer
        visible: false
        Component.onCompleted: {
            node.processingContainer=processingviewer
            node.roiEditorGraphView=processingviewer.roiEditorGraphView
        }
    }


    Qan.BottomRightResizer {
        z:999
        target: parent

        minimumTargetSize.width: 75
        minimumTargetSize.height: 50
        opacity:resizable?0.75:0
        visible:opacity!=0
        handlerColor:Material.color(Material.primary)
        handlerSize.width: 50;
        handlerSize.height: 50
        Behavior on opacity{

            NumberAnimation {
                duration: 200
                easing.type: Easing.Linear
            }
        }
        handler:Rectangle{
            color: Material.accent
            opacity: 0.25
            radius: width*0.25
        }

        onResizeEnd:{

            root.node.normalWidth=parent.width
            root.node.normalHeight =parent.height
        }
    }




    Binding{
        target: root
        property: "width"
        value: root.node.normalWidth


    }

    Binding{
        target: root
        property: "height"
        value: root.node.normalHeight
    }


    onXChanged: {

        if(x<0){
            x=0
        }
        else{
            if(root.nodeGraphView && root.nodeGraphView.containerItem && x+width>root.nodeGraphView.containerItem.width){
                x=root.nodeGraphView.containerItem.width-width
            }
        }

        root.roiChanged=true;
    }

    onYChanged:{
        if(y<0){
            y=0
        }
        else{
            if(root.nodeGraphView && root.nodeGraphView.containerItem && y+height>root.nodeGraphView.containerItem.height){
                y=root.nodeGraphView.containerItem.height-height
            }

        }

        root.roiChanged=true;
    }


    onWidthChanged: {
        root.roiChanged=true;
    }
    onHeightChanged: {
        root.roiChanged=true;
    }


    Rectangle{

        anchors.fill: parent

        border.color: "green"

        anchors.margins: -5
        border.width: 5
        color: "transparent"



    }




    QMatView{
        id:viewer
        anchors.fill: parent
        onMatChanged: {
            root.roiChanged=false
        }

        //  input: node.roiFrame
        visible: opacity!=0
        opacity: root.roiChanged==false ?1:0
        Behavior on opacity{

            NumberAnimation {
                duration: 200
                easing.type: Easing.Linear
            }
        }




    }




}
