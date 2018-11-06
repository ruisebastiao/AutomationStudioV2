import QtQuick              2.8
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import guimodule 1.0

import automationmodule 1.0

import visionmodule 1.0

FlowNodeItem{
    id:root

    //    normalWidth: 300
    //    normalHeight: 200

    property IDSCameraListModel cameras: node.availableCameras

    property IDSCamera selectedCamera: node.selectedCamera

    onSelectedCameraChanged: {
        if(selectedCamera){

            selectedCameraCombo.currentIndex=cameras.indexOfID(selectedCamera.camID)

        }
        else{
            console.log("No camera selected");
            selectedCameraCombo.currentIndex=-1;
        }
    }

    resizable: true

    contentItem:  Rectangle{

        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent

            ColumnLayout{
                Layout.fillHeight: true
                Layout.fillWidth: true

                RowLayout{
                    Layout.preferredHeight: 42
                    Layout.fillWidth: true

                    Label{
                        text:"Camera: "
                    }

                    ComboBox{
                        id:selectedCameraCombo
                        Layout.fillWidth: true
                        model:root.cameras
                        currentIndex: -1
                        textRole: 'name'
                        onCurrentIndexChanged: {
                            console.log(currentIndex)

                            //                            node.cameraSerialNumber=selectedCamera.model.at(currentIndex)
                        }

                        onCurrentTextChanged: {
                            //node.cameraSerialNumber=selectedCamera.currentText
                        }


                        Component.onCompleted: {

                        }
                    }


                }

                RowLayout{
                    Layout.preferredHeight: 42
                    Layout.fillWidth: true

                    Label{
                        text:"Opened: "
                    }


                    Switch{
                        enabled: node.cameraAvailable && root.node.updatingCamera==false
                        checked: node.cameraOpened;

                        onCheckedChanged: {
                            node.setCamera(checked)
                        }
                    }
                    CheckBox{
                        text: "Trigger mode"
                        enabled: root.node.cameraOpened
                        checked: root.node.externalTrigger
                        onCheckedChanged: root.node.externalTrigger=checked
                    }
                    BusyIndicator{
                        Layout.fillHeight: true
                        Layout.preferredWidth: height;

                        running: root.node.updatingCamera
                        visible: true
                    }




                }

            }
            Item{
                Layout.preferredHeight:50;
                Layout.fillWidth: true;
                CheckBox{
                    id:continuouscapture_check
                    text: "Continuous Capture"
                    enabled:  node.cameraOpened && root.node.updatingCamera==false;
                    onCheckedChanged: {
                        node.continuousCapture=checked
                    }
                }

            }

            Item{
                Layout.preferredHeight: 60
                Layout.fillWidth: true;
                RowLayout{
                    anchors.fill: parent
                    Item{
                        Layout.fillHeight:true;
                        Layout.fillWidth: true;
                        Label{
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter

                            text:"Acquisition buffers:"
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

                            enabled: root.node.cameraOpened==false
                            editable: false

                        }

                    }


                }








            }


            Item{
                Layout.fillHeight:true;

                Layout.fillWidth: true;



            }
        }


    }


}
