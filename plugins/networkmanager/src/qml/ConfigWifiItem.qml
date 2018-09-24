import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

import networkmanager 1.0
import guimodule 1.0

Item {

    state: "editwifi"
    property string title: qsTr("Wifi settings")

    property NetworkManager networkmanager

    id:root


    Connections{
        target: networkmanager
        onWifiStatusChanged: {
            console.log("Status:"+wifiStatus)
        }
    }

    //property bool wifiConnecting: false

    //onWifiConnectingChanged: console.log("wifiConnecting:"+wifiConnecting)
    Pane{


        Material.elevation:6
        anchors.fill: parent
        anchors.margins: 5



        RoundButton{
            enabled: networkmanager&&(networkmanager.wpsNetworksAvailable===true)&&(networkmanager.wpsStarted===false);
            //anchors.bottom: title_label.bottom
            anchors.top: parent.top
            anchors.topMargin: -5
            anchors.right: availablenetwork_group.right
            highlighted: true
            Label{
                text: "wps"
                anchors.centerIn: parent

            }


            CircleProgress {
                id:wps_progress
                anchors.fill: parent
                anchors.margins: -2
                show: networkmanager&&networkmanager.wpsStarted===true
                //running: model.display.connecting
                Material.accent: "orange"
                value:120
                to:120
                from:0

                onValueChanged: {
                    //                    if(value==from){
                    //                        time_timer.stop();
                    //                    }
                }


                property bool wpsStarted:networkmanager&&networkmanager.wpsStarted
                onWpsStartedChanged: {
                    //                    if(wpsStarted) time_timer.start()
                    //                    else time_timer.stop();
                }

                ColorAnimation{
                    target: wps_progress
                    property: "progressColor"
                    from:"orange"
                    to:"red"

                    onRunningChanged: {
                        if(running==false) wps_progress.progressColor="orange"
                    }

                    duration: animate_progress.duration
                    running: animate_progress.running
                }

                NumberAnimation{
                    id:animate_progress

                    running: wps_progress.wpsStarted

                    onRunningChanged: {
                        if(running==false){
                            wps_progress.value=120
                        }
                    }

                    target: wps_progress
                    property: "value"
                    from:120
                    to:0

                    duration: 120000
                }


            }



            onClicked: {
                if(networkmanager){
                    networkmanager.startWPS();
                }
            }


        }

        GroupBox{
            id:availablenetwork_group
            //title: "Available networks"

            Label{
                id:title_label

                anchors.left: parent.left
                anchors.bottom: parent.top

                text: "Available networks"
            }

            BusyIndicator{
                running: networkmanager&&networkmanager.scanning
                height: title_label.paintedHeight+15
                width: height
                anchors.bottom: title_label.bottom
                anchors.left: title_label.right
                anchors.leftMargin: 5

            }


            anchors.centerIn: parent
            width: parent.width*0.75
            height: parent.height*0.75
            spacing: 0
            padding: 0


            ListView{
                id:availablenetwork_list
                clip:true
                anchors.fill: parent
                model:networkmanager&&networkmanager.availableNetworks;
                delegate:  networkDelegate



                add: Transition {
                    NumberAnimation { property: "height"; from: 0; to:50;duration: 400 }
                    // NumberAnimation { property: "opacity"; from: 0; to:1;duration: 250 }
                    ColorAnimation{ property: "backgroundColor"; from: "green"; to:"transparent"; duration: 400}
                }
                remove: Transition {
                    NumberAnimation { property: "height"; from: 50; to:0;duration: 400 }
                    NumberAnimation { property: "opacity"; from: 1; to:0;duration: 400 }
                    ColorAnimation{ property: "backgroundColor"; from: "transparent"; to:"red"; duration: 400}
                }

                displaced: Transition {

                    SequentialAnimation{
                        PauseAnimation {
                            duration: 200
                        }
                        NumberAnimation { properties: "x,y"; duration: 200 }
                    }
                }

                Component.onCompleted: {

                }
            }
        }

    }
    Component {
        id: networkDelegate
        ItemDelegate {
            id:delegate_item

            //ListView.delayRemove:true;

            property bool editMode: false
            property color backgroundColor:"transparent";

            //visible: modelNetwork!=null


            onFocusChanged: {
                if(focus==false){
                    console.log("not focus")
                    delegate_item.editMode=false
                }
            }

            //TODO check modelNetwork null
            property int networkStatus:modelNetwork?modelNetwork.networkStatus:NetworkInfo.NET_DISCONNECTED

            onNetworkStatusChanged: {
                if(networkStatus!=NetworkInfo.NET_DISCONNECTED){
                    delegate_item.editMode=false;
                }
            }

            property int delegateIndex: index
            onDelegateIndexChanged: console.log("delegateIndex:"+delegateIndex)

            property NetworkInfo modelNetwork:model.display



            spacing: 0
            width: parent.width

            height:editMode?80:50;

            Behavior on height {
                NumberAnimation{duration: 75}
            }


            highlighted: ListView.isCurrentItem

            onHighlightedChanged: editMode=false


            RowLayout{
                anchors.fill: parent



                Item{
                    Layout.preferredHeight: 48
                    Layout.preferredWidth: 48

                    RoundButton{
                        id:connect_wifi_bt

                        anchors.fill: parent


                        Behavior on opacity {
                            NumberAnimation {duration: 50 }
                        }

                        Component.onCompleted: {
                            opacity=Qt.binding(function(){

                                //var ret=1


                                if( delegate_item.highlighted || delegate_item.modelNetwork.networkStatus==NetworkInfo.NET_CONNECTING)
                                    return 1

                                return 0

                            })
                        }

                        visible: opacity==0?false:true

                        enabled:  delegate_item.modelNetwork.networkStatus==NetworkInfo.NET_DISCONNECTED && (wifi_key.hasError==false || delegate_item.modelNetwork.isConfigured)

                        highlighted: true//root.globalConnecting==false || (delegate_item.highlighted==false && root.globalConnecting==true)


                        BusyIndicator {
                            anchors.fill: parent
                            anchors.margins: -2
                            visible: delegate_item.modelNetwork.networkStatus==NetworkInfo.NET_CONNECTING
                            running: visible
                            Material.accent: "orange"
                        }

                        Image {
                            id: connect_img
                            width: 26
                            height: 26
                            anchors.centerIn: parent
                            source: "qrc:/images/power-plug.png"
                        }
                        onClicked: {

                            toastMessage("Connecting to:"+delegate_item.modelNetwork.ssid);

                            networkmanager.connectNetwork(index)
                            //connecting=!connecting;
                            //root.globalConnecting=connecting
                        }
                    }

                }

                Item{
                    Layout.preferredHeight: 48
                    Layout.preferredWidth: 48


                    RoundButton{
                        id:delete_wifi_bt

                        anchors.fill: parent



                        opacity:(delegate_item.highlighted&&delegate_item.modelNetwork.isConfigured==true)?1:0
                        Behavior on opacity {


                            NumberAnimation {duration: 50 }
                        }

                        visible: opacity==0?false:true
                        highlighted: true
                        Image {
                            id: delete_img
                            width: 26
                            height: 26
                            anchors.centerIn: parent
                            source: "qrc:/images/delete-forever.png"
                        }

                        onClicked: networkmanager.removeNetwork(index)
                    }

                    RoundButton{
                        id:edit_wifi_bt

                        anchors.fill: parent



                        opacity:(delegate_item.highlighted && delegate_item.modelNetwork.auth!=NetworkInfo.AUTH_NONE_OPEN && delegate_item.modelNetwork.isConfigured==false)?1:0
                        Behavior on opacity {


                            NumberAnimation {duration: 50 }
                        }

                        visible: opacity==0?false:true
                        highlighted: true
                        Image {
                            id: edit_img
                            width: 26
                            height: 26
                            anchors.centerIn: parent
                            source: "qrc:/images/pencil.png"
                        }

                        onClicked: delegate_item.editMode=!delegate_item.editMode
                    }
                }



                ColumnLayout{
                    id:center_container
                    clip: true

                    Layout.margins: 1

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    spacing: 0



                    Item{

                        // visible: delegate_item.editMode==false
                        Layout.preferredHeight: 1
                        Layout.fillWidth: true
                    }

                    Item{
                        id:ssid_label_container
                        Layout.preferredHeight:ssid_label.paintedHeight
                        Layout.fillWidth: true
                        Label {
                            id:ssid_label
                            font.pixelSize: 18

                            anchors.centerIn: parent


                            text: delegate_item.modelNetwork.ssid
                            elide: Text.ElideMiddle

                        }
                    }
                    Item{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Item{

                            anchors.fill: parent

                            opacity: delegate_item.editMode?0:1
                            visible: opacity!=0
                            Behavior on opacity {
                                NumberAnimation{duration: 75}
                            }
                            Label{
                                id:status_label
                                font.pixelSize: 11
                                anchors.centerIn: parent

                                Component.onCompleted:{


                                    text=Qt.binding(function(){

                                        var ret="";



                                        if(delegate_item.modelNetwork.networkStatus==NetworkInfo.NET_REJECTED){
                                            ret+=qsTr("Network Rejected");
                                            if(delegate_item.modelNetwork.networkRejectReason==NetworkInfo.REJECT_WRONGKEY){
                                                ret+=" : "+qsTr("Wrong Key");
                                            }
                                        }
                                        else if(delegate_item.modelNetwork.networkStatus!=NetworkInfo.NET_CONNECTED){

                                            ret=ret+qsTr("Disconnected")
                                            ret=ret+"  ("

                                            switch (delegate_item.modelNetwork.auth) {
                                            case NetworkInfo.AUTH_NONE_OPEN:
                                            case NetworkInfo.AUTH_NONE_WEP:
                                            case NetworkInfo.AUTH_NONE_WEP_SHARED:
                                                ret=ret+qsTr("NONE");
                                                break;
                                            case NetworkInfo.AUTH_IEEE8021X:
                                                ret=ret+qsTr("IEEE8021X");
                                                break;
                                            case NetworkInfo.AUTH_WPA_PSK:
                                                ret=ret+qsTr("WPA-PSK");
                                                break;
                                            case NetworkInfo.AUTH_WPA_EAP:
                                                ret=ret+qsTr("WPA-EAP");
                                                break;
                                            case NetworkInfo.AUTH_WPA2_PSK:
                                                ret=ret+qsTr("WPA-PSK");

                                                break;
                                            case NetworkInfo.AUTH_WPA2_EAP:
                                                ret=ret+qsTr("WPA-EAP");

                                                break;
                                            }
                                            ret=ret+")";

                                            if(delegate_item.modelNetwork.wpsAvailable){
                                                ret=ret+" (WPS)"
                                            }

                                        }

                                        else{

                                            ret=ret+qsTr("Connected")
                                            ret=ret+"  (IP:"+delegate_item.modelNetwork.ip+")"
                                        }


                                        return ret;//+translator.emptyString;
                                    })
                                }
                                //+translator.emptyString+" ("+model.display.authDesc+")";
                            }
                        }


                        RowLayout{

                            anchors.fill: parent

                            opacity: delegate_item.editMode==false?0:1
                            visible: opacity!=0

                            Behavior on opacity {
                                NumberAnimation{duration: 75}
                            }




                            Item{
                                Layout.fillHeight: true
                                Layout.fillWidth: true

                            }

                            TextField{
                                id:wifi_key

                                Layout.minimumWidth: parent.width/2
                                //Layout.fillWidth: true
                                property var flickObject: availablenetwork_list
                                property int keyboardMargin:35
                                property bool hasError:length<8

                                //  anchors.centerIn: parent

                                font.pixelSize: 12
                                Material.accent: selectedprimary
                                text:delegate_item.modelNetwork.passKey



                                onFocusChanged: {
                                    if(focus){
                                        if(wifi_key.length<8){
//                                            keyboardHelperText.text=qsTr("8 characters minimum")+translator.emptyString
//                                            keyboardHelperText.textColor="red"
                                        }
                                    }
                                }

                                Keys.onReturnPressed: delegate_item.editMode=false
                                Keys.onEnterPressed:  delegate_item.editMode=false

                                onTextChanged: {
                                    delegate_item.modelNetwork.passKey=text
                                    if(wifi_key.length<8){
                                        //keyboardHelperText.text=qsTr("8 characters minimum")+translator.emptyString
                                        //keyboardHelperText.textColor="red"
                                    }
                                    else{
                                        //keyboardHelperText.text=""
                                        //keyboardHelperText.textColor=Material.foreground
                                    }
                                }


                                MaterialPlaceHolder{

                                    placeHolderText:qsTr("WPA passphrase")
                                }

                            }

                            Item{
                                Layout.fillHeight: true
                                Layout.fillWidth: true

                            }




                        }
                    }





                }

                WifiLevelItem{

                    property var auth: delegate_item.modelNetwork.auth
                    showAuth: auth!=NetworkInfo.AUTH_NONE_OPEN

                    network: null

                    //inited: true
                    Layout.preferredHeight: 48
                    Layout.preferredWidth: 48

                    Component.onCompleted: {

                        network=Qt.binding(function(){

                            var networkat=networkmanager.availableNetworks.getAt(index);

                            return networkat;
                        });



                    }
                }

            }





            onClicked: {

                if (availablenetwork_list.currentIndex != index) {


                    availablenetwork_list.currentIndex = index



                }

                //console.log()

            }


        }


    }

}




