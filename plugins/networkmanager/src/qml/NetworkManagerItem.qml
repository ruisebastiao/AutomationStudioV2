import QtQuick 2.8

import networkmanager 1.0

NetworkManager {

    id:gNetworkManager

    Component.onCompleted: {
        gNetworkManager.start();

    }

}
