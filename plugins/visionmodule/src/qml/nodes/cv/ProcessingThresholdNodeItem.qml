
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

        GroupBox{
            Layout.fillWidth: true
            title: "Threshold value"

            RowLayout{
                anchors.fill: parent

                Slider {
                    id: thresholdSlider
                    Layout.fillWidth: true

                    to: 255
                    from:0
                    stepSize: 1
                    value:root.node.value
                    live: false
                    onValueChanged: {
                        thresholdSpin.value=value

                    }

                    wheelEnabled: true
//                    onPositionChanged: {
//                        thresholdSpin.value=valueAt(position)

//                    }





                }





                SpinBox {
                    id:thresholdSpin
                    Layout.fillWidth: true

                    editable: true
                    from:0
                    to:255
                    onValueChanged: {
                        if(root.node && root.node.configsLoaded){
                            root.node.value=value
                        }
                    }



                }
            }
        }

        GroupBox{
            id:adaptative_settings

            Layout.fillWidth: true
            title: "Adaptative settings"


            Flow{
                anchors.fill: parent

                RowLayout{
                    width: parent.width
                    Label{
                        Layout.preferredWidth: paintedWidth
                        text:"Adaptative Block Size"
                    }

                    SpinBox {
                        Layout.fillWidth: true
                        editable: true
                        from:3
                        to:701
                        stepSize: 2
                        value: root.node.adaptativeBlockSize
                        onValueChanged: {
                            if(root.node && root.node.configsLoaded){
                                root.node.adaptativeBlockSize=value
                            }
                        }
                    }
                }
                RowLayout{
                    width: parent.width
                    Label{
                        Layout.preferredWidth: paintedWidth
                        text:"Adaptative C factor"
                    }

                    SpinBox {
                        Layout.fillWidth: true
                        editable: true
                        from:2
                        to:200
                        stepSize: 2
                        value: root.node.adaptativeC
                        onValueChanged: {
                            if(root.node && root.node.configsLoaded){
                                root.node.adaptativeC=value
                            }
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
