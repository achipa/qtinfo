import QtQuick 1.0
import com.nokia.symbian 1.0
import com.nokia.extras 1.0

Page {
    id: mainPage
    anchors {
        fill: parent
    }

    InfoView {
        anchors.fill: parent
    }

    tools: ToolBarLayout {
            id: toolBarLayout
            ToolButton {
                flat: true
                iconSource: "toolbar-back"
                onClicked: Qt.quit()
            }
            ToolButton {
                text: "Share"
                onClicked: shareDialog.open()
            }
            ToolButton {
                text: "Copy"
                onClicked: copyDialog.open()
            }
            ToolButton {
                flat: true
                iconSource: "toolbar-menu"
                onClicked: menu.open()
            }
    }

    SelectionDialog {
         id: shareDialog
         titleText: "Share"
         model: ["to Pastebin", "to e-mail"]
         onAccepted: {
             if (selectedIndex == 0) {
                 MainWindow.on_jsbinButton_clicked(true)
                 banner.text = "Opening pastebin"
                 banner.open()
             } else if (selectedIndex == 1) {
                 MainWindow.on_emailButton_clicked(true)
                 banner.text = "Opening e-mail"
                 banner.open()
             }
         }
    }

    SelectionDialog {
         id: copyDialog
         titleText: "Copy"
         model: ["to Clipboard", "to File"]
         onAccepted: {
             if (selectedIndex == 0) {
                 MainWindow.on_clipboardButton_clicked(true)
                 banner.text = "Copied to clipboard"
                 banner.open()
             } else if (selectedIndex == 1) {
                 MainWindow.on_saveButton_clicked(true)
                 banner.text = "Saved to file"
                 banner.open()
             }
         }
    }

    InfoBanner {
        id: banner
    }

    Menu {
         id: menu

         content: MenuLayout {
             MenuItem {
                 text: "Exit"
                 onClicked: Qt.quit()
             }
         }
    }
}

