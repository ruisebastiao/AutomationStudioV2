import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import visionmodule 1.0


Item {
    id:root
    property ROINode selectedROINode

    onSelectedROINodeChanged: {
        if(selectedROINode){
           selectedROINode.processingContainer.parent=container
            selectedROINode.processingContainer.visible=true
        }
    }

    MouseArea{
        anchors.fill: parent
        preventStealing: true
    }

    Rectangle{
        anchors.fill: parent
        opacity: 0.5

    }

    Item{
        id:container
        anchors.fill: parent
    }


}
