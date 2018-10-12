import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
Item{

   id:root
   property color textColor:Material.foreground
    property alias placeHolderText: placeholder_label.text
    Label{
        id:placeholder_label
        z:1
        font.pixelSize:root.parent.text.length===0?root.parent.font.pixelSize:14
        // opacity: parent.text==""?0:1
        y:root.parent.text.length===0?(root.parent.height/2-paintedHeight/2-4):-8

        color: (root.parent.focus===false || root.parent.text.length===0)?Material.foreground:textColor

        Behavior on y{
            NumberAnimation { duration: 100}
        }

        Behavior on font.pixelSize{
            NumberAnimation { duration: 100}
        }


        //                                Behavior on opacity{
        //                                    NumberAnimation { duration: 100}
        //                                }
    }

}
