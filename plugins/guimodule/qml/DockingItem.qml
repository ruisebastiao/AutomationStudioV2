import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0

Pane{
    id:root
    Material.elevation:8

    property QAutomationModule loadedmodule

    onLoadedmoduleChanged: {
        if(loadedmodule){
            loadedmodule.parent=modulecontainer
        }
    }

    property User loggedUser


    property var dockContainer

    opacity: 1




    Drag.active: dragArea.drag.active

    Drag.hotSpot.x: dragArea.mouseX
    Drag.hotSpot.y: dragArea.mouseY


    padding: 1
    ColumnLayout{
        anchors.fill: parent

        spacing: 0
        ToolBar {
            id:header
            Layout.fillWidth: true
            Layout.preferredHeight: 45
            Layout.margins: 3
            Material.foreground: "white"

            RowLayout{
                anchors.fill: parent
                z: 999
                RoundButton{
                    visible: loggedUser.role==User.AdminRole
                    highlighted: true
                    Material.background: Material.primary
                    Layout.preferredHeight: 48
                    Layout.preferredWidth: 48
                    Image{
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectFit
                        width: 30
                        height: 30
                        source:loadedmodule.editMode===false?"qrc:/images/pencil.png":"qrc:/images/arrow-left.png"
                    }


                    onClicked: {
                        loadedmodule.editMode=!loadedmodule.editMode
                    }

                }

                Label{
                    Layout.fillWidth: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 18
                    text:name
                }
                RoundButton{
                    visible: loadedmodule.editMode
                    highlighted: true
                    Material.background: Material.primary
                    Layout.preferredHeight: 48
                    Layout.preferredWidth: 48
                    Image{
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectFit
                        width: 24
                        height: 24
                        source:"qrc:/images/content-save.png"
                    }


                    onClicked: {

                        loadedmodule.save();
                    }

                }

            }



            MouseArea {
                id: dragArea
                anchors.fill: parent

                drag.target: root

                //                onPressAndHold: rect2.state="docking"
                onPressed: {
                    //rect2.beginDrag = Qt.point(rect2.x, rect2.y);
                }
                onReleased: {
                    //                    if(!rect.caught) {
                    //                        backAnimX.from = rect.x;
                    //                        backAnimX.to = beginDrag.x;
                    //                        backAnimY.from = rect.y;
                    //                        backAnimY.to = beginDrag.y;
                    //                        backAnim.start()
                    //                    }
                }
            }



        }

        RectangularGlow{
            Layout.fillWidth: true
            color: "gray"
            glowRadius: 1
            spread: 0
            Layout.preferredHeight: 2
        }

        Item{
            id:modulecontainer

            Layout.fillHeight: true
            Layout.fillWidth: true






        }


    }



    states: [
        State {
            when: dragArea.drag.active
            name: "docking"
            ParentChange { target: root; parent: dockContainer;}
            PropertyChanges {
                target: root
                scale:0.98

            }

        }

    ]


}
