import QtQuick 2.10

import QtQuick.Controls 2.3

Popup {

    id:root
    //parent: Overlay.overlay

    Overlay.modeless: Rectangle {
        color: "#aacfdbe7"
        opacity: 0.05
        MouseArea {
            anchors.fill: parent


            propagateComposedEvents: false

            onPressed: {
                root.close();
            }

        }
    }

}
