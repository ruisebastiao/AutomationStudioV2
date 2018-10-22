import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import automationmodule 1.0

import bsvalidationmodule 1.0
import guimodule 1.0

BSValidationModule {
    id:root
    anchors.fill: parent


    property string status: "Dados indisponíveis"


    onLeftsChanged: {

        if(lefts=="" || lefts=="?"){
            status="Dados indisponiveis"
        }
        else{
            if(lefts.indexOf("Invalid")>=0){
                status=lefts
            }
            else{
                status="Faltam "+lefts+" passagens"
            }


        }
    }




    RowLayout{
        parent:moduleitem.mainpagecontainer
        anchors.fill: parent
        anchors.margins: 5

        Button{
            enabled: true
            id:visualitem
            property color currentcolor: Material.primary

            Behavior on currentcolor{
                ColorAnimation {duration: 400 }
            }

            Material.background:  currentcolor

            Layout.fillHeight: true
            Layout.fillWidth: true
            Component.onCompleted: {
                visualitem.currentcolor=Qt.binding(function() {
                    if(root.waitingResponse){
                        return Material.color(Material.Orange);
                    }
                    if(root.bsOK){
                        return Material.color(Material.Green);
                    }
                    if(root.bsNOK && root.serverErrorStatus==""){
                        return Material.color(Material.Red,Material.Shade400);
                    }
                    return "white"
                })

            }

            ColumnLayout{
                spacing: 10
                visible: true
                anchors.fill: parent
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
                Label{
                    Layout.fillWidth: true;
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredHeight: 80
                    font.pixelSize: 40
                    text: root.waitingResponse?"Aguarda validação de bs":"Aguarda leitura de BS"
                    fontSizeMode:Text.HorizontalFit
                    minimumPointSize:20
                }
                Label{
                    id:serialnumber
                    Layout.fillWidth: true;
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 40
                    Layout.preferredHeight: 80
                    text: root.serialnumber
                    fontSizeMode:Text.HorizontalFit
                    minimumPointSize:12
                }

                Label{
                    visible: root.serialnumber!="" && root.serverErrorStatus==""
                    Layout.fillWidth: true;
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 40
                    Layout.preferredHeight: 80
                    text: root.status
                    fontSizeMode:Text.HorizontalFit
                    minimumPointSize:12
                }
                RowLayout{
                    Layout.fillWidth: true;
                    visible: root.serverErrorStatus!=""
                    Layout.alignment: Qt.AlignHCenter
                    Label{
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 40
                        Material.foreground: Material.Red
                        Layout.preferredHeight: 80
                        text: "Erro de Servidor:"
                        fontSizeMode:Text.HorizontalFit
                        minimumPointSize:12
                    }
                    Label{

                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 40
                        Material.foreground: Material.Red
                        Layout.preferredHeight: 80
                        text: root.serverErrorStatus
                        fontSizeMode:Text.HorizontalFit
                        minimumPointSize:12
                    }

                }





                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

            }
        }
    }





//    onConfigSourceChanged:{

//        root.load();
//    }

    AutomationModuleItem{
        id:moduleitem
        anchors.fill: parent
        loadedmodule: parent


    }

}
