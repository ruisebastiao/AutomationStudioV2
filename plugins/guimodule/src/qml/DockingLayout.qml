import QtQuick 2.7
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0

Item {
    id:root

//    property alias model:repeater.model

    property User loggedUser


    property Item contentItem
    onContentItemChanged: {
        if(contentItem){
            contentItem.parent=rootlayout
        }
    }

    GridLayout{
        id:rootlayout
        anchors.margins: 5
        anchors.fill: parent



    }

    //    Component.on

}
