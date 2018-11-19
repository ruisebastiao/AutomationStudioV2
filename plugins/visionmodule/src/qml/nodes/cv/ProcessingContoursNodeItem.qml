
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

                    value: root.node.minCountourLength
                    onValueChanged: {
                        if(root.node&&root.node.configsLoaded){
                            root.node.minCountourLength=value
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

                    value: root.node.maxCountourLength
                    onValueChanged: {
                        if(root.node && root.node.configsLoaded ){
                            root.node.maxCountourLength=value
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

                    value: root.node.minCountourArea
                    onValueChanged: {
                        if(root.node&&root.node.configsLoaded){
                            root.node.minCountourArea=value
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

                    value: root.node.maxCountourArea
                    onValueChanged: {
                        if(root.node && root.node.configsLoaded ){
                            root.node.maxCountourArea=value
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


                    value:root.node.minCountourWidth
                    onValueChanged: {
                        if(root.node && root.node.configsLoaded){
                            root.node.minCountourWidth=value
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


                    value: root.node.maxCountourWidth
                    onValueChanged: {
                        if(root.node && root.node.configsLoaded){
                            root.node.maxCountourWidth=value
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

                    value:root.node.minCountourHeight
                    onValueChanged: {
                        if(root.node && root.node.configsLoaded){
                            root.node.minCountourHeight=value
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


                    value:root.node.maxCountourHeight
                    onValueChanged: {
                        if(root.node && root.node.configsLoaded){
                            root.node.maxCountourHeight=value
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
//                        color: "red"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 150
                    }
                }
            }

        }


    }

}
