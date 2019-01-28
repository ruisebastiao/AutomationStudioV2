import QtQuick              2.8
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0
import QtQuick.Dialogs 1.3

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
                        onActivated: {

                            root.node.selectedCamera=root.cameras.getItemAt(selectedCameraCombo.currentIndex);
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
            RowLayout{
                Layout.preferredHeight:50;
                Layout.fillWidth: true;
                CheckBox{
                    id:continuouscapture_check
                    Layout.fillWidth: true;
                    text: "Continuous Capture"
                    checked: root.node.continuousCapture
                    onCheckedChanged: {
                        root.node.continuousCapture=checked
                        if(root.node.configsLoaded){
                            root.node.updateContinuousCapture(checked);
                        }
                    }
                }
                CheckBox{

                    Layout.fillWidth: true;
                    text: "Start On init"
                    checked: node.connectOnInit
                    onCheckedChanged: {
                        node.connectOnInit=checked
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
            RowLayout{
                CheckBox{
                    Layout.fillWidth: true;
                    text: "Use parameters"
                    checked: root.node.useCameraParameters
                    onCheckedChanged: {
                        root.node.useCameraParameters=checked
                    }
                }
                TextArea{
                    enabled: root.node.useCameraParameters==false
                    Layout.fillWidth: true
                    text:root.node.cameraParametersPath
                    onTextChanged: {
                        root.node.cameraParametersPath=text
                    }


                    wrapMode: TextEdit.WordWrap


                    selectByMouse:true
                    MaterialPlaceHolder{
                        placeHolderText:"Parameters path"
                    }
                }
                Button{
                     Layout.fillWidth: true;
                     highlighted: true
                     enabled: root.node.useCameraParameters==false
                     text: "Select file"

                     FileDialog {
                         id: fileDialog
                         title: "Please choose a parameter file"
                         nameFilters: ["ini files (*.ini)"]
                         onAccepted: {
                             console.log("You chose: " + fileDialog.fileUrl)
                             root.node.cameraParametersPath=fileDialog.fileUrl
                         }
                         onRejected: {


                         }

                     }

                     onClicked: {
                         fileDialog.open()
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
