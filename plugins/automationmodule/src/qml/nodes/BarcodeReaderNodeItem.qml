
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






    //    Connections{
    //        target:node

    //        onTriggerEnabledChanged:{
    //            node.inPortState('trigger',triggerEnabled);
    //        }
    //    }

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
                        id:trigger_switch


                        //                    anchors.centerIn: parent
                        text:"External Trigger"
                        checked: node.triggerEnabled
                        onCheckedChanged: {
                            node.triggerEnabled=checked;
                        }


                        contentItem: Label{
                            id:switch_label
                            height: trigger_switch.indicator.height
                            verticalAlignment: Text.AlignVCenter
                            minimumPixelSize: 8;
                            font.pixelSize: 12
                            fontSizeMode:Text.HorizontalFit
                            text:trigger_switch.text
                            leftPadding: trigger_switch.indicator.width + trigger_switch.spacing
                        }
                    }
                    Switch{
                        id:connectonopen


                        //                    anchors.centerIn: parent
                        text:"Open On Connect"
                        checked: node.openOnConnect
                        onCheckedChanged: {
                            node.openOnConnect=checked;
                        }


                        contentItem: Label{
                            id:connectonopen_label
                            height: connectonopen.indicator.height
                            verticalAlignment: Text.AlignVCenter
                            minimumPixelSize: 8;
                            font.pixelSize: 12
                            fontSizeMode:Text.HorizontalFit
                            text:connectonopen.text
                            leftPadding: connectonopen.indicator.width + connectonopen.spacing
                        }
                    }
                }


                RowLayout{
                    Layout.preferredHeight: 42
                    Layout.fillWidth: true

                    Label{
                        text:"Port: "
                    }

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
        }


    }

    onNodeConfigsLoadedChanged: {
        if(nodeConfigsLoaded){
            var ports=selectedPort.model
            var selectedport=node.port

            //var index=ports.indexOf("/dev/"+selectedport)


            var index=ports.indexOf(selectedport);
            if(index>=0){
                selectedPort.currentIndex=index

            }


        }
    }


}

