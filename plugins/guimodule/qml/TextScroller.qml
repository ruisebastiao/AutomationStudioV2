import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import QtQuick.Controls.Material 2.1


Item {
    id:root
  //  anchors.fill: parent

    property alias font:current_label.font
    property alias horizontalAlignment: current_label.horizontalAlignment
    property alias verticalAlignment: current_label.verticalAlignment

    property string text:""

//    property string textColor: Material.foreground
    property int duration:250


    onTextChanged: {
        //current_label.text=text
        next_label.text=text
//        next_label.color=textColor
        change_anim.start()
    }


    Rectangle{
        id:container

        color: "transparent"
        clip: true
        anchors.fill: parent

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
            current_label.text=next_label.text;
//            current_label.color=root.textColor
            next_label.text=""
        }
    }

}
