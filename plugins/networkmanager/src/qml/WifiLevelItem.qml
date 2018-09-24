import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.1

import networkmanager 1.0


Item {

    id:root

    property bool showAuth: false

    property NetworkInfo network


    Binding{
        target:level_canvas
        property: "level"

        value: network===null?-1:network.networkSignal
        when: network!=null || network!==0

    }

    Canvas{

        id:level_canvas


        renderStrategy: Canvas.Threaded
        antialiasing: true

        property real canvasOpacity: 0.4
        onCanvasOpacityChanged: {
            requestPaint()

        }

        property int level: -1

        property int iconY: height-(height/3)

        onLevelChanged: {
            requestPaint()
        }

        property string paintcolor: 'gray'
        anchors.fill: parent
        //scale:0.7
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            var centerX = Math.floor(width / 2);
            var centerY =level_canvas.iconY


            var startAngle = 1.25 * Math.PI;
            var endAngle = 1.75 * Math.PI;

            var steps=(centerY)/6.5

            var num_levels=5

            level_canvas.paintcolor='gray'



            ctx.imageSmoothingEnabled = true;

            ctx.beginPath();
            ctx.arc(centerX,centerY, 1.5, 0, 2*Math.PI, false);
            ctx.lineWidth = 1;

            if(level>=60){
                level_canvas.paintcolor= 'green';
            }
            else if(level>=20){
                level_canvas.paintcolor= 'orange';
            }
            else if(level>=0){
                level_canvas.paintcolor = 'red';
            }


            ctx.fillStyle = level_canvas.paintcolor;
            ctx.fill();
            ctx.strokeStyle = level_canvas.paintcolor;
            ctx.stroke();

            for(var i=1;i<num_levels;i++){
                ctx.beginPath();
                ctx.arc(centerX,centerY, steps*i, startAngle, endAngle, false);
                ctx.lineWidth = 3;
                if(level<((i/num_levels)*100)){
                    ctx.strokeStyle = 'gray';
                }
                else{
                    ctx.strokeStyle = level_canvas.paintcolor;

                }

                ctx.stroke();
            }




        }
    }

    Image{
        anchors.right: parent.right
        anchors.rightMargin: 5
        visible:root.showAuth
        y:level_canvas.iconY-width/2-2
        width: 14
        height: 14
        source: "qrc:/images/ic_lock_white_36dp_1x.png"
        layer.enabled: true
        layer.effect: ColorOverlay{
            color:level_canvas.paintcolor;
        }
    }

}
