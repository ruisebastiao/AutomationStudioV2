
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0

import automationmodule 1.0 as Module

FlowNodeItem{
    id:root


    resizable:true;
    expandOnEdit:true;



    Connections{
        target:root.node


        onConfigsLoadedChanged:{
            console.log("root.node.projectProperty:"+root.node.projectProperty)
            var index=root.node.projectProperties.indexOf(root.node.projectProperty)
            selectedProperty.currentIndex=index
        }

        onBindProjectProperty:{

            if(projectProperty!=""){
                projectObject[projectProperty]=Qt.binding(function() {
                    if(typeof root.node.input === 'undefined'){
                        return "";
                    }

                    return root.node.input;
                })

                root.node.output=Qt.binding(function() {
                    return projectObject[projectProperty];
                })
            }



        }
    }

    contentItem:  Rectangle{

        anchors.fill: parent
        ColumnLayout{
           anchors.fill: parent
            ComboBox{
                id:selectedProperty
                Layout.fillWidth: true
                model: root.node.projectProperties
                onModelChanged: {


                    var index=root.node.projectProperties.indexOf(root.node.projectProperty)
                    currentIndex=index
                }

                popup.onClosed: {
                    if(currentIndex!=-1 && currentIndex!=node.projectProperties.indexOf(root.node.projectProperty)){
                        root.node.projectProperty=root.node.projectProperties[currentIndex];
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
