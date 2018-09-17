import QtQuick 2.8

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts      1.3

import "../gui"

FlowNode{
    id:root

    normalWidth: 150
    normalHeight: 150

    editHeight:150


    contentItem:  Rectangle{
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent

        }

    }
}
