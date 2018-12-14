import QtQuick 2.7
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0

Item {
    id: root
    anchors.fill: parent
    default property alias contents: placeholder.children


    GridLayout{
        id:placeholder
        anchors.fill: parent
        rowSpacing: 5
        columnSpacing: 5


    }
}



