import QtQuick 2.8
import QtQuick.VirtualKeyboard 2.1

Item {
    id:root

    property var innerFlickable

    property var previousFlickable

    property real oldContentY: 0

    property var inputItem: InputContext.inputItem


//    Connections {
//          ignoreUnknownSignals: true
//          target: inputItem&inputItem.Keys

//          onEscapePressed: {
//              inputItem.cancel();
//              console.log("escaped")
//          }
//      }



    property bool animating: InputContext.animating
    onAnimatingChanged:  {

        if(animating==false){

            if(Qt.inputMethod.visible==false && previousFlickable){
                previousFlickable.contentY =root.oldContentY
            }
            else{
                previousFlickable=innerFlickable
            }

        }
    }


    property real panelY: 0
    property var mappedcursorRectangle

    onPanelYChanged: {

        ensureVisible(innerFlickable)

    }

    onInputItemChanged: {
        innerFlickable = null


        if (inputItem !== null) {
            var parent_ = inputItem.parent
            while (parent_) {
                if (parent_.maximumFlickVelocity) {

                    innerFlickable = parent_
                    break;
                }
                parent_ = parent_.parent
            }

        }

        if(innerFlickable!=null && inputItem && inputItem.cursorRectangle){
            mappedcursorRectangle = innerFlickable.mapToGlobal(inputItem.cursorRectangle.x, inputItem.cursorRectangle.y)
            root.oldContentY = innerFlickable.contentY
        }

    }

    function ensureVisible(flickable) {
        if (Qt.inputMethod.visible && inputItem && flickable && flickable.visible && flickable.interactive) {



            if (!inputItem.hasOwnProperty("cursorRectangle"))
                return



            var offsetY= 100




            if(mappedcursorRectangle.y>root.panelY - offsetY){

                flickable.contentY =(mappedcursorRectangle.y-root.panelY)+offsetY

            }

        }


    }

    Timer {
        id: delayedLoading
        interval: 500
        onTriggered: {
            ensureVisible(innerFlickable)
        }
    }


}
