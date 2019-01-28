import QtQuick              2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0
import epsonmodule 1.0
import guimodule 1.0

FlowNodeItem{

    id:root
    expandOnEdit: true

    resizable: true


    contentItem:  ColumnLayout{
        anchors.fill: parent
        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            title: root.node.infoTitle
            ColumnLayout{

                anchors.fill: parent

                ListView{
                    id:infolist
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model: root.node.infos
                    clip: true


                    onCurrentIndexChanged:{
                       if(currentIndex==-1) {
                           container.info=null;
                       }
                    }

                    delegate: SwipeDelegate {
                        width: infolist.width
                        height: 40
                        highlighted: ListView.isCurrentItem

                        onHighlightedChanged: {
                            if(highlighted){
                                container.info=info
                            }
                        }
                        swipe.transition: Transition {
                            SmoothedAnimation { velocity: 3; easing.type: Easing.InOutCubic }
                        }
                        swipe.onOpened:{
                            infolist.model.removeItem(info)
                            textID.text=""
                        }

                        swipe.right: Label {
                            id: deleteLabel
                            text: qsTr("Delete")
                            color: "white"
                            verticalAlignment: Label.AlignVCenter
                            padding: 12
                            height: parent.height
                            anchors.right: parent.right



                            background: Rectangle {
                                color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                            }
                        }


                        onClicked: {
                            infolist.currentIndex = index

                        }
                        Label{

                            text: info.id+" ("+info.projectName+")"
                            anchors.fill: parent
                            font.pixelSize: 16
                            horizontalAlignment:Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            //                     fontSizeMode:Text.Fit
                        }
                    }

                }

                ColumnLayout{
                    id:container
                    Layout.fillWidth: true

                    property var info


                    RowLayout{
                        Layout.fillWidth: true
                        Button{

                            Layout.fillWidth: true
                            text: container.info?"Save":"Add"
                            highlighted: true
                            enabled: textID.length>0 && textProjectName.length>0
                            onClicked: {
                                if(!container.info){
                                    root.node.addInfo(textID.text,textProjectName.text);
                                }
                                else{
                                    root.node.updateInfo(container.info,textID.text,textProjectName.text);
                                }
                            }
                        }


                    }
                    Pane{
                        Layout.fillWidth: true
                        Layout.preferredHeight: 75


                        Material.elevation: 8


                        RowLayout{
                            anchors.fill: parent
                            TextField{
                                property bool idvalid: false
                                property string currenttext: ""
                                id:textID
                                text: container.info?container.info.id:currenttext


                                onTextChanged: {
                                    if(currenttext!=text){
                                        currenttext=text
                                    }

                                    container.info=root.node.infos.getById(text)

                                }

                                MaterialPlaceHolder{
                                    placeHolderText:"ID"
                                }
                            }
                            TextField{
                                id:textProjectName
                                text: container.info?container.info.projectName:""

                                MaterialPlaceHolder{
                                    placeHolderText:"Project Name"
                                }
                            }
                        }

                    }

                    Button{

                        Layout.fillWidth: true
                        text: "Check from input"
                        highlighted: true

                        onClicked: {
                            root.node.checkInfo=true
                        }
                    }
                    CheckBox{
                        Layout.fillWidth: true
                        text: "Check on input"
                        checked: root.node.checkOnInput
                        onCheckedChanged: {
                            root.node.checkOnInput=checked
                        }
                    }
                }

            }
        }

    }
}
