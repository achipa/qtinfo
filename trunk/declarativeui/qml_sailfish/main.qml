import QtQuick 1.1
import Sailfish.Silica 1.0


ApplicationWindow {
    id: window
//    initialPage: MainPage {}

//    showStatusBar: true
//    showToolBar: true

//    StatusBar {
//        id: statusBar
//        anchors.top: window.top
//    }

//    PageStack {
//        id: pageStack
//        anchors { left: parent.left; right: parent.right; top: statusBar.bottom; bottom: toolBar.top }

//        toolBar: toolBar
//    }

//    ToolBar {
//        id: toolBar
//        anchors.bottom: window.bottom
//        tools: ToolBarLayout {
//            id: toolBarLayout
//            ToolButton {
//                flat: true
//                iconSource: "toolbar-back"
//                onClicked: pageStack.depth <= 1 ? Qt.quit() : pageStack.pop()
//            }
//        }
//    }


    Component.onCompleted: {
        pageStack.push(Qt.resolvedUrl("MainPage.qml"))
    }
    
}
