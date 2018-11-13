
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import visionmodule 1.0

PreProcessingItem{

    id:root


    //    property int thresholdValue:0

    //    headerText:preProcessor?preProcessor.name+" ("+thresholdValue+") ":"Threshold"

    //    Binding{
    //        target:root
    //        property: "thresholdValue"
    //        value: preProcessor.value
    //    }


    containerItem: ColumnLayout{

        width: parent.width
        height: 450

        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            Row{
                anchors.fill: parent
                Label{
                    text: "Min Countour Length:"
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_minContourLength
                    editable: true
                    from:0
                    height: parent.height
                    to:spin_maxContourLength.value
                    value: preProcessor&&preProcessor.loadeded?preProcessor.minCountourLength:0
                    onValueChanged: {
                        if(preProcessor){
                            preProcessor.minCountourLength=value
                        }
                    }
                }
            }
        }
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            Row{
                anchors.fill: parent
                Label{
                    text: "Max Countour Length:"
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_maxContourLength
                    editable: true
                    from:spin_minContourLength.value
                    height: parent.height
                    to:20000
                    value: preProcessor.maxCountourLength
                    onValueChanged: {
                        if(preProcessor){
                            preProcessor.maxCountourLength=value
                        }
                    }
                }
            }
        }


        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            Row{
                anchors.fill: parent
                Label{
                    text: "Min Countour Width:"
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_minContourWidth
                    editable: true
                    from:0
                    height: parent.height
                    to:spin_maxContourWidth.value
                    value: preProcessor&&preProcessor.loadeded?preProcessor.minCountourWidth:0
                    onValueChanged: {
                        if(preProcessor){
                            preProcessor.minCountourWidth=value
                        }
                    }
                }
            }
        }
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            Row{
                anchors.fill: parent
                Label{
                    text: "Max Countour Width:"
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_maxContourWidth
                    editable: true
                    from:spin_minContourWidth.value
                    height: parent.height
                    to:50000
                    value: preProcessor&&preProcessor.loadeded?preProcessor.maxCountourWidth:0
                    onValueChanged: {
                        if(preProcessor){
                            preProcessor.maxCountourWidth=value
                        }
                    }
                }
            }
        }



        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            Row{
                anchors.fill: parent
                Label{
                    text: "Min Countour Height:"
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_minContourHeight
                    editable: true
                    from:0
                    height: parent.height
                    to:spin_maxContourHeight.value
                    value:preProcessor&&preProcessor.loadeded?preProcessor.minCountourHeight:0
                    onValueChanged: {
                        if(preProcessor){
                            preProcessor.minCountourHeight=value
                        }
                    }
                }
            }
        }
        Item{
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            Row{
                anchors.fill: parent
                Label{
                    text: "Max Countour Height:"
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_maxContourHeight
                    editable: true
                    from:spin_minContourHeight.value
                    height: parent.height
                    to:40000
                    value: preProcessor&&preProcessor.loadeded?preProcessor.maxCountourHeight:0
                    onValueChanged: {
                        if(preProcessor){
                            preProcessor.maxCountourHeight=value
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
