
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



    property string headerText:preProcessor?preProcessor.name:""

    height: editMode?childrenRect.height+10:childrenRect.height

    property Item containerItem

    onContainerItemChanged: {
        containerItem.parent=maincontainer
        maincontainer.height=Qt.binding(function(){
            return containerItem.height
        });

    }

    width: parent.width-10
    anchors.horizontalCenter: parent.horizontalCenter
    RowLayout{
        id:header
        width: parent.width
        height: 50

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text{

                width: parent.width
                text: headerText
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


    }

    Rectangle{
        width: parent.width
        height: 2
        color: Material.color(Material.Grey)
        anchors.top: header.bottom


    }


    GroupBox{
        visible: true

        width: parent.width

        title: "Settings:"

        id:container
        clip: true
        anchors.top:header.bottom

        anchors.topMargin:height>5? 5:0




        height: editMode?maincontainer.height+10:0



        Behavior on height{
            NumberAnimation { duration: 250 }
        }


        Item{
            id:maincontainer
            width: parent.width


        }


    }

    Rectangle{
        width: parent.width
        height: 2
        color: Material.color(Material.primary)
        anchors.topMargin:container.height>5? 5:0
        anchors.top: container.bottom

    }



}

