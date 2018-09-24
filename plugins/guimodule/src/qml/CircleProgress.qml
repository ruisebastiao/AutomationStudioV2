import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

ProgressBar {
    id:root

    property string progressColor: "orange"

    property bool show: true

    opacity: show?1:0

    Behavior on opacity {
        NumberAnimation{
            duration: 100
        }
    }

    visible: opacity==0?false:true

    background: Item {
        anchors.fill: root
        //       Label{
        //           anchors.centerIn: parent
        //           text:root.value
        //       }
    }


    //    clip: true

    onPositionChanged: {
        progress_canvas.requestPaint()

    }
    Component.onCompleted: {
        //        onPositionChanged.connect()
    }

    contentItem: Item {
        anchors.fill: parent
        Canvas{
            id:progress_canvas
            anchors.fill: parent

            property real radius:root.show?(width/2)-5:0

            Behavior on radius {
                NumberAnimation{
                    duration: 300
                    easing.type: Easing.InOutBounce
                }
            }

            onRadiusChanged: requestPaint()

            onPaint: {


                var ctx = getContext("2d");
                ctx.reset();

                var centerX = Math.floor(width / 2);
                var centerY = Math.floor(height / 2);



                ctx.lineWidth = 2;
                ctx.strokeStyle =root.progressColor

                ctx.beginPath();
                ctx.arc(centerX, centerY, radius, 0, 2*Math.PI*root.position);

                ctx.stroke();
            }

        }
    }
}



