import QtQuick 2.8

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts      1.3

import guimodule 1.0

import automationmodule 1.0 as Module

FlowNodeItem{
    id:root

    resizable: true
    expandOnEdit: true

    contentItem:  Rectangle{
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent

            Item{
                Layout.fillHeight: true;
                Layout.fillWidth: true;

                TextField{
                    id:editfield
                    anchors.centerIn: parent
                    width: parent.width-5
                    text:node.serviceUrl
                    MaterialPlaceHolder{

                        placeHolderText:"Service Url"

                    }
                    onTextChanged: {
                        node.serviceUrl=text
                    }
                }
            }
            Item{
                Layout.fillHeight: true;
                Layout.fillWidth: true;

                RowLayout{
                    anchors.fill: parent

                    TextArea{

                        Layout.fillWidth: true
                        text:node.formattedUrl

                        readOnly: true


                       id:label_query_str

                        wrapMode: TextEdit.WordWrap


                        selectByMouse:true
                        MaterialPlaceHolder{
                            placeHolderText:"Query"
                        }
                    }

                }
            }
        }

    }
}
