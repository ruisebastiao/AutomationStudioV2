import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import QtQuick.Controls.Material 2.2

Item{
    id:root

    property bool roiPressed: false
    property bool roiSelected: false

    onRoiSelectedChanged: {
        if(roiSelected){
            root.visible=true
        }
    }

    property string side: "right"


    property int containerSize: 300


    property Item contentItem

    onContentItemChanged: {
        if(contentItem){
            contentItem.parent=container
        }
    }

    clip: true
    anchors.verticalCenter: parent.verticalCenter
    width:configcontainer.width+50
    height: parent.height
    x:side=="right"?parent.width:-configcontainer.width-50



    MouseArea{
        anchors.fill: parent
        preventStealing: true
    }


    Rectangle{
        id:configcontainer
        height: parent.height
        width: root.containerSize
        radius: 25
        border.color: Material.accent
        border.width: 5
        anchors.verticalCenter: parent.verticalCenter
        Component.onCompleted: {
            x=Qt.binding(function() {

                if(root.side=="right"){
                    return roiSelected?10:-parent.width-5
                }
                if(root.side=="left"){
                    return roiSelected?40:width+50
                }

            })


        }


        //
        Behavior on x{
            enabled: roiPressed==false
            NumberAnimation {
                duration: 250
                onRunningChanged:{
                    if(root.roiSelected==false && running==false){
                        root.visible=false
                    }
                }

                easing.type: Easing.InOutBack
            }
        }

        Item{
            id:container
            anchors.fill: parent
            anchors.margins: 15



        }



    }

}


