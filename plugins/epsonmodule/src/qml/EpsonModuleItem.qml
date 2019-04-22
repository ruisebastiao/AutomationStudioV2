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


            RoundButton{
                id:startbt

                anchors.bottom: parent.top
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





        }

        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater{
                id:epsonnodes
                model: epsonNodesProxyModel




                ToolBar {

                    id:status_bar

                    Connections{
                        target: node
                        onCommandReceivedChanged:{
                            var command=commandReceived

                            var command_splitted=command.split("|")

                            if(command_splitted.length>0){



                                if(command_splitted[0]=="STATUS"){

                                    state=command_splitted[1]

                                    status_bar.statusMessage=command_splitted[2]

                                }


                                if(command_splitted[0]=="WAITUSER"){

                                    status_bar.waitUser=true
                                    status_bar.waitUserMessage=command_splitted[1]

                                }


                            }

                        }
                    }



                    Layout.fillWidth: true
                    Layout.preferredHeight: barHeight
                    property int barHeight: status_bar.waitUser?90:45

                    Behavior on barHeight {
                        NumberAnimation {
                            duration:250
                            easing.type: Easing.InOutQuad

                        }
                    }


                    Layout.margins: 3



                    SequentialAnimation{
                        running: state!="NORMAL"
                        loops:Animation.Infinite
                        ColorAnimation {
                            property: "statusColor"
                            target:status_bar

                            to: Material.color(Material.DeepOrange)
                            duration: 500
                        }


                        ColorAnimation {
                            property: "statusColor"
                            target:status_bar

                            to: Material.color(Material.Orange)
                            duration: 500
                        }

                        PauseAnimation {
                            duration: 250
                        }

                    }



                    state: "NORMAL"

                    states: [
                        State {
                            name: "NORMAL"
                            PropertyChanges {
                                target: status_bar
                                statusColor:Material.color(Material.BlueGrey)
                            }
                        },
                        State {
                            name: "WARN"
                            PropertyChanges {
                                target: status_bar
                                statusColor:Material.color(Material.Orange)
                            }
                        },
                        State {
                            name: "ERROR"
                            PropertyChanges {
                                target: status_bar
                                statusColor:Material.color(Material.Red)
                            }
                        },
                        State {
                            name: "WAITUSER"
                            when: status_bar.waitUser
                            PropertyChanges {
                                target: status_bar
                                statusColor:Material.color(Material.Orange)
                                barHeight:90

                            }
                        }


                    ]

//                    Material.foreground: state!="NORMAL"?statusColor:"white"
                    Material.foreground:"white"

                    property color statusColor


                    Behavior on statusColor{

                        ColorAnimation {duration: 400 }
                        enabled: true
                    }

                    property bool waitUser: false

                    //                    Material.primary: statusColor

                    property string statusMessage:""

                    property string waitUserMessage:""


                    Item{

                        anchors.fill: parent


                        RowLayout{

                            anchors.fill: parent
                            Item {

                                id:user_validation
                                property bool show: status_bar.waitUser
                                clip: true
                                Layout.fillHeight: true
                                Layout.preferredWidth:show?height:0



                                RoundButton{
                                    id:valida_bt
                                    onClicked: {
                                        node.sendCommand("WAITUSER|VALIDATED|")
                                        status_bar.waitUser=false
                                        status_bar.state="NORMAL"
                                    }

                                    BusyIndicator {
                                        anchors.fill: parent
                                        Material.accent: Material.Grey
                                        running: user_validation.show
                                    }


                                    Material.accent:status_bar.statusColor

                                    anchors.fill: parent
                                    highlighted: true

                                    contentItem: Text {
                                        text: "Validar"
                                        color: "white"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        elide: Text.ElideRight
                                    }


                                }

                            }

                            Item {
                                Layout.fillWidth: true
                                Layout.fillHeight: true

                                ColumnLayout{
                                    anchors.fill: parent
                                    Item {
                                        Layout.fillWidth: true
                                        Layout.fillHeight: true
                                    }
                                    Label {
                                        id:node_name_lbl
                                        text:node.name
                                        Layout.fillWidth: true


                                        horizontalAlignment:Qt.AlignHCenter
                                    }
                                    TextScroller {
                                        id: stat_text
                                        text:status_bar.waitUser?status_bar.waitUserMessage:status_bar.statusMessage
                                        label.font.capitalization:Font.AllUppercase
                                        horizontalAlignment:Qt.AlignHCenter

                                        Layout.fillWidth: true
                                        Layout.preferredHeight: textHeight
                                    }
                                    Item {
                                        Layout.fillWidth: true
                                        Layout.fillHeight: true
                                    }
                                }


                            }


                        }

                    }
                }

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
