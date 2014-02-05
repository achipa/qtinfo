import QtQuick 2.0
import Sailfish.Silica 1.0


ApplicationWindow {
    id: window

    initialPage: loadingPage

    Page {
        id: loadingPage
        anchors.fill: parent

        PageHeader {
            title: "QtInfo"
        }

/*        Label {
            color: Theme.highlightColor
            font.family: Theme.fontFamilyHeading
        }
*/
/*        BackgroundItem {
            id: container
            anchors.fill: parent
*/
            ProgressBar {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                minimumValue: 0
                maximumValue: 100
                value: 50
                valueText: "Initializing" // value + "%"
                label: "Loading library list"
            }
//        }
    }
}
