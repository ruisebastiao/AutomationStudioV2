
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import QuickQanava          2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0

ProcessingNodeItem{
    id:root
    expandOnEdit: true


    processingConfigItem: ColumnLayout{
        anchors.fill: parent
        GroupBox{
            title: "Geometric Function:"
            Layout.fillWidth: true
            spacing: 5
            Flow{
                anchors.fill: parent
                RadioButton{
                    text: "2PointLine"
                    checked: root.node.geometricType==ProcessingGeometricNode.Geometric2PointLine
                    onCheckedChanged: {
                        if(root.node.configsLoaded){
                            root.node.geometricType=ProcessingGeometricNode.Geometric2PointLine
                        }
                    }
                }
                RadioButton{
                    text: "LinePointLine"
                    checked: root.node.geometricType==ProcessingGeometricNode.GeometricLinePointLine
                    onCheckedChanged: {
                        if(root.node.configsLoaded){
                            root.node.geometricType=ProcessingGeometricNode.GeometricLinePointLine
                        }
                    }
                }

            }
        }


        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Component.onCompleted: {

        }

    }

}
