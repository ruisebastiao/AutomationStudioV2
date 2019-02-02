
import QtQuick              2.7
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0


import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2


import QuickQanava          2.0 as Qan

import automationmodule 1.0
import visionmodule 1.0

ProcessingNodeItem{
    id:root
    expandOnEdit: true

    processingConfigItem: ColumnLayout{
        anchors.fill: parent


        Column{
            id:container
            Layout.fillWidth: true



            spacing: 5



            RowLayout{
                width: parent.width
                Label{
                    text: "Delta:"
                    Layout.preferredWidth: paintedWidth
                    verticalAlignment: Text.AlignVCenter

                }
                SpinBox {
                    id:spin_delta
                    Layout.fillWidth: true
                    editable: true
                    to:200

                    value: root.node.delta
                    onValueChanged: {
                        if(root.node&&root.node.configsLoaded){
                            root.node.delta=value
                        }
                    }
                }
            }


        }


    }

}
