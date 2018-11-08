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
                Layout.preferredHeight:  80
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

                            model:root.node.numBuffers

                            Item{
                                width: parent.width
                                height: width

                                Rectangle{
                                    anchors.fill: parent
                                    anchors.margins: 15


                                    border.width: 2
                                    color: "gray";
                                    opacity: 0.2
                                }



                            }


                        }

                    }
                }
            }
        }

    }


}





