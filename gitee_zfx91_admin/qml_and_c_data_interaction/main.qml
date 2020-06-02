import QtQuick 2.0

Rectangle
{
    id: mainWindow

    x: 30; y: 80; width: 1000; height: 800;


    GridView{
        id:designBox
        anchors.fill: parent
//        cellWidth: 82; cellHeight: 128;
        objectName: "designBox"
        Component.onCompleted: {
            designBox.model = DesignBLL.getModel();
        }
        delegate:Rectangle{
                height: 50
                width: 50
                color:model.modelData.backColor

                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        designBox.model[index].backColor = "#969696";
                    }
                }
            }
        }
}
