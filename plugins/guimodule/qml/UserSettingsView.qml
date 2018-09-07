import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.2

import QtGraphicalEffects 1.0

import base 1.0

Item{

    id:root
    clip:true
    Flickable {
        id: userflickable

        anchors.fill: parent
        //    contentWidth: parent.width

        contentHeight: pane.height
        //    interactive: true//contentHeight > height
        //    flickableDirection: Flickable.VerticalFlick




        Pane{
            id:pane
            //        anchors.fill: parent
            width: userflickable.width
            height: userflickable.height*1.25

            Material.elevation:6
            anchors.margins: 2
            padding: 1
            clip: true





            ColumnLayout{
                id:container
                anchors.fill: parent

                ColumnLayout{
                    Layout.fillWidth: true
                    PaneHeader{
                        id:app_header
                        title:qsTr("User interface")+translator.emptyString
                        Layout.preferredHeight: 24
                        Layout.fillWidth: true
                    }

                    GroupBox{


                        Component.onCompleted: {
                            background.width=0
                        }


                        Layout.fillWidth: true

                        RowLayout{
                            anchors.fill: parent

                            Item{
                                Layout.fillWidth: true;
                            }


                            ComboBox{

                                id:combo_language
                                Label{
                                    text:qsTr("Language")+translator.emptyString
                                    y:-10
                                    font.pixelSize: 12
                                    color: "gray"
                                }

                                font.pixelSize: 15
                                Layout.minimumWidth: 140
                                Layout.fillHeight: false
                                Layout.preferredHeight: 48

                                textRole: "text"

                                popup.onClosed: {

                                    if(currentIndex>=0){
                                        var lang=combo_language.model[combo_language.currentIndex].locale;
                                        loggedUser.language=lang;
                                    }


                                }

                                popup.onOpened: {
                                    //appsettings.addUser()

                                }

                                Component.onCompleted: {
                                    currentIndex=Qt.binding(
                                                function(){
                                                    var setindex= Utils.arrayObjectIndexOf(combo_language.model,loggedUser.language,"locale");
                                                    return setindex;
                                                }

                                                );
                                    popup.padding=1

                                }




                                contentItem:ColumnLayout{
                                    Item{
                                        Layout.preferredHeight: parent.height-12
                                        Layout.preferredWidth: parent.width


                                        LanguageItem{


                                            anchors.fill: parent
                                            id:current_language
                                            visible: true;
                                            animate: true
                                            model: combo_language.model[combo_language.currentIndex]

                                        }



                                    }
                                }


                                delegate: ItemDelegate {
                                    //text: modelData

                                    width: parent?parent.width:0
                                    contentItem:

                                        LanguageItem{

                                        height: parent.height+12
                                        width: parent.width

                                        clip:false
                                        model: modelData

                                    }



                                }



                                Material.accent: selectedprimary
                                model: [
                                    {text:"Portugês",flag:"qrc:/images/portugal_round_icon_64.png",locale:"pt_PT"},
                                    {text:"English",flag:"qrc:/images/united_kingdom_round_icon_64.png",locale:"en_GB"},
                                    {text:"Français",flag:"qrc:/images/france_round_icon_64.png",locale:"fr_FR"},
                                    {text:"Español",flag:"qrc:/images/spain_round_icon_64.png",locale:"es_ES"}
                                ]

                            }
                            Item{
                                Layout.fillWidth: true;
                            }



                        }
                    }



                }

                ColumnLayout{

                    visible: loggedUser.role==User.AdminRole
                    Layout.fillWidth: true
                    Layout.preferredHeight: 200
                    PaneHeader{
                        id:system_header
                        title: qsTr("System")+translator.emptyString
                        Layout.preferredHeight:  24
                        Layout.fillWidth: true
                    }

                    GroupBox{

                        Component.onCompleted: {
                            background.width=0
                        }
                        Layout.fillWidth: true
                        Layout.preferredHeight: 150

                        RowLayout{
                            anchors.fill: parent

                            Item{
                                Layout.fillWidth: true;
                                Layout.fillHeight:true;

                                GroupBox{
                                    anchors.fill: parent
                                    anchors.margins: 5
                                    title:  "Info"

                                    MouseArea{
                                        id:enterProgrammingmode

                                        onPressAndHold: {
                                            stacked_view.push(programmerview);
                                        }

                                        anchors.fill: parent


                                    }

                                    RowLayout{


                                        TextField{
                                            id:release_field
                                            readOnly: true
                                            Layout.margins: 5
                                            Layout.minimumWidth: 75
                                            Material.accent: selectedprimary
                                            text:appsettings.releaseVersion?appsettings.releaseVersion:"unknown"
                                            MaterialPlaceHolder{

                                                placeHolderText:qsTr("Release")+translator.emptyString
                                            }

                                        }
                                        Item{

                                            Layout.fillHeight: true
                                            Layout.preferredWidth: 50
                                            //                                            Layout.rightMargin: 5
                                            //                                            visible: opacity>0
                                            //                                            Behavior on opacity{
                                            //                                                NumberAnimation { duration: 250}
                                            //                                            }
                                            //                                            opacity:appsettings.updateAvailable?1:0
                                            RoundButton{
                                                anchors.centerIn: parent
                                                width: 50
                                                height: 50
                                                highlighted: true
                                                enabled: appsettings.checkingUpdate==false

                                                onPressed: {
                                                    if(appsettings.updateAvailable){
                                                        window.close()

                                                    }
                                                    else{
                                                        appsettings.checkUpdate()
                                                    }
                                                }

                                                BusyIndicator {
                                                    anchors.fill: parent
                                                    anchors.margins: 5
                                                    running: appsettings.checkingUpdate?appsettings.checkingUpdate:false
                                                    //                                                    Material.accent: "#ffb47b"
                                                }

                                                Item{

                                                    id:icon_container

                                                    anchors.centerIn: parent
                                                    width: 35
                                                    height: 35
                                                    clip: true
                                                    Image {
                                                        id:update_icon
                                                        x:width/2
                                                        anchors.horizontalCenter: parent.horizontalCenter

                                                        y:icon_container.height/2-width/2
                                                        width: 22
                                                        height: 22
                                                        source: "qrc:/images/ic_arrow_upward_white_36dp_2x.png"
                                                    }

                                                }
                                                SequentialAnimation{
                                                    PauseAnimation {
                                                        duration: 1500
                                                    }
                                                    NumberAnimation { target: update_icon; property: "y"; to: -icon_container.height-2; duration: 250 }
                                                    PauseAnimation {
                                                        duration: 50
                                                    }
                                                    NumberAnimation { target: update_icon; property: "y"; from:icon_container.height+2; to: icon_container.height/2-update_icon.width/2; duration: 250 }
                                                    loops: Animation.Infinite
                                                    running: appsettings.updateAvailable?appsettings.updateAvailable:false

                                                }
                                            }
                                        }






                                    }
                                }
                            }

                            Item{
                                Layout.fillWidth: true;
                                Layout.fillHeight:true;

                                GroupBox{
                                    anchors.fill: parent
                                    anchors.margins: 5
                                    title:qsTr("Network")+translator.emptyString

                                    RowLayout{
                                        anchors.fill: parent
                                        TextField{
                                            id:ip_field
                                            property SystemSettings system: appsettings.systemSettings
                                            readOnly: true
                                            Layout.margins: 5
                                            Layout.minimumWidth: 150
                                            Material.accent: selectedprimary
                                            text:system.localIP
                                            MaterialPlaceHolder{

                                                placeHolderText:qsTr("IP")+translator.emptyString
                                            }
                                        }
                                        RoundButton{
                                            id:set_wifi_bt
                                            Layout.preferredHeight: 56
                                            Layout.preferredWidth: 56
                                            highlighted: true
                                            Image{
                                                //                                                anchors.horizontalCenter: parent.horizontalCenter
                                                anchors.centerIn: parent
                                                //                                                anchors.topMargin: 8
                                                width: 36
                                                height: 36
                                                source: "qrc:/images/1496586297_wifi_Logo.png"

                                            }
                                            onClicked:  {

                                                console.log("pressed")
                                                stacked_view.push(editwifi_component);
                                            }

                                        }
                                    }
                                }
                            }

                            //                            Item{
                            //                                Layout.fillWidth: true;
                            //                            }
                        }
                    }
                }

                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                }
            }

        }

        ScrollBar.vertical: ScrollBar { }
    }
    Component{
        id:manageusers

        Item{

        }

        //        EditUsersView{
        //            state: "editusers"
        //            property string title: qsTr("Edit Users")+translator.emptyString
        //        }
    }

    Component{
        id:programmerview


        Item{

        }

        //        ProgrammerView{
        //            //id:usersettings
        //            state:"programmingview"
        //        }
    }


}

