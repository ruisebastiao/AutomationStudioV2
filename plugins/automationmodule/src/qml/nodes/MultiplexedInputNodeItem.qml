import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import QtQuick.Layouts 1.3


import guimodule 1.0 as GUI

import automationmodule 1.0


FlowNodeItem{

    id:root


    expandOnEdit: false


    resizable:true;

    contentItem:  ColumnLayout{
        anchors.fill: parent
        GroupBox{

            Layout.fillHeight: true
            Layout.fillWidth: true


            Flow{
                clip: true
                anchors.fill: parent
                GUI.ReadOnlyItem{
                    readOnly:true
                    RadioButton{
                        checked: root.node.in1Enabled
                        text: "In 1"
                        autoExclusive: false
                    }
                }
                GUI.ReadOnlyItem{
                    readOnly:true
                    RadioButton{
                        checked: root.node.in2Enabled
                        text: "In 2"
                        autoExclusive: false
                    }
                }
                CheckBox{
                    text: "Exclusive"
                    checked: root.node.autoExclusive
                    onCheckedChanged: {
                        root.node.autoExclusive=checked
                    }
                }
            }
        }
    }
}
