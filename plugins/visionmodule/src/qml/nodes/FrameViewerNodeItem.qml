import QtQuick 2.8
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import com.novares 1.0
import QuickQanava 2.0 as Qan
import "qrc:/QuickQanava"   as Qan

FlowNode{
    id:root

    normalWidth: 400
    normalHeight: 400
    expandOnEdit:true

    editHeight: 500
    editWidth:500


    Connections{
        target:node

        onFrameSourceChanged:{
            viewer.frameObject=frameSource

        }

        onProcessFrameChanged:{

           viewer.processFrame=processFrame
        }

    }



    Component.onCompleted: {
        //viewer.frameObject=root.node.newFrameObject
        //  console.log(viewer.frameObject)
    }

    contentItem: Item{
        anchors.fill: parent

        FrameViewer{
            id:viewer
            anchors.fill: parent
            anchors.margins: 5

        }
    }


}
