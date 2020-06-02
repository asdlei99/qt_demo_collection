import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.3

Window {
    id: mainWindow
    visible: true
    width: item_w*row_size + (row_size + 1)*item_space;
    height: item_h*column_size + (column_size + 1)*item_space;

    //矩形的大小
    property int item_w: 25;
    property int item_h: 25;

    //矩形与矩形的间距
    property int item_space: 1;

    property int row_size: control.getRow();
    property int column_size: control.getColumn();

    title: qsTr("扫雷")
    color: "gray"


    GridView{
        id:designBox
        anchors.fill: parent
        cellWidth: (row_size + 1)*item_space;
        cellHeight: (column_size + 1)*item_space;
        objectName: "designBox"
        Component.onCompleted: {
            designBox.model = control.getModel();
        }
        delegate: Image{
            id: rectItem
            height: item_w; width: item_h
            source: "qrc:/image/blank.jpg"
            smooth: true

            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    rectItem.source = control.getPath(index)
                    if(!control.clickItem(index))
                    {
                        infoWidget.visible = true;
                    }
                }
            }
        }
    }

    Item {
        id: infoWidget;
        width: 200; height: 80;
        x: (mainWindow.width - infoWidget.width) / 2;
        y: (mainWindow.height - infoWidget.height) / 2;

        visible: false;
        Text {
            color: "red"
            font.pointSize: 80;
            text: qsTr("失败")
        }
    }


//    DifficultyWidget {
//        id: difficultyWidget
//        width: mainWindow.width; height: mainWindow.height;
//    }

}
