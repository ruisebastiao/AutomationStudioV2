import QtQuick              2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0
import visionmodule 1.0

FlowNodeItem{

    id:root
    expandOnEdit: true

    resizable: true


    contentItem:  Rectangle{

        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent

            Item{
                Layout.preferredHeight:  50
                Layout.fillWidth: true
                RowLayout{


                    anchors.fill: parent


                    Rectangle{

                        Layout.fillHeight:true;
                        Layout.fillWidth: true;
                        Label{
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter

                            text:"Frame buffers:"
                        }
                    }

                    Item{
                        Layout.fillHeight:true;

                        Layout.fillWidth: true;

                        SpinBox{
                            anchors.fill: parent
                            from:1
                            to:30
                            value: root.node.numBuffers;
                            onValueChanged: {
                                root.node.numBuffers=value
                            }

                            //enabled: root.node.cameraOpened==false
                            editable: false

                        }

                    }


                }

            }
            Item{
                Layout.preferredHeight:  50
                Layout.fillWidth: true
                RowLayout{


                    anchors.fill: parent


                    Rectangle{

                        Layout.fillHeight:true;
                        Layout.preferredWidth: wid.paintedWidth
                        Label{
                            id:wid
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter

                            text:"Write Index:"
                        }
                    }

                    Item{
                        Layout.fillHeight:true;

                        Layout.fillWidth: true;

                        SpinBox{
                            anchors.fill: parent
                            from:0
                            to:root.node.numBuffers-1;
                            value: root.node.writeIndex;
                            onValueChanged: {
                                root.node.writeIndex=value
                            }

                            enabled: root.node.editMode
                            //editable: false

                        }

                    }
                    Item{
                        Layout.fillHeight:true;

                        Layout.fillWidth: true

                        CheckBox{
                            id:cid1
                            anchors.fill: parent
                            text: "Auto increment"
                            checked: root.node.autoIncrementWriteIndex
                            onCheckedChanged: {
                                root.node.autoIncrementWriteIndex=checked
                            }
                        }
                    }


                }

            }

            Item{
                Layout.preferredHeight:  50
                Layout.fillWidth: true
                RowLayout{


                    anchors.fill: parent


                    Rectangle{

                        Layout.fillHeight:true;
                        Layout.preferredWidth: lid2.paintedWidth
                        Label{
                            id:lid2
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter

                            text:"Read Index:"
                        }
                    }

                    Item{
                        Layout.fillHeight:true;

                        Layout.fillWidth: true;

                        SpinBox{
                            anchors.fill: parent
                            from:0
                            to:root.node.numBuffers-1;
                            value: root.node.readIndex;
                            onValueChanged: {
                                root.node.readIndex=value
                            }

                            enabled: root.node.editMode

                        }

                    }
                    Item{
                        Layout.fillHeight:true;

                        Layout.fillWidth: true

                        CheckBox{
                            id:cid2
                            anchors.fill: parent
                            text: "Auto increment"
                            checked: root.node.autoIncrementReadIndex
                            onCheckedChanged: {
                                root.node.autoIncrementReadIndex=checked
                            }
                        }
                    }
                    Item{
                        Layout.fillHeight:true;

                        Layout.fillWidth: true

                        Button{
                            visible: root.node.editMode
                            anchors.fill: parent
                            text: "Process"

                            onClicked: {
                                root.node.processCurrent();
                            }

                        }
                    }





                }

            }

            Item{
                Layout.preferredHeight:  50
                Layout.fillWidth: true
                RowLayout{
                    CheckBox{
                        text: "Lock and read on write"
                        Layout.fillWidth: true
                        checked: root.node.lockWriteReadIndex
                        onCheckedChanged: {
                            root.node.lockWriteReadIndex=checked
                        }
                    }
                    CheckBox{
                        text: "Store captures"
                        Layout.fillWidth: true
                        checked: root.node.storeCapture
                        onCheckedChanged: {
                            root.node.storeCapture=checked
                        }
                    }
                }


            }


            Item{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Flickable {
                    id: f
                    anchors.fill: parent
                    //                    boundsBehavior: Flickable.OvershootBounds
                    contentHeight: iContainer.height;
                    contentWidth: iContainer.width;
                    clip: true
                    Column {
                        id: iContainer
                        width: f.width
                        Repeater{

                            model:root.node.frameBuffers

                            Item{
                                width: parent.width
                                height: width

                                Rectangle{
                                    anchors.fill: parent
                                    anchors.margins: 15


                                    Rectangle{
                                        anchors.fill: parent

                                        MouseArea{
                                            anchors.fill: viewer
                                            onClicked: {
                                                if (root.node.editMode){
                                                    root.node.readIndex=index
                                                    root.node.processCurrent();
                                                }
                                            }
                                        }

                                        QMatView{

                                            id:viewer
                                            anchors.margins: 5
                                            anchors.fill: parent
                                            mat:itemMat

                                        }


                                        Rectangle{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.left: parent.left
                                            height: root.node.writeIndex==index?parent.height-5:0
                                            width: 5
                                            radius: width*0.5
                                            Behavior on height {
                                                NumberAnimation { duration: 150 }
                                            }


                                            opacity: root.node.writeIndex==index?0.75:0
                                            Behavior on opacity {
                                                NumberAnimation { duration: 50 }
                                            }


                                            color: Material.color(Material.Red)
                                        }


                                        Rectangle{
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.right: parent.right
                                            height: root.node.readIndex==index?parent.height-5:0
                                            width: 5
                                            radius: width*0.5
                                            Behavior on height {
                                                NumberAnimation { duration: 150 }
                                            }


                                            opacity: root.node.readIndex==index?0.75:0
                                            Behavior on opacity {
                                                NumberAnimation { duration: 50 }
                                            }


                                            color: Material.color(Material.Green)
                                        }


                                    }






                                }



                            }


                        }

                    }
                }
            }
        }

    }


}





