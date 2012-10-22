// List with a context menu project template
import bb.cascades 1.0
//import com.rim.example.custom 1.0

Page {
    content: Container {
        layout: DockLayout {
        }
        ListView {
            Component.onCompleted: { console.log("yay"); }
            id: listView
            objectName: "listView"
            horizontalAlignment: HorizontalAlignment.Center
            dataModel: MyListModel {
                id: myListModel
            }
            property int activeItem: -1
            contextActions: [
            ActionSet {
                // put context menu actions here
                title: qsTr("Picture actions")
                subtitle: qsTr("Set of the useful things to do ...")
                ActionItem {
                    title: qsTr("Break")
                    onTriggered: {
                        // define action handler here
                        console.log ("action triggered: " + title + " active item: " + listView.activeItem)
                        var flags = myListModel.value(listView.activeItem, "flags");
                        if(!flags) flags = {};
                        flags.broken = !flags.broken;
                        title = flags.broken? qsTr("Unbreak"): qsTr("Break");
                        myListModel.setValue(listView.activeItem, "flags", flags)
                        myListModel.setValue(listView.activeItem, "image", assetForFlags(flags));
                        myListModel.setValue(listView.activeItem, "status", statusForFlags(flags));
                    }
                }
                ActionItem {
                    title: qsTr("Hide")
                    onTriggered: {
                        console.log ("action triggered: " + title)
                        var flags = myListModel.value(listView.activeItem, "flags");
                        if(!flags) flags = {};
                        flags.hidden = !flags.hidden;
                        title = flags.hidden? qsTr("Show"): qsTr("Hide");
                        myListModel.setValue(listView.activeItem, "flags", flags)
                        myListModel.setValue(listView.activeItem, "image", assetForFlags(flags));
                        myListModel.setValue(listView.activeItem, "status", statusForFlags(flags));
                    }
                }
            }
            ]
            // Override default GroupDataModel::itemType() behaviour, which is to return item type "header"
            listItemComponents: [
            // define delegates for different item types here
            ListItemComponent {
                // StandardListItem is a convivience component for lists with default cascades look and feel
                StandardListItem {
                    title: ListItemData.text
                    description: ListItemData.description
                    status: ListItemData.status
                    imageSource: ListItemData.image
                }
            }
            ]
            onSelectionChanged: {
                // slot called when ListView emits selectionChanged signal
                // A slot naming convention is used for automatic connection of list view signals to slots
                console.log ("onSelectionChanged, selected: " + selected)
            }
            onActivationChanged: {
                console.log ("onActivationChanged, active: " + active)
                if(active) listView.activeItem = indexPath[0]
            }
        }
    }
    function assetForFlags(flags) {
        var ret = "asset:///images/picture1.png";
        if(flags.hidden) ret = null;
        else if(flags.broken) ret = "asset:///images/picture2.png";
        return ret;
    }
    function statusForFlags(flags) {
        var ret = "";
        if(flags.hidden) ret = qsTr("hidden");
        if(flags.broken) {
            if(ret) ret += ", ";
            ret += qsTr("broken");
        }
        return ret;
    }
    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("Page - onCreationCompleted()")

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;

        // populate list view model with the sample data
        myListModel.load("app/native/assets/mydata.json")
    }
}
