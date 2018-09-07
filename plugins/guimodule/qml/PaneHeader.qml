import QtQuick 2.8
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtGraphicalEffects 1.0

Item {

    property string title

    ColumnLayout{
        anchors.fill: parent



        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 24
            Layout.margins: 2
            color: "transparent"

            Label {
                id:temp_label
                text: title
                anchors{
                    top:parent.top

                }
            }
            Rectangle{
                id:title_separator
                color: Material.theme==Material.Dark?"white":"black"
                height: 1
                anchors{
                    top:temp_label.bottom
                    topMargin: 3
                    left: parent.left
                    right: parent.right
                }
            }
            DropShadow {
                anchors.fill: title_separator

                verticalOffset: 1
                radius: 8
                samples: 17
                color: Material.theme==Material.Dark?"white":"black"
                source: title_separator
            }

        }

    }
}
