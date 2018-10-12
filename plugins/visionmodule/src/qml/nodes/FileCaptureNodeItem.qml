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
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                RowLayout{
                    anchors.fill: parent
                    Label{
                        id:lbl
                        Layout.fillHeight: true;
                        Layout.fillWidth: true;

                        text: "Path: "
                        verticalAlignment: Text.AlignVCenter


                    }

                    TextField{
                        id:editfield
                        Layout.fillHeight: true;
                        Layout.fillWidth: true;
                        Layout.alignment: Qt.AlignVCenter

                        enabled: editMode
                        verticalAlignment: Text.AlignVCenter
                        text:node.filePath
                        onTextChanged: {
                            node.filePath=text
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
                        //root.node.processFile();
                        imagefile.file="";
                        imagefile.file=node.filePath;

                    }
                }

            }


        }



    }
}

