import QtQuick 2.8

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1


Item {
    //anchors.fill: parent

    id:root


    clip: true;
    property var model;

    property bool animate: false

    state:"base"

    states: [

        State {
            name: "base"

            //            PropertyChanges { target: current_language; y: current_language.parent.height/2-current_language.height/2}

            //            PropertyChanges { target: new_language; y:new_language.parent.height+15}


        },
        State {
            name: "scrollUp"


            onCompleted: {
                root.state="base"
            }
        },
        State {
            name: "scrollDown"



        }
    ]

    transitions: [
        Transition {

            to: "scrollUp"

            YAnimator{
                target: current_language
                from:1
                to:-container.height-15
                duration: 300
                easing.type: Easing.OutQuad
            }
            YAnimator{
                target: new_language
                from:container.height+15
                to:container.height/2-10
                duration: 300
                easing.type: Easing.OutQuad
            }


            onRunningChanged: {
                if(running===false){
                    current_language.itemmodel=model;
                }
                else{
                    new_language.itemmodel=model
                }

            }
        },

        Transition {

            to: "scrollDown"

            YAnimator{
                target: current_language
                from:0
                to:container.height
                duration: 100
            }

        }
    ]


    onModelChanged: {
        // y:

        if(animate){



            if(typeof current_language === 'undefined'  ){

                if (typeof model !== 'undefined' || model){


                    new_language.itemmodel=model
                    current_language.itemmodel=model
                }
                else
                    return;

            }
            else{

              //  console.log(model)
                scrollTimer.start();

            }

        }
        else
            current_language.itemmodel=model

    }

    Timer{
        id:scrollTimer
        interval: 100; running: false; repeat: false
        onTriggered: root.state="scrollUp"


    }

    Item{
        id:container


        anchors.fill: parent


        RowLayout{

            id:new_language
            property var itemmodel: null

            y:height



            Item{
                id:new_flag
                Layout.preferredWidth: 32;
                Layout.fillHeight: true

                Image{
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                    width: 32
                    height: 32
                    source: new_language.itemmodel?new_language.itemmodel.flag:""

                }
            }
            Label{
                Layout.fillWidth:  true
                Layout.fillHeight: true

                Layout.alignment: Qt.AlignVCenter
                verticalAlignment:Text.AlignVCenter
                id:new_combo_label
                font.pixelSize: combo_language.font.pixelSize
                text: new_language.itemmodel?new_language.itemmodel.text:""

                anchors.leftMargin: 10


            }
        }



        RowLayout{

            id:current_language
            property var itemmodel: null

            height: parent.height
            y:0



            Item{
                id:curr_flag
                Layout.preferredWidth: 32;
                Layout.fillHeight: true

                Image{
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                    width: 30
                    height: 30
                    source:current_language.itemmodel?current_language.itemmodel.flag:""

                }
            }
            Label{
                Layout.fillWidth:  true
                Layout.fillHeight: true

                Layout.alignment: Qt.AlignVCenter
                verticalAlignment:Text.AlignVCenter
                id:curr_combo_label
                font.pixelSize: combo_language.font.pixelSize
                text: current_language.itemmodel?current_language.itemmodel.text:""

                anchors.leftMargin: 10


            }
        }


    }




}
