import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Video list demo")

    VideoDialogQml {
        id: videoDialogQml
        modality: Qt.WindowModal
    }

    VideoDialogCpp {
        id: videoDialogCpp
        modality: Qt.WindowModal
    }

    Flow {
        id: flowTop
        anchors.fill: parent
        anchors.margins: 4
        spacing: 4
        Button {
            id: buttonShowVideoQml
            text: "Show Video(qml)"
            onClicked: videoDialogQml.open();
        }

        Button {
            id: buttonShowVideoCpp
            text: "Show Video(cpp)"
            onClicked: videoDialogCpp.open();
        }
    }
}
