
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

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

    }
}
