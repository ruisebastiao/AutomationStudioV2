import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import automationmodule 1.0
import epsonmodule 1.0

import QuickQanava 2.0 as Qan
import guimodule 1.0

EpsonModule {
    id:root
    anchors.fill: parent


    property bool productionStarting:false
    property bool productionStopping:false



//    property bool toolInDock: false


    onProductionRunningChanged: {
        productionStarting=false
        productionStopping=false
    }

    ColumnLayout{
        parent:moduleitem.mainpagecontainer
        anchors.fill: parent
        anchors.margins: 5
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

        }
        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true
            ToolBar {

                Layout.fillWidth: true
                Layout.preferredHeight: 45
                Layout.margins: 3
                Material.foreground: "white"

                TextScroller {
                    id: c4stat
                    anchors.fill: parent
                    text:"C4 Not Connected"
                    label.font.capitalization:Font.AllUppercase
                    horizontalAlignment:Qt.AlignHCenter
                }
            }
            ToolBar {

                Layout.fillWidth: true
                Layout.preferredHeight: 45
                Layout.margins: 3
                Material.foreground: "white"

                TextScroller {
                    anchors.fill: parent
                    id: rs4stat
                    label.font.capitalization:Font.AllUppercase
                    horizontalAlignment:Qt.AlignHCenter
                    text:"RS4 Not Connected"
                }
            }
        }


    }
    RoundButton{
        id:startbt

        Component.onCompleted: {
            enabled=Qt.binding(function(){
//              if(root.stationReady && root.productionStarting==false && root.productionStopping==false){
//                     && (root.productionRunning==false && root.toolInDock==false)
//              }

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
                root.productionStarting=true
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
