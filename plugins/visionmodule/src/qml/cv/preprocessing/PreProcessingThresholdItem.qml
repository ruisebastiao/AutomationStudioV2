
import QtQuick              2.11
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import visionmodule 1.0

PreProcessingItem{

    id:root
    headerText:preProcessor?preProcessor.name+" ("+preProcessor.value+") ":"Threshold"

    property PreProcessingThreshold preProcessorThreshold: preProcessor

    onPreProcessorThresholdChanged: {
        if(preProcessorThreshold){
            console.log("preProcessorThreshold:"+preProcessorThreshold.value)
        }
    }


    containerItem: Column{

        id:container
        width: parent.width

        spacing: 5


        GroupBox{
            title: "Threshold Type:"
            width: parent.width
//            height: 80
            RowLayout{
                anchors.fill: parent
                RadioButton{
                    checked:preProcessor.thresholdType==PreProcessingThreshold.Simple
                    text: "Simple"
                    onCheckedChanged: {
                        preProcessor.thresholdType=PreProcessingThreshold.Simple
                    }
                }
                RadioButton{
                    checked:preProcessor.thresholdType==PreProcessingThreshold.Adaptative
                    text: "Adaptative"
                    onCheckedChanged: {
                        preProcessor.thresholdType=PreProcessingThreshold.Adaptative
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
                    value:preProcessorThreshold.value
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
                        if(preProcessorThreshold){
                            preProcessorThreshold.value=value
                        }
                    }



                }
            }
        }

        GroupBox{
            width: parent.width
            title: "Adaptative settings"

//            height: 150
            RowLayout{
                anchors.fill: parent


                Label{
                    Layout.fillWidth: true
                    text:"Adaptative Block Size"
                }

                SpinBox {
                    Layout.fillWidth: true
                    Layout.preferredWidth: childrenRect.width
                    editable: true
                    from:3
                    to:201
                    stepSize: 2
                    value: preProcessorThreshold.adaptativeBlockSize
                    onValueChanged: {
                        if(preProcessor && preProcessorThreshold.loadeded){
                            preProcessorThreshold.adaptativeBlockSize=value
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


