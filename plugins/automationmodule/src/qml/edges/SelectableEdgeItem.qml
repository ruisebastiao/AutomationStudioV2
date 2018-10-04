//-----------------------------------------------------------------------------

import QtQuick                      2.7
import QtQuick.Controls.Material    2.1

import QtQuick.Controls 2.2
import QuickQanava          2.0 as Qan


Qan.EdgeItem {
    id: root



    property bool hover: false


    onEdgeClicked:{

    }

    onEdgeHoverMove:{
        hover=true
    }


    onEdgeHoverLeave:{
        hover=false
    }

    Qan.EdgeTemplate {
        anchors.fill: parent
        visible:root.edge.isHidden===false


        edgeItem: parent
        color: hover?Material.accent:Material.primary


        RoundButton{
            id:bt
            anchors.centerIn: parent;
            width: 48
            height: 48
            highlighted: true
            opacity: root.hover?1:0
            visible: opacity!=0
            Behavior on opacity {

                NumberAnimation {

                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }

            Image {
                anchors.centerIn: parent
                fillMode: Image.Pad
                source: "qrc:/images/ic_remove_circle_outline_white_36dp_1x.png"
            }

            onPressed: {
                root.graph.deleteEdge(root.edge);

            }
        }

    }
}
