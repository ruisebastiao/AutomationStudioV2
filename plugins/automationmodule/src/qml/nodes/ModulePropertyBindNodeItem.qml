
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


        onConfigsLoadedChanged:{
            console.log("root.node.moduleProperty:"+root.node.moduleProperty)
            var index=root.node.moduleProperties.indexOf(root.node.moduleProperty)
            selectedProperty.currentIndex=index
        }

//        onBindModuleProperty:{

//            if(moduleProperty!=""){
//                moduleObject[moduleProperty]=Qt.binding(function() {
//                    return root.node.input;
//                })

//                root.node.output=Qt.binding(function() {
//                    return moduleObject[moduleProperty];
//                })
//            }



//        }
    }

    contentItem:  Rectangle{

        anchors.fill: parent
        ColumnLayout{
           anchors.fill: parent
            ComboBox{
                id:selectedProperty
                Layout.fillWidth: true
                model: root.node.moduleProperties
                onModelChanged: {


                    var index=root.node.moduleProperties.indexOf(root.node.moduleProperty)
                    currentIndex=index
                }

                popup.onClosed: {
                    if(currentIndex!=-1 && currentIndex!=node.moduleProperties.indexOf(root.node.moduleProperty)){
                        root.node.moduleProperty=root.node.moduleProperties[currentIndex];
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
