
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
            title: "Filter Type:"
            Layout.fillWidth: true
            spacing: 5
            Flow{
                anchors.fill: parent
                RadioButton{
//                    checked:root.node.configsLoaded && root.node.thresholdType==ProcessingThresholdNode.Simple
                    text: "Average"
                    onCheckedChanged: {
//                        adaptative_settings.visible=false;
//                        root.node.thresholdType=ProcessingThresholdNode.Simple
                    }
                }
                RadioButton{
//                    checked:root.node.configsLoaded && root.node.thresholdType==ProcessingThresholdNode.AdaptativeGaussian
                    text: "Gaussian"
//                    onCheckedChanged: {
//                        adaptative_settings.visible=true
//                        root.node.thresholdType=ProcessingThresholdNode.AdaptativeGaussian
//                    }
                }
                RadioButton{
//                    checked:root.node.configsLoaded && root.node.thresholdType==ProcessingThresholdNode.AdaptativeMean
                    text: "Median"
                    onCheckedChanged: {
//                        adaptative_settings.visible=true
//                        root.node.thresholdType=ProcessingThresholdNode.AdaptativeMean
                    }
                }

                RadioButton{
//                    checked:root.node.configsLoaded && root.node.thresholdType==ProcessingThresholdNode.AdaptativeMean
                    text: "Bilateral"
                    onCheckedChanged: {
//                        adaptative_settings.visible=true
//                        root.node.thresholdType=ProcessingThresholdNode.AdaptativeMean
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
