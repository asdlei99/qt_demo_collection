import QtQuick 2.12
import QtQuick.Controls 2.12
import TaoQuick 1.0
import "qrc:/Tao/Qml"
Item {
    anchors.fill: parent
    Image {
        id: src
        source: "qrc:/EffectImage/Img/girl.jpg"
        visible: false
    }
    Grid {
        anchors.centerIn: parent
        columns: 2
        spacing: 40
        ADiagonal {
            id: d1
            width: 460
            height: 280
            dir: ADiagonal.Direct.FromLeftTop
            effectSource.sourceItem: src
        }
        ADiagonal {
            id: d2
            width: 460
            height: 280
            dir: ADiagonal.Direct.FromRightBottom
            effectSource.sourceItem: src
        }
        ADiagonal {
            id: d3
            width: 460
            height: 280
            dir: ADiagonal.Direct.FromRightTop
            effectSource.sourceItem: src
        }
        ADiagonal {
            id: d4
            width: 460
            height: 280
            dir: ADiagonal.Direct.FromLeftBottom
            effectSource.sourceItem: src
        }
    }
    Component.onCompleted: {
        ani.start()
    }
    SequentialAnimation {
        id: ani
        ScriptAction {script: {d1.restart() } }
        PauseAnimation {duration: 1200}
        ScriptAction {script: {d2.restart() } }
        PauseAnimation {duration: 1200}
        ScriptAction {script: {d3.restart() } }
        PauseAnimation {duration: 1200}
        ScriptAction {script: {d4.restart() } }
    }
    Button {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: "replay"
        onClicked: {
            ani.restart()
        }
    }
}
