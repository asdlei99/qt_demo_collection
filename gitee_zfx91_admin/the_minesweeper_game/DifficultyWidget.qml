import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle
{
    id: difficultyWidget


    Button {
        id: btn1;
        width: 100; height: 60;
        Text {
            font.pointSize: 40;
            text: qsTr("简单")
        }
    }

    Button {
        id: btn2;
        width: 100; height: 60;
        Text {
            font.pointSize: 40;
            text: qsTr("普通")
        }
    }

    Button {
        id: btn3;
        width: 100; height: 60;
        Text {
            font.pointSize: 40;
            text: qsTr("中级")
        }
    }

    Button {
        id: btn4;
        width: 100; height: 60;
        Text {
            font.pointSize: 40;
            text: qsTr("高级")
        }
    }
}
