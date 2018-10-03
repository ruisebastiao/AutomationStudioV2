
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

    Binding{
        when: thresholdLowSlider.pressed==false && root.node.configsLoaded
        target:thresholdLowSlider
        property: "value"
        value: thresholdLowSpin.value

    }



    preProcessingConfigItem: ColumnLayout{
        anchors.fill: parent

        GroupBox{
            //enabled: root.node.processing==false
            //            anchors.fill: parent
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            title: "Low Threshold Value"
            RowLayout{
                anchors.fill: parent

                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Slider {
                        id: thresholdLowSlider
                        anchors.fill: parent
                        to: 255
                        from:0
                        stepSize: 1
                        value: root.node.thresholdlow
                        live: false
                        onValueChanged: {
                            root.node.thresholdlow=value
                            thresholdLowSpin.value=value
                            if(root.node.configsLoaded){
                                root.node.reProcess();
                            }
                        }

                        wheelEnabled: true
                        onPositionChanged: {
                            thresholdLowSpin.value=valueAt(position)
                        }



                    }

                }
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    SpinBox {
                        id:thresholdLowSpin
                        anchors.fill: parent
                        editable: true
                        from:0
                        to:255

                    }
                }



            }

        }

        GroupBox{
            //enabled: root.node.processing==false
            //            anchors.fill: parent
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            title: "High Threshold Value"
            RowLayout{
                anchors.fill: parent

                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Slider {
                        id: thresholdHighSlider
                        anchors.fill: parent
                        to: 255
                        from:0
                        stepSize: 1
                        value: root.node.thresholdhigh
                        live: false
                        onValueChanged: {
                            root.node.thresholdhigh=value
                            thresholdHighSpin.value=value
                            if(root.node.configsLoaded){
                                root.node.reProcess();
                            }
                        }

                        wheelEnabled: true
                        onPositionChanged: {
                            thresholdHighSpin.value=valueAt(position)
                        }





                    }
                }
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    SpinBox {
                        id:thresholdHighSpin
                        anchors.fill: parent
                        editable: true
                        from:0
                        to:255

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
