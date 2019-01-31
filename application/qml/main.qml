import QtQuick 2.10
//import QtQuick.Window 2.10
import QtQuick.VirtualKeyboard 2.3
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls 2.4

import QtQuick.Controls.Material 2.1
//import Qt.labs.platform 1.0

import QtGraphicalEffects 1.0

import QtQuick.VirtualKeyboard 2.1

import base 1.0
import guimodule 1.0 as GUI
import automationmodule 1.0

import QuickQanava 2.0 as Qan



ApplicationWindow {
    id: rootwindow
    visible: true
    //    width: 640
    //    height: 480
    title: qsTr("Automation Studio")
    
    property string mainState: "home"
    onMainStateChanged: {
        console.log(mainState);
    }


    signal toastMessage(string message);

    signal editWifi();

    onEditWifi: {
        stacked_view.push(configWifiLoader.item);
    }

    property Settings settings: automationstudio.settings

    Connections{
        target: settings
        onDoUpdate:{
            console.log("Updating to release:"+releasename);
        }
    }
    property bool projectEditMode: false

    property Utilities utilities

    property User loggedUser:settings&&settings.currentUser

    readonly property Project currentProject:settings&&settings.selectedProject

    onCurrentProjectChanged: {
        if(currentProject){

            if(currentProject.modules.rowCount(null)<1 && loggedUser&&loggedUser.role===User.AdminRole){
                projectEditMode=true
            }
        }
    }


    GUI.ToastManager{
        id:toast_manager
        anchors.fill: parent


        Connections {
            target: rootwindow
            onToastMessage:{
                toast_manager.addMessage(message)
            }

        }


    }

    
    visibility: "Maximized"
    //    flags: Qt.Window |Qt.FramelessWindowHint
    
    property int selectedTheme:Material.Light
    property color selectedprimary:Material.color(Material.BlueGrey);
    Behavior on selectedprimary{
        id:selectedprimary_Behavior
        ColorAnimation {duration: 400 }
        enabled: true
    }
    
    property color selectedaccent:Material.color(Material.DeepOrange);
    Behavior on selectedaccent{
        
        ColorAnimation {duration: 400 }
        enabled: true
    }
    

    
    Material.theme: selectedTheme
    Material.primary: selectedprimary
    Material.accent:selectedaccent
    
    
    property int selectionAnimationTime: 400
    property int mainStateAnimationTime: 350
    







    onLoggedUserChanged: {
        if(loggedUser){
            console.log("User role:"+loggedUser.role+" pass:"+Qt.btoa(loggedUser.pin));
        }
    }
    
    onSettingsChanged:  {
        if(settings){
            settings.loadBaseSettings()
            stacked_view.push(maincontentview)
            settings.initSocketIO();
        }
    }
    

    Component.onCompleted: {
        settings=automationstudio.settings;
        //var teste=automationstudio.utilites.resourceExists("");
        utilities=automationstudio.utilities;
        console.log("Checking settings")


        var hasnetworkmanager=utilities.resourceExists(":/NetworkManager/");
        if(hasnetworkmanager){
            wifiloader.source="qrc:///NetworkManager/NetworkManagerItem.qml";
            wifilevel_loader.source="qrc:///NetworkManager/WifiLevelItem.qml";
            configWifiLoader.source="qrc:///NetworkManager/ConfigWifiItem.qml"
        }


    }
    

    Connections{
        target: wifiloader.item
        onWifiStatusChanged:{
            console.log("wifistatus:"+wifiStatus)
        }

        onConnectedNetworkChanged:{
            //
            console.log("connectedchanged:"+connectedNetwork)
            wifilevel_loader.item.network= wifiloader.item.connectedNetwork
        }
    }

    Loader{
        id:wifiloader
    }

    Loader{
        id:configWifiLoader
        onLoaded: {
            item.networkmanager=wifiloader.item
        }

    }




    
    Flickable{
        id:mainflickable
        objectName: "mainflickable"
        anchors.fill: parent
        interactive: false
        flickableDirection: Flickable.VerticalFlick
        Drawer {
            id: drawer
            width: Math.min(rootwindow.width, rootwindow.height) / 2.5
            height: rootwindow.height
            dragMargin: 1
            onPositionChanged: {
                if(position==0){
                    login_container.opened=false
                }
            }



            ColumnLayout{
                anchors.fill: parent

                spacing: 0
                ToolBar {
                    z:1
                    id:drawer_toolbar
                    Material.foreground: "white"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 90

                    RowLayout{
                        anchors.fill: parent
                        RoundButton{
                            Layout.preferredHeight: 70
                            Layout.preferredWidth: 70
                            Image {
                                anchors.fill: parent
                                fillMode: Image.Pad
                                source: "qrc:/images/ic_person_white_36dp_1x.png"
                            }
                            //                        text: "res"
                            //icon.source:"qrc:/images/ic_person_white_36dp_1x.png"
                            highlighted: true
                            Material.background: Material.primary
                            onPressed: {

                                login_container.opened=!login_container.opened
                            }




                        }
                        Item {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Label{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                text:loggedUser?loggedUser.name:""
                            }
                        }
                    }


                }
                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Item{
                        id:login_container
                        z:1
                        width: drawer_toolbar.width
                        height: 150
                        property bool opened: false
                        //                    color: "red"
                        x:0
                        y:opened?-4:-height

                        Behavior on y{
                            NumberAnimation {
                                duration: 500
                                easing.type: Easing.InOutQuart;
                            }
                        }


                        Rectangle{
                            anchors.fill: parent
                            anchors.margins: 0
                            color: Material.primary
                            radius: 2
                            ListView{
                                Material.foreground: "white"
                                id:usersList
                                model:settings&&settings.users
                                onModelChanged: {
                                    console.log("Users model changed");
                                }

                                anchors.topMargin: 8
                                anchors.fill: parent
                                focus: true
                                //                        clip: true
                                currentIndex: -1


                                delegate: ItemDelegate {
                                    width: parent.width
                                    text: model.name
                                    highlighted: ListView.isCurrentItem
                                    onClicked: {
                                        loginpopup.selectedUser=model.user
                                        if(model.user.role!=User.AdminRole){
                                            automationstudio.settings.currentUser=model.user
                                        }
                                        else{
                                            loginpopup.open()

                                        }

                                    }
                                }

                                //                     model:basesettings.modules

                                ScrollIndicator.vertical: ScrollIndicator { }
                            }
                        }
                    }

                    ColumnLayout{
                        anchors.fill: parent


                        ToolBar {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 48
                            Material.foreground: "white"
                            Label{
                                anchors.fill: parent
                                verticalAlignment: Text.AlignVCenter

                                horizontalAlignment: Text.AlignHCenter

                                text: "Projects List"
                            }
                            RoundButton{
                                width: 48
                                height: width
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                onClicked: {

                                    settings.projects.createNewProject()
                                }
                            }
                        }

                        ListView {
                            id: projectslist
                            //                            enabled: !currentProject || currentProject && currentProject.projectLocked==false
                            model:settings && settings.projects

                            property Project selectedProject//: model&&model.at(projectslist.currentIndex)

                            onModelChanged: {
                                if(settings){
                                    //                                    currentIndex=settings.projects.indexOf(currentProject);

                                }


                            }
                            //                            enabled: currentProject&&currentProject.projectLocked==false
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            focus: true
                            clip: true
                            currentIndex: -1
                            onCurrentIndexChanged:{
                                var project=null

                                if(model){
                                    project=model.at(projectslist.currentIndex)
                                    if(project.subProjects.length==0){
                                        projectslist.selectedProject=project
                                    }
                                }
                            }



                            delegate: ItemDelegate {
                                id:projectdelegate
                                property Project itemProject: model.project


                                property bool isExpanded:false

                                property bool isCurrentItem: ListView.isCurrentItem
                                onIsCurrentItemChanged: {
                                    if(isCurrentItem){
                                        isExpanded=true
                                    }
                                    else{
                                        isExpanded=false
                                    }
                                }

                                width: projectslist.width
                                height: delegateContent.childrenRect.height+10

                                anchors.margins: 0
                                padding: 0

                                onClicked: {
                                    projectslist.currentIndex = index

                                }

                                highlighted: ListView.isCurrentItem && model.project.subProjects.length==0

                                Rectangle {
                                    color: Material.accent
                                    anchors.fill: parent
                                    opacity: 0.5
                                    visible: model && model.project.subProjects.length==0 && rootwindow.currentProject == model.project
                                }

                                Menu {
                                    id: subproject_context
                                    x:0
                                    //                                    width: parent.width
                                    y:parent.height

                                    MenuItem{
                                        enabled: true
                                        text: "Add sub project"
                                        onClicked: {
                                            model.project.addSubProject()
                                        }
                                    }


                                }

                                contentItem: Column {
                                    id:delegateContent
                                    width: parent.width




                                    Label{
                                        width: parent.width
                                        height: 20
                                        horizontalAlignment:Text.AlignHCenter
                                        verticalAlignment:Text.AlignVCenter
                                        text: model.name

                                    }
                                    ListView{
                                        id:subprojectslist
                                        clip: true

                                        property int projectListIndex: projectslist.currentIndex
                                        onProjectListIndexChanged: {
                                            currentIndex=-1
                                        }

                                        height: projectdelegate.isExpanded?childrenRect.height:0
                                        Behavior on height {
                                            NumberAnimation {
                                                duration: mainStateAnimationTime/2
                                                easing.type: Easing.InOutQuad

                                            }
                                        }




                                        opacity: height/childrenRect.height
                                        width: projectslist.width
                                        model: itemProject?itemProject.subProjects:null

                                        currentIndex: -1
                                        onModelChanged: {
                                            //                                            if(model){
                                            //                                                currentIndex=itemProject.subProjects.indexOf(currentProject);

                                            //                                            }

                                        }

                                        //                                        highlight: Rectangle{
                                        //                                            color: Material.accent
                                        //                                            opacity: 0.5

                                        //                                        }


                                        delegate: ItemDelegate{
                                            id:subprojectdelegate
                                            width:parent.width;
                                            height: 40
                                            text: modelData



                                            Rectangle {
                                                color: Material.accent
                                                anchors.fill: parent
                                                opacity: 0.5
                                                visible: rootwindow.currentProject&&rootwindow.currentProject.subProjectName==modelData
                                            }


                                            onClicked: {
                                                subprojectslist.currentIndex=itemProject.subProjects.indexOf(modelData)
                                                itemProject.subProjectName=modelData;
                                                if(projectslist.model){
                                                    var project=projectslist.model.at(projectslist.currentIndex)
                                                    projectslist.selectedProject=project

                                                }
                                            }


                                            highlighted: ListView.isCurrentItem



                                        }


                                    }


                                }





                            }

                            //                     model:basesettings.modules

                            ScrollIndicator.vertical: ScrollIndicator { }
                            footer: ColumnLayout{
                                width:  projectslist.width
                                height: 42
                                ToolBar{
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    RowLayout{

                                        anchors.fill: parent
                                        Layout.margins: 10
                                        Item {

                                            Layout.fillWidth: true
                                            Layout.fillHeight: true

                                        }


                                        Button{
                                            Layout.fillHeight: true
                                            highlighted: true
                                            property bool openProject: projectslist.selectedProject!=rootwindow.currentProject
                                            text:openProject || !projectslist.selectedProject?"Open":"Close"
                                            enabled: projectslist.selectedProject
                                            onClicked: {

                                                if(openProject==false){
                                                    if(settings.selectedProject){
                                                        settings.selectedProject=null
                                                    }

                                                }
                                                else if(projectslist.selectedProject){
                                                    //                                                    rootwindow.currentProject=projectslist.selectedProject
                                                    settings.selectedProject=projectslist.selectedProject
                                                }

                                                //settings.projects.l
                                            }
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
                    RoundButton{
                        id:fab
                        width: 64
                        visible:  automationstudio.reboot?true:false
                        height: 64
                        highlighted: true
                        icon.source: "qrc:/images/if_refresh_926645.png"
                        z:9999
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        Material.accent: Material.primary
                        onClicked: {
                            automationstudio.reboot();
                        }

                    }
                }
            }
        }


        ColumnLayout{
            anchors.fill: parent

            spacing: 0
            ToolBar {
                id:header
                Layout.fillWidth: true
                Layout.preferredHeight: 45

                Material.foreground: "white"

                RowLayout{
                    //

                    anchors.fill: parent
                    Item{
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true


                        id:title_container

                        RowLayout{

                            anchors.fill: parent
                            //                            anchors.leftMargin: mainState=="wizard"?10:0
                            spacing: 3
                            Item{
                                visible:settings&& settings.currentUser
                                id:drawer_container_layout
                                Layout.preferredHeight: 48
                                Layout.preferredWidth: 48
                                clip: true
                                Behavior on Layout.preferredWidth{
                                    NumberAnimation {
                                        duration: mainStateAnimationTime/2
                                        easing.type: Easing.InOutQuad

                                    }

                                }

                                RoundButton {

                                    id:top_button
                                    property int customPos: 0


                                    Behavior on customPos{
                                        NumberAnimation {
                                            duration: mainStateAnimationTime/2
                                            easing.type: Easing.InOutQuad

                                        }

                                    }

                                    x: customPos


                                    anchors.verticalCenter: parent.verticalCenter
                                    flat: true

                                    visible: true;
                                    clip: true


                                    states: [
                                        State {
                                            name: "home"
                                            when: mainState=="home"
                                            PropertyChanges { target: drawer_button; x: 8}


                                        },

                                        State {
                                            name: "back"
                                            when: mainState!="home"
                                            PropertyChanges { target: drawer_button; x: -width-8}
                                            PropertyChanges { target: back_button; x: 8}

                                        }
                                    ]

                                    Image {
                                        id:drawer_button
                                        fillMode: Image.Pad
                                        anchors.verticalCenter: parent.verticalCenter
                                        height: 32
                                        width: 32

                                        anchors.margins: 0
                                        horizontalAlignment: Image.AlignHCenter
                                        verticalAlignment: Image.AlignVCenter
                                        source:"qrc:/images/menu.png"
                                        Behavior on x{
                                            NumberAnimation  {

                                                duration: mainStateAnimationTime
                                                easing.type: Easing.InOutQuad

                                            }

                                        }


                                    }
                                    Image {

                                        id:back_button
                                        x:parent.width+8
                                        anchors.verticalCenter: parent.verticalCenter
                                        height:32
                                        width: 32
                                        fillMode: Image.PreserveAspectCrop
                                        anchors.margins: 2
                                        horizontalAlignment: Image.AlignHCenter
                                        verticalAlignment: Image.AlignVCenter

                                        source:"qrc:/images/ic_arrow_back_white_48dp_2x.png"

                                        Behavior on x{
                                            NumberAnimation  {

                                                duration: mainStateAnimationTime
                                                easing.type: Easing.InOutQuad

                                            }

                                        }




                                    }



                                    onClicked:{
                                        if(mainState=="home"){
                                            drawer.open();

                                        }
                                        else{
                                            stacked_view.pop();


                                        }
                                    }
                                }
                            }
                            Item{
                                Layout.fillHeight: true
                                Layout.fillWidth: true



                                GUI.TextScroller {
                                    id: titleLabel

                                    anchors.fill: parent
                                    Component.onCompleted: {
                                        text=Qt.binding(function(){

                                            if(stacked_view.currentItem){
                                                if(mainState=="home"){
                                                    if(loggedUser) {
                                                        console.log("loggedUser.name:"+loggedUser.name)
                                                        return loggedUser.name
                                                    }
                                                    return "Novares"
                                                }
                                                return stacked_view.currentItem.title
                                            }
                                            return "Novares"

                                        })
                                    }

                                    duration: mainStateAnimationTime
                                    font.pixelSize: 20
                                    horizontalAlignment:Text.AlignLeft




                                }





                            }
                        }



                    }



                    Item{

                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true
                        Layout.margins:0
                        id:central_label_container

                        RowLayout{

                            anchors.fill: parent


                            Item {

                                Layout.fillHeight: true
                                Layout.fillWidth: true


                                GUI.TextScroller {
                                    id: centralLabel
                                    anchors.fill: parent

                                    horizontalAlignment:Text.AlignRight

                                    text:currentProject?currentProject.name:"No project loaded"

                                    onTextChanged:{
                                        if(text){

                                        }
                                    }

                                    duration: mainStateAnimationTime
                                    font.pixelSize: 15
                                    //                                horizontalAlignment:Text.AlignHCenter




                                }

                            }

                            Item {
                                Layout.fillHeight: true
                                Layout.fillWidth: true

                                GUI.TextScroller {
                                    anchors.fill: parent

                                    visible:false//rootwindow.currentProject&&currentProject.selectedSubproject
                                    //text:currentProject&&currentProject.selectedSubproject?"- "+currentProject.selectedSubproject.name:""
                                    horizontalAlignment:Text.AlignLeft
                                    duration: mainStateAnimationTime
                                    font.pixelSize: 15



                                }


                            }


                        }

                    }

                    Item{


                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        enabled:(loggedUser&&loggedUser.role===User.AdminRole)
                        RowLayout{


                            anchors.fill: parent


                            Item{
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                            }





                            RoundButton{
                                id:project_edit

                                visible: loggedUser&&loggedUser.role===User.AdminRole

                                Material.elevation:0

                                //opacity:networkManager_component.Ready?1:0

                                Behavior on opacity {
                                    NumberAnimation { duration: mainStateAnimationTime }
                                }


                                Behavior on Layout.preferredWidth {
                                    NumberAnimation { duration: mainStateAnimationTime }
                                }


                                highlighted: rootwindow.projectEditMode

                                onClicked: {
                                    rootwindow.projectEditMode=!rootwindow.projectEditMode
                                }


                                states: [
                                    State {
                                        name: "invisible"
                                        when: mainState!="home" || (loggedUser&&loggedUser.role!==User.AdminRole) || !currentProject
                                        PropertyChanges { target: project_edit; Layout.preferredWidth: 0 }
                                        PropertyChanges { target: project_edit; opacity: 0 }

                                    },
                                    State {
                                        name: "visible"
                                        when: mainState=="home" &&  (loggedUser&&loggedUser.role===User.AdminRole)
                                        PropertyChanges { target: project_edit; Layout.preferredWidth: 48 }
                                        PropertyChanges { target: project_edit; opacity: 1 }

                                    }
                                ]


                                Image {

                                    anchors.fill: parent
                                    anchors.margins: 10
                                    fillMode: Image.PreserveAspectFit
                                    source: "qrc:/images/pencil.png"



                                }
                            }

                            ToolSeparator {
                                //rightPadding: 1
                                visible: loggedUser&&loggedUser.role===User.AdminRole

                            }




                            RoundButton{
                                id:wifi_fab


                                visible: wifilevel_loader.item


                                Loader{
                                    id:wifilevel_loader

                                    anchors.fill: parent

                                    onLoaded: {
                                        //item.network=wifiloader.item.connectedNetwork
                                    }
                                }



                                Material.elevation:0

                                //opacity:networkManager_component.Ready?1:0

                                Behavior on opacity {
                                    NumberAnimation { duration: mainStateAnimationTime }
                                }


                                Behavior on Layout.preferredWidth {
                                    NumberAnimation { duration: mainStateAnimationTime }
                                }


                                highlighted: false




                                Image {
                                    width: 15
                                    height: 15

                                    anchors.bottom: parent.bottom
                                    anchors.right: parent.right

                                    anchors.rightMargin: 3
                                    anchors.bottomMargin: 11



                                    source: "qrc:/images/alert-outline.png"

                                    property int netCount:wifiloader.item?wifiloader.item.networksAvailableCount:0;

                                    visible: wifiloader.item&&wifiloader.item.connected==false && netCount>0




                                    GUI.Blink{
                                        running: parent.visible
                                        blinkTime: 500
                                        //target: parent
                                    }

                                    layer.enabled: true

                                    layer.effect: ColorOverlay{
                                        color: "orange"
                                    }
                                }






                                //                                Component{
                                //                                    id:editwifi_component
                                //                                    url:"qrc:///NetworkManager/ConfigWifiItem.qml";
                                //                                }



                                onClicked: {

                                    if( (loggedUser&&loggedUser.role==User.AdminRole) && mainState!="editwifi"){
                                        editWifi()
                                    }


                                }

                            }
                            ToolSeparator {
                                rightPadding:0
                                leftPadding: 0
                                visible: false
                                //visible:network_manager&&network_manager.wifiStatus!=NetworkManager.STAT_NOTINITED && settings_container.state!="settings"
                            }


                            RowLayout{

                                id:settings_container

                                Layout.fillHeight: true
                                spacing: 2

                                visible: loggedUser&&loggedUser.role==User.AdminRole
                                //                        visible: true





                                RoundButton{
                                    id:save_fab

                                    Material.elevation:0
                                    Layout.preferredHeight: 48
                                    Layout.preferredWidth: 48

                                    enabled: settings&&settings.loaded
                                    //                    highlighted: true
                                    //    anchors.verticalCenter: parent.verticalCenter

                                    opacity: enabled?1:0.2

                                    Image {
                                        anchors.centerIn: parent
                                        height: 30
                                        width:height
                                        fillMode: Image.PreserveAspectFit
                                        horizontalAlignment: Image.AlignHCenter
                                        verticalAlignment: Image.AlignVCenter
                                        source:"qrc:/images/content-save.png"

                                    }


                                    states: [
                                        State {
                                            name: "invisible"
                                            when: (loggedUser&&loggedUser.role===User.ProductionRole)
                                            PropertyChanges { target: save_fab; Layout.preferredWidth: 0 }
                                            PropertyChanges { target: save_fab; opacity: 0 }

                                        },
                                        State {
                                            name: "visible"
                                            when: (loggedUser&&loggedUser.role===User.AdminRole)
                                            PropertyChanges { target: save_fab; Layout.preferredWidth: 48 }
                                            PropertyChanges { target: save_fab; opacity: 1 }

                                        }
                                    ]



                                    Behavior on Layout.preferredWidth {
                                        NumberAnimation { duration: mainStateAnimationTime }
                                    }
                                    Behavior on opacity{
                                        NumberAnimation { duration: mainStateAnimationTime}
                                    }


                                    onClicked: {

                                        //                                        if(currentUser.isLogged) {

                                        settings.save();

                                        //                                        }
                                    }
                                }

                                RoundButton{
                                    id:settings_fab
                                    enabled: mainState=="home"

                                    //cursorShape: Qt.PointingHandCursor

                                    //anchors.verticalCenter: parent.verticalCenter
                                    //Material.elevation:0

                                    Material.elevation:0
                                    //highlighted: true
                                    Layout.preferredHeight: 48
                                    Layout.preferredWidth: 48

                                    states: [
                                        State {
                                            name: "invisible"
                                            when: mainState!="home" || (loggedUser&&loggedUser.role!==User.AdminRole)
                                            PropertyChanges { target: settings_fab; Layout.preferredWidth: 0 }
                                            PropertyChanges { target: settings_fab; opacity: 0 }

                                        },
                                        State {
                                            name: "visible"
                                            when: mainState=="home" &&  (loggedUser&&loggedUser.role===User.AdminRole)
                                            PropertyChanges { target: settings_fab; Layout.preferredWidth: 48 }
                                            PropertyChanges { target: settings_fab; opacity: 1 }

                                        }
                                    ]

                                    Behavior on Layout.preferredWidth {
                                        NumberAnimation { duration: mainStateAnimationTime }
                                    }
                                    Behavior on opacity{
                                        NumberAnimation { duration: mainStateAnimationTime}
                                    }

                                    //                  Material.background: selectedprimary



                                    Image {
                                        anchors.centerIn: parent
                                        height: 30
                                        width:height
                                        fillMode: Image.PreserveAspectCrop
                                        horizontalAlignment: Image.AlignHCenter
                                        verticalAlignment: Image.AlignVCenter
                                        source: "qrc:/images/settings.png"

                                    }

                                    onClicked: {

                                        stacked_view.push(usersettingsview)
                                    }
                                }


                            }
                        }

                    }

                }
            }



            Item{
                id:maincontainer
                Layout.fillHeight: true
                Layout.fillWidth: true

                StackView{
                    id:stacked_view
                    anchors.fill: parent

                    onCurrentItemChanged: {
                        mainState=currentItem?currentItem.state:"";
                        //titleLabel.text=mainState=="home"?currentUser?currentUser.userName:"DynamicFLow3":currentItem?currentItem.title:"";
                    }


                }



            }

            ToolBar {
                id:footer
                Layout.fillWidth: true
                Layout.preferredHeight: 45

                Material.foreground: "white"


                RowLayout{
                    anchors.margins: 2
                    anchors.fill: parent
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Label{
                        text: "Automation 2018"
                    }
                }

            }

        }

        GUI.PopUp {
            id:loginpopup

            //            parent:inputPanel
            property User selectedUser
            x: (rootwindow.width - width) / 2
            y: (rootwindow.height - height) / 2
            contentWidth: view.implicitWidth
            contentHeight: view.implicitHeight
            Material.foreground: "white"
            modal: false
            dim:true
            focus: true
            closePolicy:Popup.CloseOnEscape

            onVisibleChanged:{

                if(visible){
                    drawer.close()
                }
            }

            background:null

            Component.onCompleted: {
                pass_input.focus=true
            }



            Flickable {
                id: popupflickable

                property real scrollMarginVertical: 0

                objectName: "popupflickable"

                anchors.fill: parent

                flickableDirection: Flickable.VerticalFlick

                contentWidth: view.implicitWidth
                contentHeight: view.implicitHeight


                Rectangle{
                    color: Material.primary
                    anchors.fill: parent

                    radius: 2

                    ColumnLayout {

                        id:view

                        Image {
                            Layout.fillWidth: true;
                            fillMode: Image.Pad
                            source: "qrc:/images/ic_person_white_36dp_1x.png"
                        }
                        Label{
                            Layout.fillWidth: true
                            horizontalAlignment:Text.AlignHCenter
                            text:loginpopup.selectedUser?loginpopup.selectedUser.name:""
                        }

                        TextField{


                            GUI.MaterialPlaceHolder{
                                id:placeholder
                                placeHolderText:"PIN"


                            }



                            Layout.margins: 10
                            id:pass_input
                            Layout.fillWidth: true;
                            //                            placeholderText: "PIN"
                            passwordCharacter: "*"
                            maximumLength:4
                            echoMode: TextInput.Password
                            inputMethodHints: Qt.ImhDigitsOnly
                            onTextChanged: {
                                if(Qt.atob(loginpopup.selectedUser.pin)==text){
                                    settings.currentUser=loginpopup.selectedUser;
                                    loginpopup.close()
                                    pass_input.text=""
                                    login_container.opened=false
                                }
                                else if(text.length==maximumLength){
                                    placeholder.placeHolderText="Invalid Pin"
                                    placeholder.textColor=Material.color(Material.Red)
                                }
                                else{
                                    placeholder.placeHolderText="PIN"
                                    placeholder.textColor=Material.foreground
                                }

                            }
                        }


                    }
                }
            }
        }


    }


    Component{
        id:maincontentview


        Item{
            state:"home"
            property string title:"Novares"

            id:basemodule
            //            //            anchors.fill: parent
            visible:settings&&settings.loaded

            Component.onCompleted: {

            }


            Loader{
                id:layoutloader
                asynchronous: true
                onProgressChanged: {
                    console.log("pogress:"+progress);
                }



                sourceComponent: layoutcomponent

                anchors.fill: parent
            }


            Image{
                id:backLogo
                anchors.centerIn: parent
                //                Behavior on width {
                //                    NumberAnimation {
                //                        duration: 200
                //                    }
                //                }
                height: width
                width: rootwindow.width/1.75
                source: "qrc:/images/novares02_1.png"
                visible: opacity!=0
                opacity: 1
                fillMode:Image.PreserveAspectFit

                Behavior on opacity {
                    NumberAnimation { duration: 400 }
                }

                Timer{
                    interval: 1000
                    repeat: false
                    onTriggered: {
                        //                        backLogo.width= Qt.binding( function(){ return rootwindow.width/1.75 } )
                        backLogo.opacity=0

                    }

                    Component.onCompleted: {
                        start()
                    }
                }
            }

            //            BusyIndicator {
            //                id:loadingindicator
            //                running: layoutloader.item.modulesloaded!==true
            //                anchors.centerIn: parent
            //                width: parent.width/3
            //                height: parent.height/3
            //            }




            Component{
                id:layoutcomponent


                GUI.DockingLayout{
                    id:modulescontainer

                    property var fullscreenModule: null


                    visible:currentProject
                    anchors.fill: parent


                    Repeater{
                        model: currentProject&&currentProject.modules




                        GUI.DockingItem{
                            id:moduledockitem

                            isHidden:fullscreenModule && fullscreenModule!=module


                            MouseArea{
                                //                                anchors.centerIn: parent
                                anchors.verticalCenter: parent.verticalCenter
                                height: parent.height/0.95
                                width: 40

                                onClicked: {
                                    moduledockitem.z=999999
                                    resizer.width=40
                                }

                                onEntered: {
                                    //                                    moduledock.z=999999
                                    //                                    resizer.width=40
                                }


                                hoverEnabled: true
                                onExited: {
                                    moduledockitem.z=0
                                    resizer.width=0
                                }

                                //                                clip: true
                                Button{

                                    id:resizer
                                    clip: true
                                    anchors.margins: 5
                                    //                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.centerIn: parent
                                    height: parent.height

                                    width: 0
                                    Behavior on width {

                                        NumberAnimation {
                                            duration: 200
                                            easing.type: Easing.InOutQuad
                                        }
                                    }

                                    highlighted: true
                                    Material.background: Material.primary

                                    onDoubleClicked: {
                                        if(!modulescontainer.fullscreenModule){
                                            modulescontainer.fullscreenModule=module
                                        }
                                        else{
                                            modulescontainer.fullscreenModule=null

                                        }
                                    }

                                    Image {
                                        anchors.centerIn: parent
                                        fillMode: Image.PreserveAspectFit
                                        width: parent.width<24?parent.width:24
                                        height: parent.height<24?parent.height:24
                                        source: "qrc:/images/icons8-menu-24_white.png"
                                    }

                                }

                                //                                color: "red"
                                anchors.left: parent.right
                            }

                            Item{
                                id:container
                                enabled: rootwindow.projectEditMode?false:true
                                anchors.fill: parent
                                property AutomationModule loadedmodule:module
                                onLoadedmoduleChanged: {
                                    if(loadedmodule){
                                        loadedmodule.parent=container
                                    }

                                }


                            }


                            Item{


                                Rectangle{
                                    color: "grey"
                                    anchors.fill: parent

                                    opacity: 0.5
                                }

                                opacity: rootwindow.projectEditMode?1:0
                                visible: opacity!=0
                                Behavior on opacity {

                                    NumberAnimation {
                                        duration: 200
                                        easing.type: Easing.Linear
                                    }
                                }

                                anchors.fill: parent



                                RoundButton{
                                    anchors.centerIn: parent
                                    radius: 72
                                    highlighted: true
                                    Image {
                                        anchors.margins: 12
                                        anchors.fill: parent
                                        source: "qrc:/images/baseline_delete_white_48dp.png"
                                    }
                                    onClicked: {
                                        currentProject.modules.removeItem(module)
                                    }
                                }
                            }



                        }





                    }

                    GUI.DockingItem{

                        id:module_manager

                        isHidden:rootwindow.projectEditMode==false || (settings && settings.currentUser.role!=User.AdminRole)

                        clip:true


                        RoundButton{
                            anchors.centerIn: parent
                            radius: 72
                            highlighted: true
                            Image {
                                anchors.margins: 12
                                anchors.fill: parent
                                source: "qrc:/images/baseline_add_white_48dp.png"
                            }
                            onClicked: {
                                context.popup()
                            }

                            Menu {
                                id: context
                                //                                    title: ""
                                Action{
                                    enabled: false
                                    text: "Add module"
                                }
                                MenuSeparator { }

                                Repeater{
                                    model: availableModules
                                    MenuItem {
                                        text: modelData
                                        onClicked: {
                                            currentProject.createModule(text)

                                        }
                                    }

                                }


                            }

                        }

                    }




                }

                //                }



            }



            Rectangle{
                id:sourcefilenokId
                property bool sourcefileOK:false;

                anchors.fill: parent
                visible:settings&&settings.basefileError
                TextField{
                    id:source_path_id
                    anchors.centerIn: parent
                    width: 450;

                    text: settings?settings.source:""
                    onTextChanged: {
                        //                        if(utilities.fileExists(text)){
                        //                            console.log("file exists")
                        //                            basesettings.setSource(text);
                        //                            sourcefilenokId.sourcefileOK=true
                        //                        }else{
                        //                            console.log("file don't exists")

                        //                            sourcefilenokId.sourcefileOK=false
                        //                        }
                    }

                    Component.onCompleted: {

                    }

                    placeholderText: "Configuration file not found, select one"
                    Material.background: "red"
                    selectByMouse: true
                    RoundButton{
                        id: roundButton
                        spacing: 5
                        Material.background:sourcefilenokId.sourcefileOK?Material.Green:Material.accent

                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: -8
                        anchors.left: parent.right
                        onPressed:{
                            if(sourcefilenokId.sourcefileOK){
                                settings.updateBaseSettings();
                            }else{
                                fileDialog.open()
                            }
                        }
                        Image{
                            fillMode:Image.Pad
                            source: sourcefilenokId.sourcefileOK==false?"qrc:/images/ic_insert_drive_file_white_24dp_1x.png":"qrc:/images/ic_file_upload_white_24dp_1x.png"
                            anchors.centerIn: parent

                        }
                        highlighted: true;
                        //                        FileDialog {
                        //                            id: fileDialog
                        //                            title: "Please choose a file"
                        //                            //folder: shortcuts.home
                        //                            defaultSuffix:"json"
                        //                            nameFilters: ["Configutarion files (*.json)"]
                        //                            onAccepted: {
                        //                                //console.log("You chose: " + fileDialog.currentFile)

                        //                                settings.setSource(fileDialog.currentFile)
                        //                                source_path_id.text=Qt.binding(function(){
                        //                                    return settings.source;
                        //                                }
                        //                                );
                        //                            }
                        //                            onRejected: {
                        //                                console.log("Canceled")

                        //                            }

                        //                        }
                    }
                }



            }


        }




    }

    Component{
        id:usersettingsview


        GUI.UserSettingsView{
            id:usersettings
            state:"preferences"
            property string title:qsTr("User Settings")
        }
    }







    //    Popup{
    //        id:inputpanelPopup
    //        z: 9999999

    //        contentWidth: inputPanel.implicitWidth
    //        contentHeight: inputPanel.implicitHeight

    //        padding: 0

    //        background: null

    //        x:0
    //        y:rootwindow.height-inputPanel.height



    //        InputPanel {
    //            id: inputPanel
    //            z: 9999999

    //            onActiveChanged: {
    //                if(active){
    //                    inputpanelPopup.open()
    //                }
    //                else{
    //                    inputpanelPopup.close()
    //                }


    //            }

    //            onVisibleChanged: {
    //                console.log("visible:"+visible)
    //            }

    //            width: rootwindow.width

    //            // width: 400
    //            scale: 1
    //            opacity: 0
    //            visible: opacity!=0
    //            states: State {
    //                name: "visible"
    //                when: inputPanel.active
    //                PropertyChanges {
    //                    target: inputPanel
    //                    opacity:1
    //                }
    //            }
    //            transitions: Transition {
    //                from: ""
    //                to: "visible"
    //                reversible: true
    //                ParallelAnimation {
    //                    NumberAnimation {
    //                        properties: "opacity"
    //                        duration: 250
    //                        easing.type: Easing.InOutQuad
    //                    }
    //                }
    //            }
    //            GUI.AutoScroller {}
    //        }


    //    }



    Connections{
        target: automationstudio.settings

        onDoUpdate:{
            updater.visible=true
        }
    }

    GUI.AppUpdaterItem{
        id:updater
        visible:false
    }


    InputPanel {
        id: inputPanel
        enabled: settings&&settings.useKeyboard
        visible: enabled

        parent: Overlay.overlay

        z: 1000002

        y: rootwindow.height

        anchors.horizontalCenter: parent.horizontalCenter


        //        width:parent.width*0.75
        width:parent.width
        states: State {
            name: "visible"
            /*  The visibility of the InputPanel can be bound to the Qt.inputMethod.visible property,
                    but then the handwriting input panel and the keyboard input panel can be visible
                    at the same time. Here the visibility is bound to InputPanel.active property instead,
                    which allows the handwriting panel to control the visibility when necessary.
                */
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: rootwindow.height - inputPanel.height
            }


        }
        property var mappedy: inputPanel.mapToGlobal(inputPanel.x,inputPanel.y)
        transitions: Transition {
            id: inputPanelTransition
            from: ""
            to: "visible"
            reversible: true
            //                    enabled: !VirtualKeyboardSettings.fullScreenMode
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
        Binding {
            target: InputContext
            property: "animating"
            value: inputPanelTransition.running
        }



        GUI.AutoScroller {

            panelY:inputPanel.y
        }
    }


}
