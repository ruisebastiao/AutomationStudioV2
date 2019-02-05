
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0 as GUI

import QuickQanava          2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0

ProcessingNodeItem{
    id:root
    expandOnEdit: true


    processingConfigItem: ColumnLayout{
        anchors.fill: parent
        GroupBox{
            title: "Enclosing Type:"
            Layout.fillWidth: true
            spacing: 5
            Flow{
                anchors.fill: parent
                RadioButton{
                    checked:root.node.configsLoaded && root.node.enclosingType==ProcessingEnclosingNode.RotatedRectEnclosing
                    text: "Minimum Enclosing Rectangle"
                    onCheckedChanged: {
                        root.node.enclosingType=ProcessingEnclosingNode.RotatedRectEnclosing
                    }
                }
                RadioButton{
                    checked:root.node.configsLoaded && root.node.enclosingType==ProcessingEnclosingNode.BoundingRectEnclosing
                    text: "Bounding Rectangle"
                    onCheckedChanged: {
                        root.node.enclosingType=ProcessingEnclosingNode.BoundingRectEnclosing
                    }
                }





            }
        }

        GroupBox{
            title: "Shape ratio:"
            Layout.fillWidth: true
            spacing: 5
            Flow{
                anchors.fill: parent
                TextField{


                    text: root.node.minRatio
                    onTextChanged: {
                        root.node.minRatio=parseFloat(value)
                    }

                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    selectByMouse:true
                    GUI.MaterialPlaceHolder{

                        placeHolderText:"Min ratio"
                    }

                }
                TextField{


                    text: root.node.maxRatio
                    onTextChanged: {
                        root.node.maxRatio=parseFloat(value)
                    }

                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    selectByMouse:true
                    GUI.MaterialPlaceHolder{

                        placeHolderText:"Max ratio"
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
