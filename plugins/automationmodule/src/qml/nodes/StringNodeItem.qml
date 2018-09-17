import QtQuick 2.8


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import guimodule 1.0

import automationmodule 1.0 as Module


FlowNodeItem{
    id:root

    expandOnEdit:true
    resizable: true
    onEditModeChanged: {
        if(editMode){
            editfield.forceActiveFocus()
        }
    }

    contentItem:  Rectangle{

        anchors.fill: parent
        TextField{
            id:editfield
            anchors.centerIn: parent
            text:node.stringValue
            onTextChanged: {
                if(node.stringValue!=text){
                    node.stringValue=text
                }


            }
        }
    }
}
