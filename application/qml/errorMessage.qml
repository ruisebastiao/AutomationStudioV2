import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: errorwindow
    visible: true
    width: 400
    height: 150

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


    Timer{
        id:closetimer
        property int triggerSecs: 8
        property int numSecs: 0
        onNumSecsChanged: {
            if(numSecs==triggerSecs){
                stop()
                errorwindow.close()
            }
        }

        interval: 1000
        repeat: true
        onTriggered: {
            numSecs=numSecs+1
//
        }

    }

    Component.onCompleted: {
        closetimer.start()
    }

    Material.theme: selectedTheme
    Material.primary: selectedprimary
    Material.accent:selectedaccent

    ColumnLayout{
        Material.elevation: 8
        anchors.fill: parent
        ToolBar {
            z:1
            id:drawer_toolbar
            Material.foreground: "white"
            Layout.fillWidth: true
            Layout.preferredHeight: 45
            Label{
                anchors.centerIn: parent
                text: "Já existe uma aplicacao a correr ("+(closetimer.triggerSecs-closetimer.numSecs)+")"
            }
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight:  true
        }
        //        Button{
        ////            highlighted: true
        //            Layout.alignment: Layout.Center
        //            text: "Já existe uma aplicacao a correr"
        //        }
        Button{
            id:closebutton
            highlighted: true
            Layout.alignment: Layout.Center
            text: "Sair"
            onClicked: {
                errorwindow.close()
            }
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight:  true
        }
    }

    //    x: Screen.width / 2 - width / 2
    //    y: Screen.height / 2 - height / 2
    //    flags:Qt.SplashScreen
    flags:Qt.FramelessWindowHint


}
