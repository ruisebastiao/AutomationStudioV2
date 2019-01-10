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

    onProductionRunningChanged: {
        productionStarting=false
        productionStopping=false
    }

    RowLayout{
        parent:moduleitem.mainpagecontainer
        anchors.fill: parent
        anchors.margins: 5
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

        }
    }
    RoundButton{
        highlighted: true
        width:100
        height: width
        enabled: root.productionStarting==false && root.productionStopping==false


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
            running: root.productionStarting || root.productionStopping
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
