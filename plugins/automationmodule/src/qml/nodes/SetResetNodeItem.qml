import QtQuick 2.8

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts      1.3


FlowNodeItem{
    id:root

    resizable: true

    contentItem:  Rectangle{
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            RadioButton{
                Layout.fillWidth: true
                checked: root.node.output
            }
        }

    }
}
