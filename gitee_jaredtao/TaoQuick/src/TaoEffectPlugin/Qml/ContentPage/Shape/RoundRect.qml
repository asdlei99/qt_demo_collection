import QtQuick 2.12
import QtQuick.Controls 2.12
import TaoQuick 1.0
import "qrc:/Tao/Qml"
Item {
    anchors.fill: parent
    Rectangle {
        x: 10
        width: 100
        height: 160
        color: "red"
    }
    TRoundRect {
        id: roundRect
        x: 40
        y: 10
        width: 200
        height: 160
        radius: 40
        leftTopRound: lt.checked
        rightTopRound: rt.checked
        leftBottomRound: lb.checked
        rightBottomRound: rb.checked
        color: "#A0333666"
    }

    Grid {
        x: 300
        y: 10
        columns: 2
        spacing: 10

        CheckBox {
            id: lt
            text: "LeftTop"
            checked: true
        }
        CheckBox {
            id: rt
            text: "RightTop"
            checked: true
        }
        CheckBox {
            id: lb
            text: "LeftBottom"
            checked: true
        }
        CheckBox {
            id: rb
            text: "rightBottom"
            checked: true
        }
    }
}
