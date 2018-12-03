import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import automationmodule 1.0
import epsonmodule 1.0

import guimodule 1.0

EpsonModule {
    id:root
    anchors.fill: parent







    RowLayout{
        parent:moduleitem.mainpagecontainer
        anchors.fill: parent
        anchors.margins: 5
  }




    AutomationModuleItem{
        id:moduleitem
        anchors.fill: parent
        loadedmodule: parent


    }

}
