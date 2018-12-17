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

    property Item fullscreenItem: null

//    onFullscreenItemChanged: {
//        if(fullscreenItem){
//            fullscreenItem.parent=fullscreencontainer
//            fullscreenItem.width=parent.width

//        }
//        else{

//        }
//    }

    GridLayout{
        id:placeholder
        anchors.fill: parent
        rowSpacing: 2
        columnSpacing: 2


    }


//    Item{
//        id:fullscreencontainer
//        anchors.fill: parent
//        visible: fullscreenItem

//    }
}



