
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import visionmodule 1.0

Rectangle {

    id:root

    property bool editMode: false


    property PreProcessing preProcessor;



    property string headerText:""

    height: childrenRect.height+10

    property Item containerItem

    onContainerItemChanged: {
        containerItem.parent=container
        containerItem.height=Qt.binding(function(){
            return containerItem.childrenRect.height;
        })

    }

    width: parent.width
    RowLayout{
        id:header
        width: parent.width
        height: 50

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text{

                width: parent.width
                text: preProcessor.name
                height:parent.height
                fontSizeMode: Text.HorizontalFit

                font.pixelSize: 18

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                visible: true

            }
            MouseArea{
                anchors.fill: parent
                onPressAndHold: {
                    root.editMode=!root.editMode
                }

                onDoubleClicked: {
                    root.editMode=!root.editMode
                }
            }
        }
//        Item{
//            Layout.fillHeight: true
//            Layout.preferredWidth:50
//            RoundButton{
//                anchors.fill: parent
//                highlighted: true
//                onPressed: {
//                    root.editMode=!root.editMode
//                    console.log("PreProcessingItem editmode:"+editMode)
//                }
//            }
//        }

    }
    Item{
        id:container
        clip: true
        anchors.top:header.bottom

        height: editMode?containerItem.height+10:0

        Behavior on height{
            NumberAnimation { duration: 250 }
        }

        width: parent.width
    }

}

