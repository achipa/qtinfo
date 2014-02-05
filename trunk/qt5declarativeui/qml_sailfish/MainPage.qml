import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: mainPage
    anchors {
        fill: parent
    }
    PageHeader {
        title: "QtInfo"
    }

    InfoView {
        anchors.fill: parent
    }

}

