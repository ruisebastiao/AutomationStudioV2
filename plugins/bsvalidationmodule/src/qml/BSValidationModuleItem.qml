import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import automationmodule 1.0

import bsvalidationmodule 1.0
import guimodule 1.0

BSValidationModule {
    id:bsvalidationmodule
    anchors.fill: parent

    property bool bsOK: false
    property bool bsNOK: false
    property bool waitingResults: false
    property string serialnumber
    property string lefts
    onLeftsChanged: {

        if(lefts=="" || lefts=="?"){
            bsinfo="Dados indisponiveis"
        }
        else{
            bsinfo="Faltam "+lefts+" passagens"
        }
    }

    property string bsinfo: "Dados indisponíveis"
    onBsinfoChanged: {
         console.log("bsinfo:"+bsinfo)
    }


    onNodeAdded: {

        if(node){
            if(node.type===FlowNode.Type.BarcodeReaderNode){
                bsvalidationmodule.serialnumber=Qt.binding(
                            function(){
                                return node.dataout
                            }
                            )


            }
            else if(node.type===FlowNode.Type.BSValidationNode){

                bsvalidationmodule.bsOK=Qt.binding(
                            function(){
                                return node.bsOK
                            }
                            )

                bsvalidationmodule.bsNOK=Qt.binding(
                            function(){
                                return node.bsNOK
                            }
                            )

                bsvalidationmodule.lefts=Qt.binding(
                            function(){
                                return node.lefts
                            }
                            )


            }
            else if(node.type===FlowNode.Type.WebServiceNode){
                bsvalidationmodule.waitingResults=Qt.binding(
                            function(){
                                return node.executing
                            }
                            )
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
            Material.background:  currentcolor

            Layout.fillHeight: true
            Layout.fillWidth: true
            Component.onCompleted: {
                visualitem.currentcolor=Qt.binding(function() {
                    if(bsvalidationmodule.waitingResults){
                        return Material.color(Material.Orange);
                    }
                    if(bsvalidationmodule.bsOK){
                        return Material.color(Material.Green);
                    }
                    if(bsvalidationmodule.bsNOK){
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
                //
                Label{
                    Layout.fillWidth: true;
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredHeight: 80
                    font.pixelSize: 40
                    text: bsvalidationmodule.waitingResults?"Aguarda validação de bs":"Aguarda leitura de BS"
                }
                Label{
                    id:serialnumber
                    Layout.fillWidth: true;
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 40
                    Layout.preferredHeight: 80
                    text: bsvalidationmodule.serialnumber
                }

                Label{
                    visible: bsvalidationmodule.serialnumber!=""
                    Layout.fillWidth: true;
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 40
                    Layout.preferredHeight: 80
                    text: bsvalidationmodule.bsinfo
                }

                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

            }
        }
    }





    onConfigSourceChanged:{

        bsvalidationmodule.load(appDir+configSource);
    }

    AutomationModuleItem{
        id:moduleitem
        anchors.fill: parent
        loadedmodule: parent


    }

}
