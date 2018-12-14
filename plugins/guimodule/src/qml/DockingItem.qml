import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0



Pane{
    id:root
    Material.elevation:8
    clip: true
    Layout.fillHeight: true
    Layout.fillWidth: true

    Layout.margins: 5
    property bool isLoaded:false

    property Item oldparent

    Component.onCompleted: {
        oldparent=parent
        //        console.log("Completed")
        isLoaded=true
        setHidden()
    }


    function setHidden(){
        if(isHidden){
            //                console.log("isHidden:true")
            root.Layout.fillWidth=false

            root.Layout.preferredWidth=0

            //            parent=null
        }
        else{
            root.Layout.fillWidth=true
            root.Layout.preferredWidth=-1
            //            root.Layout.preferredWidth=500
            //                console.log("isHidden:false")
            //            parent=oldparent
        }
    }

    property bool isHidden: false
    onIsHiddenChanged: {
        if(isLoaded){
            setHidden()
        }
    }


//    Behavior on implicitWidth{
//        NumberAnimation { duration: 250 }
//    }

//    Behavior on width{
//        NumberAnimation { duration: 250 }
//    }

//    Behavior on Layout.preferredWidth {
//        NumberAnimation { duration: 250 }
//    }

    opacity: 1


    default property alias contents: placeholder.children

    //    states: State {
    //        name: "reparented"
    //        ParentChange { target: root; parent: root.parent; x: 10; y: 10 }
    //    }

    //    transitions: Transition {
    //        ParentAnimation {
    //            NumberAnimation { properties: "x,y"; duration: 1000 }
    //        }
    //    }

    Item{
        id:placeholder
        anchors.fill: parent

    }

    //    MouseArea {
    //        id: dragArea
    //        anchors.fill: parent

    //        drag.target: parent.parent
    //    }

}
