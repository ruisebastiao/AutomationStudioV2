import QtQuick 2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import automationmodule 1.0

import visionmodule 1.0
import guimodule 1.0

VisionModule {
    id:root
    anchors.fill: parent







    RowLayout{
        parent:moduleitem.mainpagecontainer
        anchors.fill: parent
        anchors.margins: 5
  }





    onConfigSourceChanged:{

        root.load(appDir+configSource);
    }

    AutomationModuleItem{
        id:moduleitem
        anchors.fill: parent
        loadedmodule: parent


    }

}
