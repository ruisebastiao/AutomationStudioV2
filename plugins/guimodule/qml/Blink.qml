import QtQuick 2.8

Item {

    id:root
    property Item target: parent

    property bool running: false

    property int blinkTime: 200
    Item{

        id:container

        SequentialAnimation{
            id:blinkanimation

            running: root.running

            alwaysRunToEnd: true
            loops: Animation.Infinite

            NumberAnimation {
                target: root.target
                property: "opacity"
                from:1
                to:0
                duration: blinkTime
                easing.type: Easing.OutCubic
            }


            PauseAnimation {
                duration: blinkTime/1.5
            }

            NumberAnimation {
                target: root.target
                from:0
                to:1
                property: "opacity"
                duration: blinkTime
                easing.type: Easing.OutCubic
            }

            PauseAnimation {
                duration: blinkTime/1.5
            }
        }

    }

}
