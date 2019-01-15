
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


Item {
    id:root
    default property alias children: content.children;

    property bool readOnly: false

    implicitWidth: content.width
    implicitHeight: content.height

    Item{
        id:content
//        Material.accent: Material.primary
        //color: "red"
        width: childrenRect.width
        height: childrenRect.height


    }

    MouseArea{
        anchors.fill: content
        propagateComposedEvents: false
        enabled: root.readOnly
        hoverEnabled: false
    }

}

