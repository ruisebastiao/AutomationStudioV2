import QtQuick 2.7
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
    id:root

    property alias model:repeater.model

    GridLayout{
        id:rootlayout
        anchors.margins: 5
        anchors.fill: parent

        Repeater {
            id:repeater

            DockingItem {
                dockContainer: root
             //   loadedmodule:repeater.itemAt(index)
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

    }

    //    Component.on

}
