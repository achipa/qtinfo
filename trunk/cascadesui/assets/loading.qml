// List with a context menu project template
import bb.cascades 1.0
//import com.rim.example.custom 1.0

Page {
    content: Container {
        layout: DockLayout {
        }
        TextArea {
            id: loadTicker
            objectName: "loadTicker"
            editable: false
            text: "Starting QtInfo"
            verticalAlignment: VerticalAlignment.Top
            horizontalAlignment: HorizontalAlignment.Center
        }
        ImageView {
            id: logo
            imageSource: "qtinfo.png"
//            preferredWidth: 256
//            preferredHeight: 256
            scaleX: 2.0
            scaleY: 2.0
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
        }
        ProgressIndicator {
            id: progress
            objectName: "progress"
            fromValue: 0
            toValue: 100
            verticalAlignment: VerticalAlignment.Bottom
            horizontalAlignment: HorizontalAlignment.Center
        }
    }

    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("Page loading - onCreationCompleted()")

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
}
