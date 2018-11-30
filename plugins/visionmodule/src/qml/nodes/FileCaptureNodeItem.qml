import QtQuick              2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0
import visionmodule 1.0

FlowNodeItem{

    id:root
    expandOnEdit: false

    resizable: true

    onEditModeChanged: {
        if(editMode){
            editfield.forceActiveFocus()
        }
    }


    Connections{
        target:root.node
        onProcessFileChanged:{
            imagefile.file="";
            imagefile.file=filepath;

        }
    }

    QImRead{
        id:imagefile
        iscolor: QImageFile.CV_LOAD_IMAGE_GRAYSCALE
        visible: false
        onOutputChanged:{
            root.node.frameSink=output
            root.node.frameCaptured=true
        }

    }

    contentItem:  Rectangle{

        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            Item{
                //                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.margins: 5
                Layout.preferredHeight:50
                RowLayout{
                    anchors.fill: parent
                    Label{
                        id:lbl
                        //                        : : true;
                        Layout.fillWidth: true;

                        text: "Path: "
                        verticalAlignment: Text.AlignVCenter


                    }

                    TextField{
                        id:editfield
                        //                        Layout.fillHeight: true;
                        Layout.fillWidth: true;
                        Layout.alignment: Qt.AlignVCenter

                        enabled: editMode
                        verticalAlignment: Text.AlignVCenter
                        text:node.filePath
                        //                        onTextChanged: {

                        //                        }
                        onAccepted: {
                            node.filePath=text
                            root.node.processFile();
                        }
                        onFocusChanged: {
                            if(focus==false){
                                node.filePath=text
                            }
                        }
                    }

                }
            }
            Item{
                Layout.fillWidth: true;
                Layout.margins: 5
                Layout.preferredHeight:50
                RowLayout{
                    anchors.fill: parent
                    CheckBox{
                        Layout.fillWidth: true
                        text:"Read sequence"
                        checked: node.useSequence
                        onCheckedChanged: {
                            node.useSequence=checked
                        }
                    }

                    Label{
                        Layout.fillWidth: true
                        text: "Index:"
                    }

                    SpinBox{
                        Layout.fillWidth: true
                        value: node.fileIndex
                        onValueChanged: {
                            node.fileIndex=value
                        }
                    }

                    Label{
                        Layout.fillWidth: true
                        text: "Size:"
                    }

                    SpinBox{
                        Layout.fillWidth: true
                        value: node.sequenceSize
                        onValueChanged: {
                            node.sequenceSize=value
                        }
                    }

                }
            }


            Item {

                Layout.preferredHeight:60;
                Layout.fillWidth: true;
                Button{
                    anchors.fill: parent
                    text:"Process"
                    highlighted: true

                    onClicked: {
                        root.node.processFile();
                        //                        imagefile.file="";
                        //                        imagefile.file=node.filePath;

                    }
                }

            }


        }



    }
}

