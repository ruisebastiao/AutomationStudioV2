
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0

import com.novares.cv 1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import com.novares.flow.nodes 1.0
import com.novares.utilities 1.0

import QuickQanava          2.0 as Qan
import "qrc:/QuickQanava"   as Qan

import "../"

ProcessingNode{
    id:root
    expandOnEdit: true


    preProcessingConfigItem: ColumnLayout{
        anchors.fill: parent

        GroupBox{
            //enabled: root.node.processing==false
            //            anchors.fill: parent
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            title: "Threshold Value"
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
                        value:root.node.value
                        live: false
                        onValueChanged: {
                            root.node.value=value
                            thresholdSpin.value=value
                            if(root.node.configsLoaded){
                                root.node.reProcess();
                            }
                        }

                        wheelEnabled: true
                        onPositionChanged: {
                            thresholdSpin.value=valueAt(position)
                        }





                    }

                }
                Binding{
                    when: thresholdSlider.pressed==false && root.node.configsLoaded
                    target:thresholdSlider
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
                        //value: thresholdSlider.value
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
        }

    }

}
