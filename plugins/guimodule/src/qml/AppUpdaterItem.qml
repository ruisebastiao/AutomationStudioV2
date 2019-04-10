import QtQuick 2.10
//import QtQuick.Window 2.10
//import QtQuick.VirtualKeyboard 2.3

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3


import QtQuick.Controls.Material 2.1

Pane {
    anchors.centerIn: parent

   Material.elevation: 8

//    radius: width*0.01
    width: parent.width/1.5
    height: parent.height/2.5

    ColumnLayout{
        anchors.fill: parent

        spacing: 0
        ToolBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 45
            Material.foreground: "white"
            Label{
                anchors.centerIn: parent

                text: "App Updater"

            }
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Pane{
                Material.foreground: "white"
//                anchors.margins: 5
                Material.elevation: 8
                Material.background: Material.primary
                anchors.centerIn: parent
                width: parent.width

                height: parent.height-5


                Connections{
                    target:automationstudio.settings.appUpdater
                    onUpdateStatusChanged:{
                        updatestatus.text=automationstudio.settings.appUpdater.updateStatus;

                    }
                }

                Label{
                    id:updatestatus
                    anchors.centerIn: parent
                    text: "Waiting"
                    font.pixelSize: 20
                }

                Connections{
                    target:automationstudio.settings.appUpdater
                    onDownloadProgressChanged:{
                        progress.value=automationstudio.settings.appUpdater.downloadProgress;

                    }
                }

                Connections{
                    target:automationstudio.settings.appUpdater
                    onCompressingChanged:{
                        progress.indeterminate=automationstudio.settings.appUpdater.compressing

                    }
                }


                ProgressBar{
                    id:progress
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: updatestatus.bottom
                    anchors.topMargin: 5
                    indeterminate: false
                    width: parent.width
                    height: 60
                    value: 0
                }



            }
        }
    }
}
