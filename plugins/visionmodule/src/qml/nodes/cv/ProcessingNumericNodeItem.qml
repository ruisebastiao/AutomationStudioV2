
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



    contentItem: ColumnLayout{
        anchors.fill: parent
        GroupBox{
            title: "Value:"
            Layout.fillWidth: true
            spacing: 5
            SpinBox{
                id:spin_value
                editable: true
                to:90000000
                enabled: root.node.editMode
                stepSize: 1
                value:root.node.numericValue
                onValueChanged: {
                    if(root.node.configsLoaded){
                        root.node.numericValue=value
                    }
                }
            }

            //            TextInput{
            //                readOnly: root.node.editMode
            //                inputMethodHints:Qt.ImhFormattedNumbersOnly
            //                onAccepted: {
            //                    root.node.value=
            //                }

            //                width: parent.width
            //            }
        }
        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

    }

}
