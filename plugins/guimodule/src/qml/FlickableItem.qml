import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0


Item {
    id:root

    anchors.fill: parent

   property alias viewer: i


    Flickable {
        id: f
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        contentHeight: iContainer.height;
        contentWidth: iContainer.width;
        clip: true

        onContentXChanged: console.debug("CX"+contentX)
        onContentYChanged: console.debug("CY"+contentY)

        //Behavior on contentY { NumberAnimation {} }
        //Behavior on contentX { NumberAnimation {} }

        property bool fitToScreenActive: true

        property real minZoom: 0.1;
        property real maxZoom: 2

        property real zoomStep: 0.1

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
            width: Math.max(i.width * i.scale, f.width)
            height: Math.max(i.height * i.scale, f.height)



            Rectangle{

                id:i


                anchors.centerIn: parent


                property real prevScale: 1.0;

//                width: childrenRect.width
//                height: childrenRect.height
                smooth: f.moving



                onWidthChanged: console.debug(width)
                onHeightChanged: console.debug(height)
                transformOrigin: Item.Center
                onScaleChanged: {
                    console.debug(scale)
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
            var s = Math.min(f.width / i.width, f.height / i.height, 1)
            i.scale = s;
            f.minZoom = s;
            i.prevScale = scale
            fitToScreenActive=true;
            f.returnToBounds();
        }
        function zoomIn() {
            if (f.scale<f.maxZoom)
                i.scale*=(1.0+zoomStep)
            f.returnToBounds();
            fitToScreenActive=false;
            f.returnToBounds();
        }
        function zoomOut() {
            if (f.scale>f.minZoom)
                i.scale*=(1.0-zoomStep)
            else
                i.scale=f.minZoom;
            f.returnToBounds();
            fitToScreenActive=false;
            f.returnToBounds();
        }
        function zoomFull() {
            i.scale=1;
            fitToScreenActive=false;
            f.returnToBounds();
        }


        ScrollIndicator.vertical: ScrollIndicator { }
        ScrollIndicator.horizontal: ScrollIndicator { }

    }

    PinchArea {
        id: p
        anchors.fill: f
        enabled: i.status === Image.Ready
        pinch.target: i
        pinch.maximumScale: 2
        pinch.minimumScale: 0.1
        onPinchStarted: {
            console.debug("PinchStart")
            f.interactive=false;
        }

        onPinchUpdated: {
            f.contentX += pinch.previousCenter.x - pinch.center.x
            f.contentY += pinch.previousCenter.y - pinch.center.y
        }

        onPinchFinished: {
            console.debug("PinchEnd")
            f.interactive=true;
            f.returnToBounds();
        }
    }

}

