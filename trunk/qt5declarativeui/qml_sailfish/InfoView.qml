import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
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

            BackgroundItem {
                width: container.width
//                height: childrenRect.height * 2
//                color: "dodgerblue"

                Label {
                    anchors.margins: 5
                    text: section
                    color: Theme.highlightColor
                    font.family: Theme.fontFamilyHeading
                    font.pixelSize: Theme.fontSizeLarge
//                    font.family: "Nokia Pure Text"
                    font.weight: Font.Bold
//                    font.pixelSize: 48
//                    color: "white"
                }
            }
        }

    SilicaListView {
        id: infoList
        anchors.fill: parent
        model: dataModel
        clip: true


        PullDownMenu {
                 MenuItem {
                     text: "Share via email"
                     onClicked: console.log("Clicked option 1")
                 }
                 MenuItem {
                     text: "Share via pastebin"
                     onClicked: console.log("Clicked option 2")
                 }
                 MenuItem {
                     text: "Save to file"
                     onClicked: console.log("Clicked option 3")
                 }
                 MenuItem {
                     text: "Copy to clipboard"
                     onClicked: console.log("Clicked option 4")
                 }
        }

        section.property: "section"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading

        delegate: Item {
            height: childrenRect.height
            BackgroundItem {
//            Item {
                id: titleRect
                width: infoList.width
//                height: childrenRect.height * 1.4
//                color: "darkorange"
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
                  color: Theme.highlightColor
                  font.family: Theme.fontFamilyHeading
                  font.pixelSize: Theme.fontSizeMedium
////////                  platformStyle: LabelStyle { fontPixelSize: 32; textColor: "white" }
    //            text: "ASDF"
    //              wrapMode: Text.WrapAnywhere
                }
            }
            Label {
                id: subtitleText
                width: infoList.width - 2*x
                anchors {
                    top: titleRect.bottom; margins: 10
                }
                x: 10
//                color: "dimgray"
//                font.family: "Nokia Pure Text"
//                font.weight: Font.Bold
//                font.pixelSize: 22

                color: Theme.secondaryColor
                font.family: Theme.fontFamily
                font.pixelSize: Theme.fontSizeMedium

                text: value + "<BR>"
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
        VerticalScrollDecorator {
            id: scrolldecorator
            flickable: infoList
        }
    }
}

