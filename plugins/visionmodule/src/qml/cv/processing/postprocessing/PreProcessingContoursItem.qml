
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import visionmodule 1.0

ProcessingItem{

    id:root


    property PostProcessingContours postProcessorContours: processor


    containerItem: ColumnLayout{
        width: parent.width


        Column{
            id:container
            Layout.fillWidth: true




            spacing: 5



            RowLayout{
                width: parent.width
                Label{
                    text: "Min Countour Length:"
                    Layout.preferredWidth: paintedWidth
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_minContourLength
                    Layout.fillWidth: true
                    editable: true
                    to:900000

                    value: postProcessorContours.minCountourLength
                    onValueChanged: {
                        if(postProcessorContours&&postProcessorContours.loaded){
                            postProcessorContours.minCountourLength=value
                        }
                    }
                }
            }

            RowLayout{
                width: parent.width
                Label{
                    text: "Max Countour Length:"
                    Layout.preferredWidth: paintedWidth

                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {

                    id:spin_maxContourLength
                    editable: true
                    to:9000000
                    Layout.fillWidth: true

                    value: postProcessorContours.maxCountourLength
                    onValueChanged: {
                        if(postProcessorContours && postProcessorContours.loaded ){
                            postProcessorContours.maxCountourLength=value
                        }
                    }
                }
            }

            RowLayout{
                width: parent.width
                Label{
                    text: "Min Countour Area:"
                    Layout.preferredWidth: paintedWidth
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_minContourArea
                    Layout.fillWidth: true
                    editable: true
                    to:9000000

                    value: postProcessorContours.minCountourArea
                    onValueChanged: {
                        if(postProcessorContours&&postProcessorContours.loaded){
                            postProcessorContours.minCountourArea=value
                        }
                    }
                }
            }

            RowLayout{
                width: parent.width
                Label{
                    text: "Max Countour Area:"
                    Layout.preferredWidth: paintedWidth

                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    inputMethodHints: Qt.ImhDigitsOnly
                    id:spin_maxContourArea
                    editable: true
                    stepSize: 1

                    to:9000000
                    Layout.fillWidth: true

                    value: postProcessorContours.maxCountourArea
                    onValueChanged: {
                        if(postProcessorContours && postProcessorContours.loaded ){
                            postProcessorContours.maxCountourArea=value
                        }
                    }
                }
            }


            RowLayout{
                width: parent.width

                Label{
                    text: "Min Countour Width:"
                    Layout.preferredWidth: paintedWidth
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_minContourWidth
                    editable: true
                    to:9000000
                    Layout.fillWidth: true


                    value:postProcessorContours.minCountourWidth
                    onValueChanged: {
                        if(postProcessorContours && postProcessorContours.loaded){
                            postProcessorContours.minCountourWidth=value
                        }
                    }
                }
            }



            RowLayout{
                width: parent.width
                Label{
                    text: "Max Countour Width:"
                    Layout.preferredWidth: paintedWidth
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_maxContourWidth
                    editable: true
                    to:9000000
                    Layout.fillWidth: true


                    value: postProcessorContours.maxCountourWidth
                    onValueChanged: {
                        if(postProcessorContours && postProcessorContours.loaded){
                            postProcessorContours.maxCountourWidth=value
                        }
                    }
                }
            }

            RowLayout{
                width: parent.width
                Label{
                    text: "Min Countour Height:"
                    Layout.preferredWidth: paintedWidth
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_minContourHeight
                    editable: true
                    to:9000000
                    Layout.fillWidth: true

                    value:postProcessorContours.minCountourHeight
                    onValueChanged: {
                        if(postProcessorContours && postProcessorContours.loaded){
                            postProcessorContours.minCountourHeight=value
                        }
                    }
                }
            }

            RowLayout{
                width: parent.width
                Label{
                    text: "Max Countour Height:"
                    Layout.preferredWidth: paintedWidth
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    Layout.fillWidth: true
                    id:spin_maxContourHeight
                    editable: true

                    to:9000000


                    value:postProcessorContours.maxCountourHeight
                    onValueChanged: {
                        if(postProcessorContours && postProcessorContours.loaded){
                            postProcessorContours.maxCountourHeight=value
                        }
                    }
                }
            }

            GroupBox{
                visible: true

                width: parent.width

                title: "Results:"
                ColumnLayout{
                    width: parent.width
                    Rectangle{
                        color: "red"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 150
                    }
                }
            }

        }

        Item{
            width: parent.width
            height: 30
        }
    }
}



