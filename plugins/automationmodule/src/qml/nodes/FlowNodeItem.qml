
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0 as GUI

import QuickQanava          2.0 as Qan

Qan.NodeItem {
    id: root


    property alias showBackground: background.visible

    property bool nodeConfigsLoaded: false

    property bool serializedDims: true

    property bool expandOnEdit: false

    property Item customHeader: null

    onCustomHeaderChanged: {
        if(customHeader){
            customHeader.parent=customHeaderContainer
        }
    }

    leftDock: Item{
        id: leftdock
        width: 24
        z: 1.5   // Selection item z=1.0, dock must be on top of selection


        anchors.rightMargin: 2

        property var hostNodeItem

        onHostNodeItemChanged: {
            if(hostNodeItem){
                leftdock.height=hostNodeItem.height
                leftdock.anchors.right=hostNodeItem.left
                leftdock.anchors.verticalCenter= hostNodeItem.verticalCenter
            }
        }

    }

    rightDock: Item{
        id: rightdock
        width: 24
        z: 1.5   // Selection item z=1.0, dock must be on top of selection

        property var hostNodeItem

        anchors.leftMargin: 2
        onHostNodeItemChanged: {
            if(hostNodeItem){
                rightdock.height=hostNodeItem.height
                rightdock.anchors.left=hostNodeItem.right
                rightdock.anchors.verticalCenter= hostNodeItem.verticalCenter
            }
        }

    }


    Component.onCompleted: {
        if(serializedDims){
            root.width=root.node.normalWidth;
        }

        if(serializedDims){
            root.height=root.node.normalHeight;
        }
    }



    Connections{

        target: node

        onNormalWidthChanged:{
            if(serializedDims){
                root.width=root.node.normalWidth;

            }
        }

        onNormalHeightChanged:{
            if(serializedDims){
                root.height=root.node.normalHeight;
            }
        }

        //        //on
        //        onBindSourceProperty:{


        //            if(!sourceNode){
        //                return;
        //            }

        //            // console.log("Node: "+root.node+" | Binding target:"+targetProperty+"("+root.node[targetProperty]+") to source:"+sourceProperty)




        //            //            if( root.node[targetProperty]==undefined ){
        //            //                console.log("Undefined target property:"+targetProperty+"| Node:"+root.node+" id:"+root.node.id);
        //            //            }
        //            //            else{
        //            root.node[targetProperty]=Qt.binding(function() {
        //                //                    if(sourceNode[sourceProperty]==undefined ){
        //                //                        console.log("Undefined source property:"+sourceProperty+"| Node:"+root.node+" id:"+root.node.id);
        //                //                        return null
        //                //                    }



        //                return sourceNode[sourceProperty];
        //            })
        //            //            }
        //        }
        //        onBindPropertyToTarget:{

        //            target[targetproperty]=Qt.binding(function() {
        //                return root.node[sourceproperty];
        //            });
        //        }

        //        onUnbindSourceProperty:{

        //            root.node[targetProperty]=null;

        //        }

        //        onBindPortLabelToProperty:{

        //            var portItemLabel=portItem.label;
        //            portItem.label=Qt.binding(function() {

        //                return portItemLabel+" ("+root.node[nodeProperty]+")";

        //            })

        //        }


        onConfigsLoadedChanged:{
            nodeConfigsLoaded=true;

        }
    }



    draggable:editMode==false


    Qan.BottomRightResizer {
        z:999
        target: parent

        minimumTargetSize.width: 75
        minimumTargetSize.height: 50
        opacity:selected&&resizable?0.75:0
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

            if(editMode){
                root.node.editWidth=parent.width
                root.node.editHeight =parent.height
            }
            else{
                root.node.normalWidth=parent.width
                root.node.normalHeight =parent.height
            }


        }
    }



    property bool resizeEnd: false


    property Item contentItem
    property bool editMode: root.node.editMode
    onEditModeChanged: {
        root.node.editMode=editMode

    }




    connectable: Qan.NodeItem.UnConnectable     // Do not show visual edge connector, use out port instead

    resizable:false;

    onStateChanged: {
        resizeEnd=false
    }

    //    state:

    states: [
        State {
            name: "edit"
            when: root.editMode && root.expandOnEdit==true
            PropertyChanges {
                target: root;
                width:root.node.editWidth
                height:root.node.editHeight
            }
        }
    ]
    transitions: Transition {
        reversible:true

        NumberAnimation {

            properties: "width,height";
            easing.type: Easing.InOutQuad;
            duration: 350

        }
        onRunningChanged : {
            resizeEnd=!running;
        }

    }


    onContentItemChanged: {
        contentItem.parent=container
    }


    RoundButton{
        width: 48
        height: 48

        visible: root.selected
        z:99999
        x:root.width-width+5
        y:-5
        highlighted: true
        Image {
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            source: root.editMode?"qrc:/images/pencil.png":"qrc:/images/pencil-lock.png"
        }
        onPressed: {
            root.editMode=!root.editMode
        }

    }


    RoundButton{
        width: 48
        height: 48
        antialiasing: true
        visible: root.node.editMode && selected
        z:99999
        x:5

        y:0
        highlighted: true
        Image {
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            source: "qrc:/images/baseline_delete_white_48dp.png"
        }
        onPressed: {
            root.node.remove()
        }

    }




    Rectangle{
        id:background;
        anchors.fill: parent
        radius: 5
        border.color: Material.primary
    }

    Item{
        id:root_container

        anchors.fill: parent
        clip: true


        //color: "red"
        ColumnLayout{
            anchors.fill: parent


            Rectangle{
                id:header_teste

                radius: 5
                Layout.fillWidth: true
                Layout.preferredHeight:50
                Layout.topMargin: 5
                Layout.leftMargin: 5
                Layout.rightMargin: 5

                Material.elevation:5

                Item {
                    id:customHeaderContainer
                    anchors.fill: parent
                    visible: customHeader!=null

                }

                Item{
                    anchors.fill: parent
                    visible: customHeader===null
                    Label{
                        id:header_text
                        text:root.node.name+" | ID:"+root.node.id
                        opacity: 1-node_name_editor.opacity
                        visible: opacity!=0
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter


                        MouseArea{
                            id:ma_editnodename
                            visible: node_name_editor.visible==false
                            anchors.fill: parent
                            enabled: editMode

                            onDoubleClicked:   {
                                node_name_editor.opacity=1;
                                node_name_editor.focus=true;

                            }
                        }


                    }

                    TextField{
                        id:node_name_editor
                        anchors.topMargin: 5
                        visible: opacity!=0
                        opacity: 0
                        selectByMouse:true
                        Behavior on opacity {
                            NumberAnimation{
                                duration: 250
                            }
                        }
                        onTextChanged: {
                            if(root.node.configsLoaded){
                                root.node.name=text
                            }
                        }

                        onAccepted: {
                            focus=false
                        }

                        text:root.node.name


                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        width: contentWidth

                        GUI.MaterialPlaceHolder{
                            id:placeholder
                            placeHolderText:"Node Name:"
                        }
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        onFocusChanged: {
                            if(focus==false){
                                node_name_editor.opacity=0;
                            }
                        }

                    }

                }


            }
            Rectangle{
                id:separator
                Layout.fillWidth: true
                Layout.leftMargin: 5
                Layout.rightMargin: 5
                Layout.preferredHeight: 2
                border.color: Material.primary

            }

            Item{
                id:containerLayout
                //                Layout.preferredHeight:container.childrenRect.height
                Layout.fillHeight: true

                Layout.fillWidth: true


                Rectangle{
                    id:container
                    radius:  background.visible?5:0

                    color: background.visible?"white":"transparent"


                    anchors.fill: parent
                    anchors.leftMargin: 5
                    anchors.rightMargin: 5
                    anchors.bottomMargin: 5


                    Material.elevation:5


                }
            }


        }

    }




    //    Item{
    //        id:overlay
    //        anchors.fill: parent


    //        z:100



    //        MouseGrabber{
    //            anchors.fill: parent
    //            proxyTo: root
    //            viewport: window
    //            active:root.editMode==false


    //        }


    //    }



}
