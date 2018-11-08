
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import QuickQanava          2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0



Flickable {
    id: f

    boundsBehavior: Flickable.StopAtBounds
    contentHeight: iContainer.height;
    contentWidth: iContainer.width;
    clip: true

    property alias viewer: viewer


    property bool fitToScreenActive: false

    property real minZoom: 1;
    property real maxZoom: 8

    property real zoomStep: 0.05

    onWidthChanged: {
        if (fitToScreenActive)
            fitToScreen();
    }
    onHeightChanged: {
        if (fitToScreenActive)
            fitToScreen();
    }

    Item {
        id: iContainer
        width: Math.max(viewer.width * viewer.scale, f.width)
        height: Math.max(viewer.height * viewer.scale, f.height)


        QMatView{

            id:viewer

            property real prevScale: 1.0;


            smooth: f.moving
            anchors.centerIn: parent

            transformOrigin: Item.Center

            onScaleChanged: {

                if ((width * scale) > f.width) {
                    var xoff = (f.width / 2 + f.contentX) * scale / prevScale;
                    f.contentX = xoff - f.width / 2
                }
                if ((height * scale) > f.height) {
                    var yoff = (f.height / 2 + f.contentY) * scale / prevScale;
                    f.contentY = yoff - f.height / 2
                }
                prevScale=scale;
            }



            Behavior on opacity{

                NumberAnimation{
                    duration: 250
                }
            }

        }


    }
    function fitToScreen() {
        var s = Math.min(f.width / viewer.width, f.height / viewer.height, 1)
        viewer.scale = s;
        f.minZoom = s;
        viewer.prevScale = scale
        fitToScreenActive=true;
        f.returnToBounds();
    }
    function zoomIn() {
        if (viewer.scale<f.maxZoom)
            viewer.scale*=(1.0+zoomStep)

        f.returnToBounds();
        fitToScreenActive=false;
        f.returnToBounds();
    }
    function zoomOut() {
        console.log("f.scale:"+f.scale)
        if (viewer.scale>f.minZoom)
            viewer.scale*=(1.0-zoomStep)


        f.returnToBounds();

    }
    function zoomFull() {
        viewer.scale=1;
        fitToScreenActive=false;
        f.returnToBounds();
    }


    ScrollIndicator.vertical: ScrollIndicator { }
    ScrollIndicator.horizontal: ScrollIndicator { }

    MouseArea{
        anchors.fill: parent
        scrollGestureEnabled: false

        onWheel: {
            if (wheel.modifiers & Qt.ControlModifier) {
                //                            console.log("wheel")

                if(wheel.angleDelta.y>0){
                    f.zoomIn()
                }
                else{
                    f.zoomOut()
                }

                wheel.accepted=true
                //                            f.contentX=mouseX
                //                            f.contentY=-mouseY
                //                             f.returnToBounds();
            }
            else{
                wheel.accepted=false
            }



        }

        //                    propagateComposedEvents: true
    }


}


