import QtQuick              2.8
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import com.novares.utilities 1.0

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

FlowNode {
    id:root

    resizable:true

    contentItem: ColumnLayout{
        anchors.fill: parent
        //        Button{
        //            anchors.centerIn: parent
        //            text:"teste"
        //            onPressed: {
        //                root.node.teste()
        //            }

        //        }


        ComboBox{
//            anchors.centerIn: parent
            Layout.fillWidth: true
            model: flownodemanager
            delegate:ItemDelegate{
                 width: parent.width
                text: nodeName
            }
        }
        ComboBox{
//            anchors.centerIn: parent
            Layout.fillWidth: true
            model: flownodemanager
            delegate:ItemDelegate{
                 width: parent.width
                text: nodeName
            }
            textRole: nodeName
        }

    }

    Component.onCompleted: {

    }
}
