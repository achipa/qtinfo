import QtQuick 1.0
import com.nokia.symbian 1.0

ListView {
    id: infoList
    model: keyModel
    clip: true
    delegate: ListItem {
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

    ScrollDecorator {
        id: scrolldecorator
        flickableItem: infoList
    }
}

