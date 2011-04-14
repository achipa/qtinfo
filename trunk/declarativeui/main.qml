import Qt 4.7

Rectangle {
    width: 800
    height: 480

    property int itemHeight: 50

    color: "#ffffff"

    Component {
        id: itemDelegate

        Grid {
            columns: 2
            rows: 1
            height: Math.max(itemHeight, Math.max(key.height, value.height))
            width: infoList.width


            property bool section: modelData == "section"

            Rectangle {
                id: key
                height: Math.max(itemHeight, Math.max(keyText.paintedHeight, valueText.paintedHeight))
                width: section ? 0 : 100
                color: "#44a51c"


                Text {
                    id: keyText
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        right: parent.right
                        leftMargin: 5
                        rightMargin: 5
                    }
                    text: section ? "": modelData
                    clip: true
                    wrapMode: Text.Wrap
                    font.pixelSize: 16
                    font.family: "Helvetica"
                }
            }

            Rectangle {
                id: value
                height: Math.max(itemHeight, valueText.paintedHeight)
                width: parent.width - key.width
                color: "#ffffff"

                Text{
                    id: valueText
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        right: parent.right
                        leftMargin: 5
                        rightMargin: 5
                    }
                    text: valueModel[index]
                    clip: true
                    wrapMode: Text.Wrap
                    font.pixelSize: 16
                    font.family: "Helvetica"
                    font.bold: section ? true : false
                }
            }

        }
    }

    ListView {
        id: infoList

        focus: true
        anchors.fill: parent
        delegate: itemDelegate
        model: keyModel
    }
}
