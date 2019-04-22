import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import QtQuick.Controls.Material 2.1


Item {
    id:root


    property alias label:current_label
    property alias font:current_label.font
    property alias horizontalAlignment: current_label.horizontalAlignment
    property alias verticalAlignment: current_label.verticalAlignment
    property int textHeight: current_label.contentHeight;
    property int textWidth: current_label.contentWidth;
    property string text

    //    property string textColor: Material.foreground
    property int duration:250

//    width: textWidth
    implicitHeight: container.implicitHeight

    implicitWidth: textWidth

    onTextChanged: {
        //current_label.text=text
//        if(change_anim.running){
            change_anim.stop();
//        }
        next_label.text=text
        change_anim.start()
    }


    Item{
        id:container

        width: parent.width
//        implicitWidth: current_label.contentWidth
        implicitHeight: current_label.contentHeight

        anchors.centerIn: parent

        clip: true
//        anchors.fill: parent

        Label{
            id:current_label
            text:""

            anchors{
                left: parent.left
                right:parent.right
            }
            y:parent.height/2-paintedHeight/2
            //  color: root.textColor

        }


        Label{
            id:next_label
            font:current_label.font
            horizontalAlignment: current_label.horizontalAlignment
            verticalAlignment: current_label.verticalAlignment

            //color: root.textColor

            anchors{
                left: parent.left
                right:parent.right
            }
            y:-parent.height
        }



    }



    ParallelAnimation{
        id:change_anim

        NumberAnimation { target: current_label; property: "y";from:container.height/2-current_label.paintedHeight/2; to: container.height;
            duration: duration;easing.type: Easing.InOutQuad
        }
        NumberAnimation { target: next_label; property: "y";from:-container.height; to: container.height/2-next_label.paintedHeight/2;
            duration: duration;easing.type: Easing.InOutQuad
        }
        onStopped: {
            current_label.text=root.text;
//            next_label.text=""
        }
    }

}
