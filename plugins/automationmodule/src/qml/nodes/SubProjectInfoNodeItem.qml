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
            title: "Tools"
            ColumnLayout{

                anchors.fill: parent

                ListView{
                    id:infolist
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model: root.node.tools
                    clip: true


                    onCurrentIndexChanged:{
                       if(currentIndex==-1) {
                           container.toolInfo=null;
                       }
                    }

                    delegate: SwipeDelegate {
                        width: infolist.width
                        height: 40
                        highlighted: ListView.isCurrentItem

                        onHighlightedChanged: {
                            if(highlighted){
                                container.toolInfo=tool
                            }
                        }
                        swipe.transition: Transition {
                            SmoothedAnimation { velocity: 3; easing.type: Easing.InOutCubic }
                        }
                        swipe.onOpened:{
                            infolist.model.removeItem(tool)
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

                            //                            SwipeDelegate.onClicked: toolslist.model.removeItem(tool)

                            background: Rectangle {
                                color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                            }
                        }


                        onClicked: {
                            infolist.currentIndex = index

                        }
                        Label{

                            text: tool.id+" ("+tool.projectName+")"
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

                    property var toolInfo
                    onToolInfoChanged: {

                    }



                    RowLayout{
                        Layout.fillWidth: true
                        Button{

                            Layout.fillWidth: true
                            text: container.toolInfo?"Save":"Add"
                            highlighted: true
                            enabled: textID.length>0 && textProjectName.length>0
                            onClicked: {
                                if(!container.toolInfo){
                                    root.node.addTool(textID.text,textProjectName.text);
                                }
                                else{
                                    root.node.updateTool(container.toolInfo,textID.text,textProjectName.text);
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
                                text: container.toolInfo?container.toolInfo.id:currenttext


                                onTextChanged: {
                                    if(currenttext!=text){
                                        currenttext=text
                                    }

                                    container.toolInfo=root.node.tools.getByToolId(text)

                                }

                                MaterialPlaceHolder{
                                    placeHolderText:"Tool ID"
                                }
                            }
                            TextField{
                                id:textProjectName
                                text: container.toolInfo?container.toolInfo.projectName:""

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
                            root.node.checkTool=true
                        }
                    }
                }

            }
        }

    }
}
