
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import guimodule 1.0

import automationmodule 1.0 as Module


FlowNodeItem{
    id:root


    expandOnEdit:false
    resizable: false
    serializedDims: false
    width: 250
    height: 150

    Connections{
        target:root.node

        onBindModuleProperty:{

            if(moduleProperty!=""){
                moduleObject[moduleProperty]=Qt.binding(function() {
                    return root.node.input;
                })
            }



        }
    }

    contentItem:  Rectangle{

        anchors.fill: parent
        ColumnLayout{
           anchors.fill: parent
            ComboBox{
                id:selectedPort
                Layout.fillWidth: true
                model: root.node.moduleProperties
                onModelChanged: {

                    var index=root.node.moduleProperties.indexOf(root.node.moduleProperty)
                    currentIndex=index
                }

                popup.onClosed: {
                    if(currentIndex!=-1 && currentIndex!=node.moduleProperties.indexOf(node.moduleProperty)){
                        node.moduleProperty=node.moduleProperties[currentIndex];
                    }
                }

                onCurrentIndexChanged: {
//                    console.log("currentIndex:"+currentIndex)

                }


                currentIndex: -1

                Component.onCompleted: {

                }
            }
            Item{
                Layout.fillHeight: true
                Layout.fillWidth: true

            }
        }

    }
}
