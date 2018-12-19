
//-----------------------------------------------------------------------------
// This file is a part of the QuickQanava software library. Copyright 2015 Benoit AUTHEMAN.
// \file	Port.qml
// \author	benoit@destrat.io
// \date	2017 08 12
//-----------------------------------------------------------------------------
import QtQuick 2.7
import QtQuick.Controls 2.1

import guimodule 1.0 as GUI


import QuickQanava 2.0 as Qan
import "qrc:/QuickQanava" as Qan

Qan.PortItem {
    id: portItem
    width: 24
    height: 24
    states: [
        State {
            name: "left"
            when: dockType === Qan.NodeItem.Left

            AnchorChanges {
                target: labelPane
                anchors {
                    left: undefined
                    top: undefined
                    right: contentItem.right
                    bottom: contentItem.top
                    horizontalCenter: undefined
                }
            }
        },
        State {
            name: "top"
            when: dockType === Qan.NodeItem.Top

            AnchorChanges {
                target: labelPane
                anchors {
                    left: undefined
                    top: undefined
                    right: undefined
                    bottom: contentItem.top
                    horizontalCenter: contentItem.horizontalCenter
                }
            }
        },
        State {
            name: "right"
            when: dockType === Qan.NodeItem.Right

            AnchorChanges {
                target: labelPane
                anchors {
                    left: contentItem.left
                    top: undefined
                    right: undefined
                    bottom: contentItem.top
                    horizontalCenter: undefined
                }
            }
        },
        State {
            name: "bottom"
            when: dockType === Qan.NodeItem.Bottom

            AnchorChanges {
                target: labelPane
                anchors {
                    left: undefined
                    top: portItem.bottom
                    right: undefined
                    bottom: undefined
                    horizontalCenter: portItem.horizontalCenter
                }
            }

            PropertyChanges {
                target: labelPane
                width: label.implicitWidth
                height: label.implicitHeight
            }
        }
    ]

    onXChanged:{
        //        console.log("x:"+x)
        x=0
    }

    onYPositionChanged:{
        y=yPosition;
    }

    onYChanged:{

        var nodeHeight=portItem.parent.parent.height;

        var stepy=Math.round(y/portItem.height)*portItem.height

        if(stepy>0 && stepy>=((nodeHeight-height)/2)){
            stepy=((nodeHeight-height)/2)
        }
        else if(stepy< 0 && stepy<=-((nodeHeight-height)/2)){
            stepy=-((nodeHeight-height)/2)
        }

        y=stepy

    }

    Component.onCompleted: {

    }

    Rectangle {
        id: contentItem
        anchors.fill: parent
        radius: width / 2
        color: "transparent"
        border {
            color: "lightblue"
            width: 3
        }
    }

    Pane {
        id: labelPane
        property bool editing: false
        onEditingChanged: {
            if(editing){
                //port_label_editor.focus=true

            }
            else{
                //port_label_editor.focus=false
            }
        }

        opacity: 0.80
        padding: 0
        z: 2
        width: labelPane.editing?port_label_editor.implicitWidth:label.implicitWidth
        height: labelPane.editing?port_label_editor.implicitHeight:label.implicitHeight

        Label {
            id: label
            z: 3
            opacity: labelPane.editing?0:1
            text: portItem.label
            visible: opacity!=0
        }

        TextField{
            id:port_label_editor
            property string originalText: ""
            anchors.topMargin: 5
            visible: opacity!=0
            opacity: labelPane.editing?1:0
            selectByMouse:true
            Behavior on opacity {
                NumberAnimation{
                    duration: 250
                }
            }

            onVisibleChanged: {
                if(visible){
                    forceActiveFocus()
                    selectAll()
                    originalText=text;
                }
            }


            Keys.onEscapePressed: {

                text=originalText

                focus = false
            }

            onEditingFinished: {
                labelPane.editing=false
            }



            onAccepted: {
                labelPane.editing=false
            }

            text:portItem.label
            onTextChanged: {
                portItem.label=text
//                if(text===""){
//                    implicitWidth=placeholder.label.paintedWidth
//                }
            }


            //            anchors.horizontalCenter: parent.horizontalCenter
            //            anchors.top: parent.top
            //            anchors.bottom: parent.bottom
            width: contentWidth

            GUI.MaterialPlaceHolder{
                id:placeholder
                placeHolderText:"Label Name:"
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter




        }

        MouseArea{
            anchors.fill: label
            onDoubleClicked: {
                labelPane.editing=!labelPane.editing

            }
        }
    }
}