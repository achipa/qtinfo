import QtQuick 1.1
import com.nokia.meego 1.1

Rectangle {
    id: container
    anchors.fill: parent


    Component.onCompleted: {
//        console.log(keyModel.length);
        console.log(keyModel);
        var lastSection = "General";
        for (var i=0; i<keyModel.length; i++) {
            if (keyModel[i] == "section") {
                console.log("Z: " + keyModel[i] + " - " + valueModel[i]);
                lastSection = valueModel[i];
            } else {
                dataModel.append({ "key": keyModel[i], "value": valueModel[i], "section": lastSection })
            }
//            console.log("Z: " + keyModel[i]);
        }
        console.log(dataModel);
        console.log(dataModel.count);
        console.log(dataModel.get(20).key);
        console.log(dataModel.get(20).value);
        console.log(dataModel.get(20).section);
    }

    ListModel {  id: dataModel   }

    Component {
            id: sectionHeading
            Rectangle {
                width: container.width
                height: childrenRect.height * 2
                color: "dodgerblue"

                Text {
                    anchors.margins: 5
                    text: section
                    font.family: "Nokia Pure Text"
                    font.weight: Font.Bold
                    font.pixelSize: 48
                    color: "white"
                }
            }
        }

    ListView {
        id: infoList
        anchors.fill: parent
        model: dataModel
        clip: true

        section.property: "section"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading

        delegate: Item {
            height: childrenRect.height
            Rectangle {
                id: titleRect
                width: infoList.width
                height: childrenRect.height * 1.4
                color: "darkorange"
                Label {
                  id: titleText
                  y: 10
                  x: 5
    //            anchors {
    //                top: titleText.bottom
    //                bottom: listItem.paddingItem.bottom
    //                left: listItem.paddingItem.left
    //                right: listItem.paddingItem.right
    //            }

    //            opacity: section ? 0 : 1
    //            color: "gray"
    //            text: valueModel[index]
                  text: key
                  anchors.margins: 5
                  platformStyle: LabelStyle { fontPixelSize: 32; textColor: "white" }
    //            text: "ASDF"
    //              wrapMode: Text.WrapAnywhere
                }
            }
            Text {
                id: subtitleText
                width: infoList.width - 2*x
                anchors {
                    top: titleRect.bottom; margins: 10
                }
                x: 10
                color: "dimgray"
                font.family: "Nokia Pure Text"
//                font.weight: Font.Bold
                font.pixelSize: 22

                text: value
                wrapMode: Text.Wrap
            }

        }

            /*
          ListItem {
            id: listItem
            property bool section: modelData == "section"

            height: section ? titleText.height + listItem.paddingItem.anchors.topMargin + listItem.paddingItem.anchors.bottomMargin
                            : titleText.height + subtitleText.paintedHeight + listItem.paddingItem.anchors.topMargin + listItem.paddingItem.anchors.bottomMargin

            Rectangle {
                anchors.fill: parent
                color: "gray"
                opacity: section ? 1 : 0
            }

            ListItemText {
                id: titleText
                anchors {
                    left: listItem.paddingItem.left
                    right: listItem.paddingItem.right
                    top: listItem.paddingItem.top
                }

                mode: listItem.mode
                role: section ? "Heading" : "Title"
                text: section ? valueModel[index] : modelData
            }
            Text {
                id: subtitleText
                anchors {
                    top: titleText.bottom
                    bottom: listItem.paddingItem.bottom
                    left: listItem.paddingItem.left
                    right: listItem.paddingItem.right
                }

                opacity: section ? 0 : 1
                color: "gray"
                text: section ? "" : valueModel[index]
                wrapMode: Text.WrapAnywhere
            }
        }
*/
        ScrollDecorator {
            id: scrolldecorator
            flickableItem: infoList
        }
    }
}

/*
ListView {
    id: infoList
    model: sectionModel
//    model: keyModel
    clip: true
    cacheBuffer: 2000
    delegate: valueDelegate
    section.delegate: sectionDelegate
    section.property: "section"
//    section.property: modelData
Component {
    id: sectionDelegate
    Rectangle {
        id: sectionRect
        color: "#2e84e5"
        width: listItem.width
        height: sectionText.height * 2

        Label {
            anchors.top: parent
            anchors.topMargin: sectionText.height
            id: sectionText
            text: section
//            text: valueModel[index]
//                            font.family: "Nokia Pure Text"
//                            font.weight: Font.Bold
            font.pixelSize: 48
            color: "#ffffff"
        }
    }
}

Component {
    id: valueDelegate
//        anchors.fill: parent
//        anchors.margins: 4
    Flow {
//            Row {
//                id: row
        spacing: 2
//                height: sectionrect.height + mainText.height + subText.height

//                Column {
//                    anchors.verticalCenter: parent.verticalCenter


        Label {
//            width: listItem.width
            id: mainText
            text: key
//            text: modelData
            font.weight: Font.Bold
            font.pixelSize: 26
        }

        Label {
            anchors.top: mainText.bottom
//            width: listItem.width
            id: subText
            text: value
//            text: valueModel[index]
            font.weight: Font.Light
            font.pixelSize: 22
            color: "#cc6633"
            wrapMode: "WordWrap"

        }
//                }
    }
}
//        Item {
//            id: listItem
//            property bool section: modelData == "section"
////            height: 88
//            width: parent.width

//            BorderImage {
//                id: background
//                anchors.fill: parent
//                // Fill page borders
////                anchors.leftMargin: -listPage.anchors.leftMargin
////                anchors.rightMargin: -listPage.anchors.rightMargin
//                visible: mouseArea.pressed
//                source: "image://theme/meegotouch-list-background-pressed-center"
//            }


////             Image {
////                 source: "image://theme/icon-m-common-drilldown-arrow" + (theme.inverted ? "-inverse" : "")
////                 anchors.right: parent.right;
////                 anchors.verticalCenter: parent.verticalCenter
////             }

//            MouseArea {
//                id: mouseArea
//                anchors.fill: background
//                onClicked: {
////                    listPage.openFile(page)
//                }
//            }
//        }
//        ListItem {
//        id: listItem
//        property bool section: modelData == "section"

//        height: section ? titleText.height + listItem.paddingItem.anchors.topMargin + listItem.paddingItem.anchors.bottomMargin
//                        : titleText.height + subtitleText.paintedHeight + listItem.paddingItem.anchors.topMargin + listItem.paddingItem.anchors.bottomMargin

//        Rectangle {
//            anchors.fill: parent
//            color: "gray"
//            opacity: section ? 1 : 0
//        }

//        ListItemText {
//            id: titleText
//            anchors {
//                left: listItem.paddingItem.left
//                right: listItem.paddingItem.right
//                top: listItem.paddingItem.top
//            }

//            mode: listItem.mode
//            role: section ? "Heading" : "Title"
//            text: section ? valueModel[index] : modelData
//        }
//        Text {
//            id: subtitleText
//            anchors {
//                top: titleText.bottom
//                bottom: listItem.paddingItem.bottom
//                left: listItem.paddingItem.left
//                right: listItem.paddingItem.right
//            }

//            opacity: section ? 0 : 1
//            color: "gray"
//            text: section ? "" : valueModel[index]
//            wrapMode: Text.WrapAnywhere
//        }
//    }

    ScrollDecorator {
        id: scrolldecorator
        flickableItem: infoList
    }
    SectionScroller {
        listView: infoList
    }
}

*/
