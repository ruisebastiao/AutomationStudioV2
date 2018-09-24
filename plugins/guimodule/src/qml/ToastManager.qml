import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1


Item {

    id:root



    signal addMessage(string message);

    onAddMessage: {

        toasters_list.model.insert(0,{"message": message})
    }

    Item{
        id:container
        anchors.fill: parent
        property int hideDelay: 2500
        ListModel { id: messagesModel }

        ListView{
            id:toasters_list
            anchors.fill: parent

            interactive: false
            add: Transition {
                NumberAnimation { property: "opacity"; to: 1.0; duration: 250 }
                NumberAnimation { property: "scale"; easing.type: Easing.OutBack; from: 0; to: 1.0; duration: 350 }
            }

            addDisplaced: Transition {
                NumberAnimation { property: "opacity"; to: 1.0; duration: 250 }
                NumberAnimation { properties: "x,y"; duration: 150 }
                NumberAnimation { property: "scale"; easing.type: Easing.OutBack;  to: 1.0; duration: 350 }
            }


            remove: Transition {
                NumberAnimation { property: "x"; easing.type: Easing.InBack; to: toasters_list.width+10; duration: 250 }
                NumberAnimation { property: "opacity"; easing.type: Easing.Linear; from: 1.0; to: 0; duration: 350 }

            }


            delegate: messageDelegate
            model: messagesModel
        }

        Component {
            id: messageDelegate



            Button {

                width: message_label.paintedWidth+5

                highlighted: true

                x:parent.width-width-10
                //anchors.margins: 2
                Label {
                    id:message_label
                    anchors.centerIn: parent

                    text: message
                }

                Timer{
                    repeat: false
                    interval: container.hideDelay
                    running: true
                    onTriggered: {
                        messagesModel.remove(index,1)
                    }

                }
            }


        }


        //        Timer{
        //            id:temp_timer
        //             repeat: true
        //             interval: 3000
        //             onTriggered:{
        //                 root.addMessage("Item "+(messagesModel.count+1))
        ////                 if(messagesModel.count>2){
        ////                    messagesModel.remove(messagesModel.count-1,1)
        ////                 }

        //                 if(messagesModel.count==5){
        //                    repeat=false;
        //                 }

        //             }
        //        }


    }

}
