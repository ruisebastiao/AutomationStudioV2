import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import automationmodule 1.0
import epsonmodule 1.0
import SortFilterProxyModel 1.0
import QuickQanava 2.0 as Qan
import guimodule 1.0

EpsonModule {
    id:root
    anchors.fill: parent



    property string stationStatusMessage:"Not connected"


    property bool productionStopping:false

    property bool toolError: !root.productionRunning && root.toolInDock
    onToolErrorChanged: {
        if(toolError){

            root.stationStatusMessage="Remove tool from dock"

        }
        else{
            // Check this
            root.stationStatusMessage="Ready"

        }
    }

    onProductionRunningChanged: {

        productionStopping=false
        if(productionRunning==false ){
            if(toolError==false)
                stationStatusMessage="Production stopped"
        }
        else{
            stationStatusMessage="Production running"
        }



    }

    onStationReadyChanged:{
        if(stationReady==false){

            productionStopping=false
            stationStatusMessage="Station not ready"

        }
    }



    SortFilterProxyModel {
        id: epsonNodesProxyModel


        sourceModel:root.flowNodes




        filters: [
            ValueFilter {
                enabled: true


                roleName: "nodeTypeRole"



                value: FlowNode.EpsonNode

            }
        ]

    }


    ColumnLayout{
        parent:moduleitem.mainpagecontainer
        anchors.fill: parent
        anchors.margins: 5
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Item {
                id:user_validation
                property bool show: false
                visible: opacity!=0
                opacity: show?1:0
                anchors.centerIn: parent
                width: 300
                height: 300
                RoundButton{
                    anchors.centerIn: parent
                    width: 200
                    height: 200
                    highlighted: true

                    contentItem: Text {
                        text: "Validar"
                        font: control.font
//                        opacity: enabled ? 1.0 : 0.3
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }
                }
            }


        }
        ToolBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 45
            Layout.margins: 3
            Material.foreground: "white"

            TextScroller {
                id:stationStat
                anchors.fill:parent
                text:stationStatusMessage
                label.font.capitalization:Font.AllUppercase
                horizontalAlignment:Qt.AlignHCenter
                verticalAlignment:Qt.AlignVCenter

            }

        }

        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater{
                id:epsonnodes
                model: epsonNodesProxyModel




                ToolBar {



                    Connections{
                        target: node
                        onCommandReceivedChanged:{
                            var command=commandReceived

                            var pos=command.indexOf("STATUS|")
                            if(pos>=0){
                                stat_text.text=command.split("|")[1]
                            }



                        }
                    }

                    Layout.fillWidth: true
                    Layout.preferredHeight: 45
                    Layout.margins: 3
                    Material.foreground: "white"

                    RowLayout{
                        anchors.fill: parent
                        TextScroller {

                            Layout.fillWidth: true
                            text:node.name+" - "
                            label.font.capitalization:Font.AllUppercase
                            horizontalAlignment:Qt.AlignRight
                        }
                        TextScroller {
                            id: stat_text
                            Layout.fillWidth: true

                            text:"Not connected"
                            label.font.capitalization:Font.AllUppercase
                            horizontalAlignment:Qt.AlignLeft
                        }
                    }


                }

            }

        }


    }


    onWaitUserValidationChanged:{

        console.log("onWaitUserValidationChanged")
        if(waitUserValidation){
            user_validation.show=true;
        }
    }



    RoundButton{
        id:startbt

        Component.onCompleted: {
            enabled=Qt.binding(function(){
                if(!root.stationReady || root.productionStarting || root.productionStopping){
                    return false
                }

                if(!root.productionRunning && root.toolInDock){
                    return false
                }



                return true
            })
        }

        highlighted: true
        width:100

        height: width


        onEnabledChanged: {
            if(enabled){

            }
        }

        z:999999

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Image {
            anchors.centerIn: parent
            width: parent.width*0.5
            height: width
            source: root.productionRunning?"qrc:/images/baseline_stop_white_48dp.png":"qrc:/images/baseline_play_arrow_white_48dp.png"
        }
        BusyIndicator {
            id:loadingindicator
            running: (root.productionStarting || root.productionStopping) && root.stationReady
            anchors.centerIn: parent
            width: parent.width-5
            height: parent.height-5
        }

        onClicked: {
            if(root.productionRunning){
                root.stopProduction=true
                root.productionStopping=true
            }
            else{
                root.startProduction=true

            }
        }
    }




    AutomationModuleItem{
        id:moduleitem
        anchors.fill: parent
        loadedmodule: parent


        graph:EpsonGraph {
            id: dataflowGraph

            portDelegate: Component {

                FlowNodePortItem{

                }
            }


            selectionPolicy :Qan.Graph.SelectOnClick
            connectorCreateDefaultEdge: false
            objectName: "graph"
            anchors.fill: parent
            clip: true
            connectorEnabled: true
            selectionColor: Material.accent
            connectorColor: Material.accent
            connectorEdgeColor: Material.accent


            Component.onCompleted: {

                defaultEdgeStyle.lineType = Qan.EdgeStyle.Curved




            }




        }



    }



}
