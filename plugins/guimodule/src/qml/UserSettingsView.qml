import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.2

import QtGraphicalEffects 1.0

import base 1.0

import automationmodule 1.0

import "qrc:/utils.js" as JSUtils


Item{

    id:root
    clip:true
    visible: automationstudio.systemSettings
    property Settings settings: automationstudio.settings

    //    Connections{
    //        target: settings
    //        onDoUpdate:{
    //            console.log("Updating to release:"+releasename);
    //        }
    //    }


    property User loggedUser:automationstudio.settings&&automationstudio.settings.currentUser


    property SystemSettings system: automationstudio.systemSettings
    Flickable {

        id: userflickable
        visible: root.system

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
                        //                        title:qsTr("User interface")+translator.emptyString
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
                                    text:qsTr("Language")
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

                                }

                                Component.onCompleted: {
                                    currentIndex=Qt.binding(
                                                function(){
                                                    var teste=JSUtils;

                                                    var setindex= JSUtils.arrayObjectIndexOf(combo_language.model,loggedUser.language,"locale");
                                                    return setindex;
                                                }

                                                );
                                    //                                    popup.padding=1

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

                            CheckBox{
                                text: "Use built-in kewyboard"
                                checked: settings&&settings.useKeyboard
                                onCheckedChanged: {
                                    settings.useKeyboard=checked
                                }

                            }

                            Item{
                                Layout.fillWidth: true;
                            }



                        }
                    }



                }

                ColumnLayout{

                    visible: loggedUser&&loggedUser.role==User.AdminRole
                    Layout.fillWidth: true
                    Layout.preferredHeight: 200
                    PaneHeader{
                        id:system_header
                        title: qsTr("System")
                        Layout.preferredHeight:  24
                        Layout.fillWidth: true
                    }

                    GroupBox{

                        Component.onCompleted: {
                            background.width=0
                        }
                        Layout.fillWidth: true
                        Layout.preferredHeight: 250

                        RowLayout{
                            anchors.fill: parent

                            Item{
                                Layout.fillWidth: true;
                                Layout.fillHeight:true;

                                GroupBox{
                                    anchors.fill: parent
                                    anchors.margins: 5
                                    title:  "Info"

                                    //                                    MouseArea{
                                    //                                        id:enterProgrammingmode

                                    //                                        onPressAndHold: {
                                    //                                            stacked_view.push(programmerview);
                                    //                                        }

                                    //                                        anchors.fill: parent


                                    //                                    }

                                    ColumnLayout{

                                        anchors.fill: parent
                                        RowLayout{


                                            TextField{
                                                id:release_field
                                                readOnly: true
                                                Layout.margins: 5
                                                Layout.minimumWidth: 75
                                                Material.accent: selectedprimary
                                                text:automationstudio.releaseVersion
                                                MaterialPlaceHolder{

                                                    placeHolderText:qsTr("Release")
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

                                                RoundButton{
                                                    anchors.centerIn: parent
                                                    width: 50
                                                    height: 50
                                                    highlighted: true
                                                    enabled: automationstudio.settings.checkingUpdate==false

                                                    onPressed: {
                                                        if(automationstudio.settings.updateAvailable){
                                                            window.close()

                                                        }
                                                        else{
                                                            automationstudio.settings.checkUpdate()
                                                        }
                                                    }

                                                    BusyIndicator {
                                                        anchors.fill: parent
                                                        anchors.margins: 5
                                                        running: false
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
                                                        running: false


                                                    }
                                                }
                                            }




                                            Item{
                                                Layout.fillWidth: true
                                                Layout.preferredHeight: 50

                                                Button{
                                                    anchors.centerIn: parent
                                                    highlighted: true
                                                    visible: root.system?root.system.boardInfo=="RPI":false
                                                    text: "Halt"
                                                    onPressed: {

                                                        automationstudio.halt();
                                                    }
                                                }
                                            }
                                        }

                                        RowLayout{

                                            TextField{
                                                id:server_field

                                                Layout.margins: 5
                                                Layout.fillWidth:  true
                                                Material.accent: selectedprimary
                                                text:automationstudio.settings.appUpdater.serverUrl
                                                onAccepted: {
                                                    automationstudio.settings.appUpdater.serverUrl=text
                                                }

                                                MaterialPlaceHolder{

                                                    placeHolderText:qsTr("Server URL")
                                                }

                                            }

                                            Button{
                                                visible: automationstudio.settings.appRegistred===false && automationstudio.settings.socketIO.connected
                                                text: "Register APP"
                                                highlighted: true

                                                onClicked: {
                                                    console.log("Registring app")
                                                    automationstudio.settings.registerApp();
                                                }
                                            }
                                        }
                                        RowLayout{
                                            Layout.fillWidth:  true
                                            TextField{
                                                id:appid_field
                                                readOnly: true
                                                Layout.margins: 5
                                                Layout.fillWidth:  true
                                                //                                                anchors.centerIn: parent
                                                //                                                width: parent.width
                                                Layout.minimumWidth: 75
                                                Material.accent: selectedprimary
                                                text:automationstudio.settings.appID
                                                MaterialPlaceHolder{

                                                    placeHolderText:qsTr("APP ID")
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
                                    title:qsTr("Network")

                                    ColumnLayout{

                                        id: netlayout
                                        //anchors.fill: parent

                                        RowLayout{

                                            TextField{
                                                id:ip_field


                                                readOnly: true
                                                Layout.margins: 5
                                                Layout.minimumWidth: 150
                                                Material.accent: selectedprimary
                                                text:root.system?root.system.localIP:""
                                                MaterialPlaceHolder{

                                                    placeHolderText:qsTr("IP")
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
                                                    editWifi()
                                                }

                                            }
                                        }

                                        RowLayout{

                                            TextField{
                                                id:hostname_field


                                                //                                                readOnly: true
                                                Layout.margins: 5
                                                Layout.fillWidth: true
                                                Material.accent: selectedprimary
                                                text:root.system?root.system.hostname:""

                                                onAccepted: {
                                                    root.system.setNewHostName(hostname_field.text);
                                                }

                                                MaterialPlaceHolder{

                                                    placeHolderText:qsTr("Hostname")
                                                }
                                            }
                                        }
                                    }
                                }
                            }

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

