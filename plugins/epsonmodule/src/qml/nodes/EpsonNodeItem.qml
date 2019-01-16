import QtQuick              2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0
import epsonmodule 1.0
import guimodule 1.0 as GUI

FlowNodeItem{

    id:root
    expandOnEdit: true

    resizable: true
    contentItem:  Rectangle{

        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            GroupBox{
                visible: root.node.connection==EpsonNode.TCPCLIENT
                Layout.fillWidth: true
                Layout.preferredHeight: 125
                title: "TCP Connection"
                ColumnLayout{
                    anchors.fill: parent

                    RowLayout{
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50

                        TextField{
                            id:hostname_lbl
                            Layout.fillWidth: true
                            text: root.node.tcpClient.host
                            onAccepted: {
                                root.node.tcpClient.host=text
                            }
                            onFocusChanged: {
                                if(focus==false){
                                    root.node.tcpClient.host=text
                                }
                            }

                            selectByMouse:true
                            GUI.MaterialPlaceHolder{

                                placeHolderText:"Host"
                            }
                        }
                        TextField{
                            id:port_lbl
                            Layout.fillWidth: true
                            inputMethodHints:Qt.ImhDigitsOnly
                            text: root.node.tcpClient.port
                            onAccepted: {
                                root.node.tcpClient.port=text*1
                            }
                            onFocusChanged: {
                                if(focus==false){
                                    root.node.tcpClient.port=text*1
                                }
                            }

                            selectByMouse:true
                            GUI.MaterialPlaceHolder{

                                placeHolderText:"Port"
                            }
                        }

                    }
                    CheckBox{
                        text: "Reconnect on close"
                        checked: root.node.tcpClient.reconnectOnClose
                        onCheckedChanged: {
                            root.node.tcpClient.reconnectOnClose=checked
                        }
                    }
                }
            }
            Item{
                Layout.fillWidth: true
                Layout.preferredHeight: 75
                Button{
                    anchors.fill: parent
                    highlighted: true
                    text:root.node.tcpClient.state==QAbstractSocket.ConnectedState?"Disconnect":"Connect"

                    onClicked: {
                        root.node.toogleConnection();
                    }
                }

            }
        }
    }
}
