
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
            height: 80
            title: "Edit Value"
            RowLayout{
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
                    Layout.fillWidth: true
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

    }

}
