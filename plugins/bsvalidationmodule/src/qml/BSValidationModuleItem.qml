import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import automationmodule 1.0

import bsvalidationmodule 1.0
import guimodule 1.0

BSValidationModule {
    id:bsvalidationmodule
    anchors.fill: parent

    //property FlowNode name: value

    ListModel {
        id: modulesContainer
    }

    onNodeAdded: {

        if(node){
            if(node.type===FlowNode.Type.BSValidationVisualNode){
                modulesContainer.append(
                            {
                                flownode:node
                            }
                            )
            }


        }
    }

    RowLayout{
        parent:moduleitem.mainpagecontainer
        anchors.fill: parent
        anchors.margins: 5
        Repeater{
            model: modulesContainer
            Button{
                enabled: true
                id:visualitem
                property color currentcolor: Material.primary
                Material.background:  currentcolor

                Layout.fillHeight: true
                Layout.fillWidth: true
                Component.onCompleted: {
                    visualitem.currentcolor=Qt.binding(function() {
                        if(modelData.WaitResults){
                                    return Material.color(Material.Orange);
                        }
                        if(modelData.BSOK){
                                    return Material.color(Material.Green);
                        }
                        if(modelData.BSNOK){
                                    return Material.color(Material.Red,Material.Shade400);
                        }
                        return "white"
                    })

                }

                ColumnLayout{
                    spacing: 10
                    visible: true
                    anchors.fill: parent
                    Item{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
//
                      TextScroller{
                        Layout.fillWidth: true;
                        horizontalAlignment: Text.AlignHCenter
                        Layout.preferredHeight: textHeight
                        font.pixelSize: 40

//                        color: visualitem.color=="white"?"black":"white"
                        text: modelData.Status
                    }
                    TextScroller{
                        id:serialnumber
                        Layout.fillWidth: true;
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 40
                        Layout.preferredHeight: textHeight
//                        color: visualitem.color=="white"?"black":"white"
                        text: modelData.serialnumber
                    }

                    TextScroller{
                        visible: serialnumber.text!=""
                        Layout.fillWidth: true;
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 40
                        Layout.preferredHeight: textHeight
                        text: modelData.BSInfo
                    }

                    Item{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }





    onConfigSourceChanged:{

        bsvalidationmodule.load(appDir+configSource);
    }

    AutomationModuleItem{
        id:moduleitem
        anchors.fill: parent
        loadedmodule: parent


    }

}
