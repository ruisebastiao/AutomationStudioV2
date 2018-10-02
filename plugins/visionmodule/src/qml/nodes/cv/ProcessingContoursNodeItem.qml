
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0
import com.novares.cv 1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import com.novares.flow.nodes 1.0
import com.novares.utilities 1.0

import QuickQanava          2.0 as Qan
import "qrc:/QuickQanava"   as Qan

import "../"

ProcessingNode{
    id:root

    expandOnEdit: true


    preProcessingConfigItem: ColumnLayout{
        anchors.fill: parent


        GroupBox{
            //            anchors.fill: parent
            Layout.minimumWidth: 100
            Layout.preferredHeight: 60
            Layout.fillWidth: true
            title: "Min contour length"

            SpinBox {
                anchors.centerIn: parent
                editable: true
                from:0
                to:2000
                value: root.node.minCountourLength
                onValueChanged: {
                    root.node.minCountourLength=value
                    if(root.node.configsLoaded){
                        root.node.reProcess();
                    }
                }
            }
        }
        GroupBox{
            //            anchors.fill: parent
            Layout.preferredHeight: 60
            Layout.fillWidth: true
            title: "Max contour length"
            Layout.minimumWidth: 100
            SpinBox {
                anchors.centerIn: parent
                editable: true
                from:0
                to:2000
                value: root.node.maxCountourLength
                onValueChanged: {
                    root.node.maxCountourLength=value
                    if(root.node.configsLoaded){
                        root.node.reProcess();
                    }
                }
            }
        }
        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

    }



    postProcessingConfigItem: ColumnLayout{
        anchors.fill: parent


        Item{
            Layout.preferredHeight: 60
            Layout.fillWidth: true


            RowLayout{
                anchors.fill: parent

                GroupBox{
                    //            anchors.fill: parent
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    title: "Total contours"
                    font.pixelSize: 12
                    Text {

                        anchors.centerIn: parent
                        text: root.node.totalContours
                    }
                }
                GroupBox{
                    //            anchors.fill: parent
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    title: "Filtered contours"
                    font.pixelSize: 12
                    Text {
                        anchors.centerIn: parent
                        text: root.node.totalFilteredContours
                    }
                }
            }

        }

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
//            Component {
//                   id: contourDelegate
//                   Row {
//                       spacing: 10
//                       Text { text: contourIndex }
//                   }
//               }


//            ListView {
//                anchors.fill: parent
//                model: filteredcontoursModel
//                delegate: contourDelegate
//            }
        }
    }

//    ListModel{
//        id:filteredcontoursModel

//        Repeater{
//            model:root.node.totalFilteredContours
//            ListElement { contourIndex: index }
//        }
//    }
}

