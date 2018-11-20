
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
            title: "Threshold Type:"
            Layout.fillWidth: true
            spacing: 5
            Flow{
                anchors.fill: parent
                RadioButton{
                    checked:root.node.configsLoaded && root.node.thresholdType==ProcessingThresholdNode.Simple
                    text: "Simple"
                    onCheckedChanged: {
                        adaptative_settings.visible=false;
                        root.node.thresholdType=ProcessingThresholdNode.Simple
                    }
                }
                RadioButton{
                    checked:root.node.configsLoaded && root.node.thresholdType==ProcessingThresholdNode.AdaptativeGaussian
                    text: "Adaptative Gaussian"
                    onCheckedChanged: {
                        adaptative_settings.visible=true
                        root.node.thresholdType=ProcessingThresholdNode.AdaptativeGaussian
                    }
                }
                RadioButton{
                    checked:root.node.configsLoaded && root.node.thresholdType==ProcessingThresholdNode.AdaptativeMean
                    text: "Adaptative Mean"
                    onCheckedChanged: {
                        adaptative_settings.visible=true
                        root.node.thresholdType=ProcessingThresholdNode.AdaptativeMean
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
