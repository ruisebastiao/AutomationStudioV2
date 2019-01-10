import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import QtQuick.Controls.Material 2.1

RoundButton {

    property alias expanded: container.expanded

    Item {
        id: container

        property bool expanded: false
        anchors.fill: parent
    }
}
