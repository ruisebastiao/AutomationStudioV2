
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import guimodule 1.0


import QuickQanava          2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0

ProcessingNodeItem{
    id:root
    expandOnEdit: true


    processingConfigItem: ColumnLayout{
        anchors.fill: parent
        GroupBox{
            title: "Mask Type:"
            Layout.fillWidth: true
            spacing: 5
            Flow{
                anchors.fill: parent
                RadioButton{
                    checked:root.node.configsLoaded && root.node.maskType==ProcessingMaskNode.MaskCircleRadius
                    text: "From Circle & Radius"
                    onCheckedChanged: {
                        if(checked){
                            root.node.maskType==ProcessingMaskNode.MaskCircleRadius
                        }
                    }
                }


            }
        }
        GroupBox{
            title: "Settings:"
            Layout.fillWidth: true
            spacing: 5


            property bool portsInited: root.node.portsInitialized;

            onPortsInitedChanged: {
                console.log("ports inited:"+portsInited)
                var port=root.node.getPortFromKey("input1")
                port1_container.port=port
                port=root.node.getPortFromKey("input2")
                port2_container.port=port
                port=root.node.getPortFromKey("input3")
                port3_container.port=port


            }

            Flow{
                anchors.fill: parent

//                TextField{
//                    id:port1_container
//                    property var port;
//                    Layout.fillWidth: true
//                    text:root.node.input1
//                    onTextChanged: {
//                        if(root.node.input1!=text){
//                            root.node.input1=text
//                        }

//                    }

//                    selectByMouse:true
//                    MaterialPlaceHolder{

//                        placeHolderText:port1_container.port?port1_container.port.portLabel:"?"
//                    }
//                }
                TextField{
                    id:port2_container
                    property var port;
                    Layout.fillWidth: true
                    text:root.node.input2
                    onTextChanged: {
                        if(root.node.input2!=text){
                            root.node.input2=text
                        }


                    }

                    selectByMouse:true
                    MaterialPlaceHolder{

                        placeHolderText:port2_container.port?port2_container.port.portLabel:"?"
                    }
                }
                TextField{
                    id:port3_container
                    property var port;
                    Layout.fillWidth: true
                    text:root.node.input3
                    onTextChanged: {
                        if(root.node.input3!=text){
                            root.node.input3=text
                        }


                    }

                    selectByMouse:true
                    MaterialPlaceHolder{

                        placeHolderText:port3_container.port?port3_container.port.portLabel:"?"
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
