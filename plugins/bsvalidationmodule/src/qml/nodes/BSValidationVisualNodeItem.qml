import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0

import automationmodule 1.0 as Module

Module.FlowNodeItem{

    id:root

    resizable:true;
    expandOnEdit:true;


    contentItem:  Rectangle{
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            RowLayout{
                Label{
                    Layout.fillWidth: true
                    text:"Estado:"
                }
                Label{
                    Layout.fillWidth: true
                    text:node.Status
                }
            }

            RowLayout{
                Label{
                    Layout.fillWidth: true
                    text:"Info do BS:"
                }
                Label{
                    Layout.fillWidth: true
                    text:node.BSInfo
                }
            }






        }

    }


}
