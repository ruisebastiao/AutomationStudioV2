
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import visionmodule 1.0

PreProcessingItem{

    id:root


    property PreProcessingContours preProcessorContours: preProcessor


    containerItem: Column{

        id:container
        width: parent.width

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
                to:90000

                value: preProcessorContours.minCountourLength
                onValueChanged: {
                    if(preProcessorContours&&preProcessorContours.loaded){
                        preProcessorContours.minCountourLength=value
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
                to:90000
                Layout.fillWidth: true

                value: preProcessorContours.maxCountourLength
                onValueChanged: {
                    if(preProcessorContours && preProcessorContours.loaded ){
                        preProcessorContours.maxCountourLength=value
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
                to:90000

                value: preProcessorContours.minCountourArea
                onValueChanged: {
                    if(preProcessorContours&&preProcessorContours.loaded){
                        preProcessorContours.minCountourArea=value
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

                id:spin_maxContourArea
                editable: true
                to:90000
                Layout.fillWidth: true

                value: preProcessorContours.maxCountourArea
                onValueChanged: {
                    if(preProcessorContours && preProcessorContours.loaded ){
                        preProcessorContours.maxCountourArea=value
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
                to:90000
                Layout.fillWidth: true


                value:preProcessorContours.minCountourWidth
                onValueChanged: {
                    if(preProcessorContours && preProcessorContours.loaded){
                        preProcessorContours.minCountourWidth=value
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
                to:90000
                Layout.fillWidth: true


                value: preProcessorContours.maxCountourWidth
                onValueChanged: {
                    if(preProcessorContours && preProcessorContours.loaded){
                        preProcessorContours.maxCountourWidth=value
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
                to:90000
                Layout.fillWidth: true

                value:preProcessorContours.minCountourHeight
                onValueChanged: {
                    if(preProcessorContours && preProcessorContours.loaded){
                        preProcessorContours.minCountourHeight=value
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

                to:90000


                value:preProcessorContours.maxCountourHeight
                onValueChanged: {
                    if(preProcessorContours && preProcessorContours.loaded){
                        preProcessorContours.maxCountourHeight=value
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
