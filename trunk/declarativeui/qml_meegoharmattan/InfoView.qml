import QtQuick 1.0
import com.nokia.meego 1.0

ListView {
    id: infoList
    model: keyModel
    clip: true
    delegate:
        Item {
            id: listItem
            property bool section: modelData == "section"
            height: 88
            width: parent.width

            BorderImage {
                id: background
                anchors.fill: parent
                // Fill page borders
//                anchors.leftMargin: -listPage.anchors.leftMargin
//                anchors.rightMargin: -listPage.anchors.rightMargin
                visible: mouseArea.pressed
                source: "image://theme/meegotouch-list-background-pressed-center"
            }

            Flow {
//            Row {
//                id: row
                anchors.fill: parent
                anchors.margins: 4
                spacing: 2
//                height: sectionrect.height + mainText.height + subText.height

//                Column {
//                    anchors.verticalCenter: parent.verticalCenter

                    Rectangle {
                        id: sectionRect
                        color: "#2e84e5"
                        visible: section
                        width: listItem.width
                        height: sectionText.height * 2

                        Label {
                            anchors.top: parent
                            anchors.topMargin: sectionText.height
                            id: sectionText
                            text: valueModel[index]
//                            font.family: "Nokia Pure Text"
//                            font.weight: Font.Bold
                            font.pixelSize: 48
                            color: "#ffffff"
                        }
                    }

                    Label {
                        anchors.top: sectionRect.bottom
                        width: listItem.width
                        id: mainText
                        text: modelData
                        font.weight: Font.Bold
                        font.pixelSize: 26
                        visible: !section
                    }

                    Label {
                        anchors.top: mainText.bottom
                        width: listItem.width
                        id: subText
                        text: valueModel[index]
                        font.weight: Font.Light
                        font.pixelSize: 22
                        color: "#cc6633"
                        wrapMode: "WordWrap"

                        visible: !section
//                        visible: text != ""
                    }
//                }
            }

//             Image {
//                 source: "image://theme/icon-m-common-drilldown-arrow" + (theme.inverted ? "-inverse" : "")
//                 anchors.right: parent.right;
//                 anchors.verticalCenter: parent.verticalCenter
//             }

            MouseArea {
                id: mouseArea
                anchors.fill: background
                onClicked: {
//                    listPage.openFile(page)
                }
            }
        }
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

