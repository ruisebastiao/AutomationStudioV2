
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0 as GUI

import automationmodule 1.0 as Module

FlowNodeItem{

    id:root

    property bool initialized: false
    resizable:true;
    expandOnEdit:true;
    contentItem:  Rectangle{

        anchors.fill: parent

        ColumnLayout{
            anchors.fill: parent
            TextField{

                Layout.fillWidth: true

                text: root.node.in.toString()


                readOnly: true
                selectByMouse:true
                GUI.MaterialPlaceHolder{

                    placeHolderText:"Input"
                }
            }

            RowLayout{
                Layout.fillWidth: true

                TextField{

                    Layout.fillWidth: true

                    text: root.node.extractProperty
                    onTextChanged: {
                        root.node.extractProperty=text
                    }


                    selectByMouse:true
                    GUI.MaterialPlaceHolder{

                        placeHolderText:"Extract property"
                    }
                }
                TextField{

                    Layout.fillWidth: true

                    text: root.node.separator
                    onTextChanged: {
                        root.node.separator=text
                    }


                    selectByMouse:true
                    GUI.MaterialPlaceHolder{

                        placeHolderText:"Separator"
                    }
                }
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.minimumHeight: 150

                TextArea{



                    text: root.node.out


                    wrapMode: TextEdit.WordWrap

                    readOnly: true
                    selectByMouse:true
                    //                GUI.MaterialPlaceHolder{

                    //                    placeHolderText:"Result"
                    //                }
                }
            }
        }
    }
}
