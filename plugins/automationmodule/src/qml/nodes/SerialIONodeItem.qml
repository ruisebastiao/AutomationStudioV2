
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0

import automationmodule 1.0 as Module

FlowNodeItem{

    id:root

    property bool initialized: false
    resizable:true;
    expandOnEdit:true;

    Connections{
        target: automationstudio
        onCoreApplicationChanged: {
            usbnotifier.coreApplication=coreApplication
        }
    }


    Module.USBNotifier{
        id:usbnotifier
        onPortAdded:{
            console.log("Port added");
            root.node.checkPorts()
        }
        onPortRemoved:{
            console.log("Port removed");
            root.node.checkPorts()
        }
        Component.onCompleted: {

        }
    }



    contentItem:  Rectangle{

        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent

            ColumnLayout{
                Layout.fillHeight: true
                Layout.fillWidth: true
                RowLayout{
                    Layout.fillWidth: true
                    Switch{
                        id:connect_switch


                        //                    anchors.centerIn: parent
                        text:"Connect"
                        checked: node.connected
                        onCheckedChanged: {
                            if(checked){
                                node.doConnect();
                            }
                            else{
                                node.doDisconnect();
                            }


                        }


                        contentItem: Label{
                            id:switch_label
                            height: connect_switch.indicator.height
                            verticalAlignment: Text.AlignVCenter
                            minimumPixelSize: 8;
                            font.pixelSize: 12
                            fontSizeMode:Text.HorizontalFit
                            text:connect_switch.text
                            leftPadding: connect_switch.indicator.width + connect_switch.spacing
                        }
                    }
                    Switch{
                        id:autoconnect


                        //                    anchors.centerIn: parent
                        text:"Open On Connect"
                        checked: node.autoConnect
                        onCheckedChanged: {
                            node.autoConnect=checked;
                        }


                        contentItem: Label{
                            id:connectonopen_label
                            height: autoconnect.indicator.height
                            verticalAlignment: Text.AlignVCenter
                            minimumPixelSize: 8;
                            font.pixelSize: 12
                            fontSizeMode:Text.HorizontalFit
                            text:autoconnect.text
                            leftPadding: autoconnect.indicator.width + autoconnect.spacing
                        }
                    }
                }


                RowLayout{
                    Layout.preferredHeight: 42
                    Layout.fillWidth: true

                    Connections{
                        target: root.node
                         onPortsAvailableChanged:{
                            console.log("ports changed");
                             selectedPort.currentIndex=root.node.indexOfPort(root.node.port)
                             if(selectedPort.currentIndex>-1){
                                 root.node.port=root.node.port
                             }
                        }
                    }

                    Label{
                        text:"Port: "
                    }

                    ComboBox{
                        id:selectedPort
                        Layout.fillWidth: true
                        model: node.portsAvailable
                        popup.onClosed: {
                            if(currentIndex!=-1 && currentIndex!=root.node.indexOfPort(root.node.port)){
                                root.node.port=node.portsAvailable[currentIndex];
                            }
                        }

                        onCurrentIndexChanged: {
                            console.log("currentIndex:"+currentIndex)

                        }


                        currentIndex: -1

                        Component.onCompleted: {

                        }
                    }

                    Label{
                        text:"Baudrate: "
                    }




                    ComboBox{
                        id:selectedBaudrate
                        Layout.fillWidth: true


                        model:ListModel {
                            id: cbItems
                            ListElement { textValue: "9600"; value: 9600 }
                            ListElement { textValue: "19200"; value: 19200 }
                            ListElement { textValue: "38400"; vale: 38400 }
                            ListElement { textValue: "57600"; vale: 57600 }
                            ListElement { textValue: "115200"; vale: 115200 }
                            ListElement { textValue: "250000"; vale: 250000 }
                        }

                        popup.onClosed: {
                            if(currentIndex!=-1){
                                root.node.baudrate=cbItems.get(currentIndex).value
                            }
                        }

                        delegate:ItemDelegate{
                            width: parent.width
                            text: textValue
                        }


                        textRole: "textValue"

                        currentIndex: -1

                        Component.onCompleted: {
                            var teste=root.node.baudrate
                            selectedBaudrate.currentIndex = selectedBaudrate.find(teste);
                        }
                    }


                }
            }


            Item{
                Layout.fillHeight: true;
                Layout.fillWidth: true;

                RowLayout{
                    anchors.fill: parent
                    TextField{

                        //                        Layout.fillHeight: true;
                        Layout.fillWidth: true;

                        text:node.prefix
                        MaterialPlaceHolder{

                            placeHolderText:"Prefix"

                        }
                        onTextChanged: {
                            node.prefix=text
                        }
                    }
                    TextField{

                        //                        Layout.fillHeight: true;
                        Layout.fillWidth: true;

                        text:node.suffix
                        MaterialPlaceHolder{

                            placeHolderText:"Suffix"

                        }
                        onTextChanged: {
                            node.suffix=text
                        }
                    }
                }


            }
            Item{
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                Button{
                    text: "Send data from input"
                    onClicked: {
                        root.node.doSend();
                    }
                }
            }

//            TextScroller {
//                id: rawLabel

//                Layout.fillHeight: true;
//                Layout.fillWidth: true;

//                text:root.node.rawdata
//                duration: 250
//                font.pixelSize: 20
//                horizontalAlignment:Text.AlignLeft




//            }

        }


    }

    onNodeConfigsLoadedChanged: {
        if(nodeConfigsLoaded){
            var ports=selectedPort.model
            var selectedport=node.port



            var index=ports.indexOf(selectedport);
            if(index>=0){
                selectedPort.currentIndex=index

            }


        }
    }



    SideContainerItem{

//        nodePressed: root.isPressed
        show: root.selected && editMode

        side: "left"

        containerSize: 250

        contentItem: GroupBox{
            anchors.fill: parent
            title: "Settings"
            anchors.margins: 10


            ColumnLayout{
                anchors.fill: parent

                TextField{
                    id:readycommand_lbl
                    Layout.fillWidth: true

                    text: root.node.readyCommand
                    onTextChanged: {
                        root.node.readyCommand=text
                    }


                    selectByMouse:true
                    MaterialPlaceHolder{

                        placeHolderText:"Command"
                    }
                }
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }

        }
    }

}

