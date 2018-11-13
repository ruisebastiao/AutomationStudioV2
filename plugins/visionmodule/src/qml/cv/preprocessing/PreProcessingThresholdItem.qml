
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import visionmodule 1.0

PreProcessingItem{

    id:root


    property int thresholdValue:0

    headerText:preProcessor?preProcessor.name+" ("+thresholdValue+") ":"Threshold"

//    onPreProcessorChanged:{
//        console.log("preProcessor:"+preProcessor.thresholdType)

//    }

    Binding{
        target:root
        property: "thresholdValue"
        value: preProcessor.value
    }


    containerItem:Item{


        width: parent.width



        GroupBox{
            visible: true

            width: parent.width
            height: 300
            title: "Settings:"
            ColumnLayout{
                anchors.fill: parent
                GroupBox{
                    Layout.preferredHeight: 100
                    Layout.fillWidth: true
                    title: "Threshold Type:"
                    RowLayout{
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

                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    RowLayout{
                        id:content
                        anchors.fill: parent
                        Item{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            Slider {
                                id: thresholdSlider
                                anchors.fill: parent
                                to: 255
                                from:0
                                stepSize: 1
                                value:root.thresholdValue
                                live: false
                                onValueChanged: {
                                    //                            root.preProcessor.value=value

                                    thresholdSpin.value=value
                                    //                            if(root.preProcessor.configsLoaded){
                                    //                                root.node.reProcess();
                                    //                            }
                                }

                                wheelEnabled: true
                                onPositionChanged: {
                                    thresholdSpin.value=valueAt(position)

                                }





                            }

                        }
                        Binding{
                            when: thresholdSlider.pressed==false
                            target:preProcessor
                            property: "value"
                            value: thresholdSpin.value

                        }

                        Item{
                            Layout.fillHeight: true
//                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            SpinBox {
                                id:thresholdSpin
                                anchors.fill: parent
                                editable: true
                                from:0
                                to:255
                                value: root.thresholdValue
                                //                        onValueChanged: {
                                //                            thresholdSlider.value=value
                                //                        }

                            }
                        }



                    }
                }
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    SpinBox {

                        anchors.fill: parent
                        editable: true
                        from:3
                        to:101
                        stepSize: 2
                        value: preProcessor.adaptativeBlockSize
                        onValueChanged: {
                            if(preProcessor){
                                preProcessor.adaptativeBlockSize=value
                            }
                        }


                    }
                }
            }
        }

    }

}
