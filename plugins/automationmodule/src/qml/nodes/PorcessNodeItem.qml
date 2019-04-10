
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import guimodule 1.0

import automationmodule 1.0

FlowNodeItem{
    id:root


    resizable:true;
    expandOnEdit:true;

    contentItem:  Flow{

        anchors.fill: parent

//        TextField{

//            text:root.node.processPath
//            anchors.margins: 4
//            wrapMode: TextEdit.WordWrap

//            onTextChanged: {
//                if(root.node.processPath!=text){
//                    root.node.processPath=text
//                }


//            }

//            width: 300

//            selectByMouse:true
//            MaterialPlaceHolder{
//                placeHolderText:"Process"
//            }
//        }

        CheckBox{

            checked: root.node.keepAlive
            onCheckedChanged: {
                root.node.keepAlive=checked
            }

            text: "Keep Alive"
        }

        CheckBox{

            checked: root.node.forceTerminate
            onCheckedChanged: {
                root.node.forceTerminate=checked
            }

            text: "Force Terminate"
        }

        RowLayout {
           Label{
               text: "Start Delay:"
           }

           SpinBox{
   //            textFromValue:  function(value, locale) { return ""Number(value).toLocaleString(locale, 'f', 0); }
               value: root.node.delayStart
               onValueChanged: root.node.delayStart=value
               from:0
               to:10000
               editable: true
           }
        }
    }

}
