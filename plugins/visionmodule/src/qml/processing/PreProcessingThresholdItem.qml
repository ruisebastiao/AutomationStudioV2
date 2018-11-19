
import QtQuick              2.11
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import visionmodule 1.0

Item{

    id:root



    property ProcessingThresholdNode processorThreshold

    Column{

        id:container
        width: parent.width

        spacing: 5


        GroupBox{
            title: "Threshold Type:"
            width: parent.width
            //            height: 80
            spacing: 5
            Flow{
                anchors.fill: parent
                RadioButton{
                    checked:processorThreshold.thresholdType==PreProcessingThreshold.Simple
                    text: "Simple"
                    onCheckedChanged: {
                        adaptative_settings.visible=false;
                        processorThreshold.thresholdType=PreProcessingThreshold.Simple
                    }
                }
                RadioButton{
                    checked:processorThreshold.thresholdType==PreProcessingThreshold.AdaptativeGaussian
                    text: "Adaptative Gaussian"
                    onCheckedChanged: {
                        adaptative_settings.visible=true
                        processorThreshold.thresholdType=PreProcessingThreshold.AdaptativeGaussian
                    }
                }
                RadioButton{
                    checked:processorThreshold.thresholdType==PreProcessingThreshold.AdaptativeMean
                    text: "Adaptative Mean"
                    onCheckedChanged: {
                        adaptative_settings.visible=true
                        processorThreshold.thresholdType=PreProcessingThreshold.AdaptativeMean
                    }
                }

            }
        }

        GroupBox{
            width: parent.width
            title: "Threshold value"
            //            height: 80
            RowLayout{
                anchors.fill: parent

                Slider {
                    id: thresholdSlider
                    Layout.fillWidth: true

                    to: 255
                    from:0
                    stepSize: 1
                    value:processorThreshold.value
                    live: false
                    onValueChanged: {
                        thresholdSpin.value=value

                    }

                    wheelEnabled: true
                    onPositionChanged: {
                        thresholdSpin.value=valueAt(position)

                    }





                }





                SpinBox {
                    id:thresholdSpin
                    Layout.fillWidth: true

                    editable: true
                    from:0
                    to:255
                    onValueChanged: {
                        if(processorThreshold && processorThreshold.loaded){
                            processorThreshold.value=value
                        }
                    }



                }
            }
        }

        GroupBox{
            id:adaptative_settings

            width: parent.width
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
                        value: processorThreshold.adaptativeBlockSize
                        onValueChanged: {
                            if(processorThreshold && processorThreshold.loaded){
                                processorThreshold.adaptativeBlockSize=value
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
                        value: processorThreshold.adaptativeC
                        onValueChanged: {
                            if(processorThreshold && processorThreshold.loaded){
                                processorThreshold.adaptativeC=value
                            }
                        }
                    }
                }

            }
        }

        Item{
            //            color: "red"
            width: parent.width
            height: 30
        }
    }
}

