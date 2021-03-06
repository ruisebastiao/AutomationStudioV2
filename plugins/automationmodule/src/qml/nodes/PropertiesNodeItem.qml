import QtQuick              2.8
import QtQuick.Layouts      1.3

import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import automationmodule 1.0
import epsonmodule 1.0
import guimodule 1.0

FlowNodeItem{

    id:root
    expandOnEdit: true

    resizable: true


    contentItem:  ColumnLayout{
        anchors.fill: parent
        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            title: "Properties"
            ColumnLayout{

                anchors.fill: parent

                ListView{
                    id:infolist
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model: root.node.properties
                    clip: true


                    onCurrentIndexChanged:{
                        if(currentIndex==-1) {
                            container.selectedPropertyInfo=null;
                        }
                    }

                    delegate: SwipeDelegate {
                        width: infolist.width
                        height: 40
                        highlighted: ListView.isCurrentItem

                        onHighlightedChanged: {
                            if(highlighted){
                                container.selectedPropertyInfo=propertyInfo
                            }
                        }
                        swipe.transition: Transition {
                            SmoothedAnimation { velocity: 3; easing.type: Easing.InOutCubic }
                        }
                        swipe.onOpened:{
                            infolist.model.removeItem(propertyInfo)
                            textPropertyName.text=""
                        }

                        swipe.right: Label {
                            id: deleteLabel
                            text: qsTr("Delete")
                            color: "white"
                            verticalAlignment: Label.AlignVCenter
                            padding: 12
                            height: parent.height
                            anchors.right: parent.right



                            background: Rectangle {
                                color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                            }
                        }


                        onClicked: {
                            infolist.currentIndex = index

                        }
                        Label{

                            text: propertyInfo.propertyName+" ("+propertyInfo.propertyValue+")"
                            anchors.fill: parent
                            font.pixelSize: 16
                            horizontalAlignment:Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            //                     fontSizeMode:Text.Fit
                        }
                    }

                }

                ColumnLayout{
                    id:container
                    Layout.fillWidth: true

                    property var selectedPropertyInfo


                    RowLayout{
                        Layout.fillWidth: true
                        Button{

                            Layout.fillWidth: true
                            text: container.selectedPropertyInfo?"Save":"Add"

                            highlighted: true
                            enabled: textPropertyName.length>0 && textPropertyValue.length>0
                            onClicked: {
                                if(!container.selectedPropertyInfo){
                                    root.node.addPropertyInfo(textPropertyName.text,textPropertyValue.text);
                                }
                                else{
                                    root.node.updatePropertyInfo(container.selectedPropertyInfo,textPropertyName.text,textPropertyValue.text);
                                }
                            }
                        }


                    }
                    Pane{
                        Layout.fillWidth: true
                        Layout.preferredHeight: 75


                        Material.elevation: 8


                        RowLayout{
                            anchors.fill: parent
                            TextField{
                                property bool idvalid: false
                                property string currenttext: ""
                                id:textPropertyName
                                //                                text:

                                Component.onCompleted: {
                                    text=Qt.binding(function(){

                                        if(container.selectedPropertyInfo){
                                            return container.selectedPropertyInfo.propertyName
                                        }

                                        return currenttext

                                    })
                                }

                                onTextChanged: {
                                    if(currenttext!=text){
                                        if(container.selectedPropertyInfo){
                                            var propinfo=root.node.properties.getByName(text)
                                            if(propinfo!=container.selectedPropertyInfo){

                                                container.selectedPropertyInfo=propinfo
                                            }

                                        }

                                        currenttext=text


                                    }


                                }

                                MaterialPlaceHolder{
                                    placeHolderText:"Property Name"
                                }
                            }
                            TextField{
                                id:textPropertyValue
                                text: container.selectedPropertyInfo?container.selectedPropertyInfo.propertyValue:""

                                MaterialPlaceHolder{
                                    placeHolderText:"Property Value"
                                }
                            }
                        }

                    }

                    Button{

                        Layout.fillWidth: true
                        text: "Check from input"
                        highlighted: true

                        onClicked: {
                            root.node.checkPropertyInfo=true
                        }
                    }
                    CheckBox{
                        Layout.fillWidth: true
                        text: "Check on input"
                        checked: root.node.checkOnInput
                        onCheckedChanged: {
                            root.node.checkOnInput=checked
                        }
                    }
                    CheckBox{
                        Layout.fillWidth: true
                        text: "Validate name only"
                        checked: root.node.validatePropertyNameOnly
                        onCheckedChanged: {
                            root.node.validatePropertyNameOnly=checked
                        }
                    }
                }

            }
        }

    }
}
