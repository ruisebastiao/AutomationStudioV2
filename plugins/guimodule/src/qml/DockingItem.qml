import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0



Pane{
    id:root
    Material.elevation:8
    //    clip: true
    Layout.fillHeight: true
    Layout.fillWidth: true



    Layout.margins: 2
    property bool isLoaded:false

    Component.onCompleted: {

        isLoaded=true
        setHidden()
    }


    function setHidden(){
        if(isHidden){
            //                console.log("isHidden:true")
            root.Layout.fillWidth=false

            root.Layout.preferredWidth=0


        }
        else{
            root.Layout.fillWidth=true
            root.Layout.preferredWidth=-1

        }
    }

    property bool isHidden: false
    onIsHiddenChanged: {
        if(isLoaded){
            setHidden()
        }
    }



    opacity: 1


    default property alias contents: placeholder.children


    Item{
        id:placeholder
        anchors.fill: parent

    }
}
