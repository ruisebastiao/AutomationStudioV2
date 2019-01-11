
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import guimodule 1.0 as GUI

import automationmodule 1.0



FlowNodeItem{
    id:root
    expandOnEdit: true

    resizable: true
    GUI.SideContainerItem{

//        nodePressed: root.isPressed
        show: root.selected && editMode

        side: "left"

        containerSize: 250

        contentItem: GroupBox{
            anchors.fill: parent
            title: "Settings"
            anchors.margins: 10
            MouseArea{
                anchors.fill: parent


                onPressed: {
                    mouse.accepted=true

                }
            }

            ColumnLayout{
                anchors.fill: parent

                CheckBox{
                    checked: root.node.processOnInput
                    text: "Process on Input"
                    onCheckedChanged: {
                        root.node.processOnInput=checked
                    }
                }

//                Item{
//                    Layout.fillHeight: true
//                    Layout.fillWidth: true
//                }
            }

        }
    }

}
