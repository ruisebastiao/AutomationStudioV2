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
                    Item {

                        Layout.preferredHeight: label_query.paintedHeight
                        Layout.preferredWidth: label_query.paintedWidth

                        Label{
                            id:label_query
                            text:"Query:"
                        }
                    }
                    Item{
                        Layout.preferredHeight: label_query_str.paintedHeight
                        Layout.fillWidth: true;


                        Label{
                            id:label_query_str
                            anchors.centerIn: parent
                            horizontalAlignment: Text.AlignHCenter
                            width: parent.width-10
                            minimumPixelSize: 10;
                            font.pixelSize: 14
                            fontSizeMode:Text.HorizontalFit
                            text:node.formattedUrl
                        }
                    }
                }
            }
        }

    }
}
