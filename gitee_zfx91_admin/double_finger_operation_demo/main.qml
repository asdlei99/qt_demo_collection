import QtQuick 2.9
import QtQuick.Window 2.0

Window {
    id: mainWindow
    visible: true
    width: 1000
    height: 500
    title: qsTr("Hello World")



    RectItem {
        id: leftWidget;
        x: 0; y: 0; width: mainWindow.width/2; height: mainWindow.height;
        color: "#EED5B7"
    }

    RectItem {
        id: rightWidget;
        x: leftWidget.width + leftWidget.x; y: 0; width: mainWindow.width/2; height: mainWindow.height;
        color: "#EEA9B8"
    }

    Rectangle {
        width: 30; height: 30
        color: "green"
        x: touch1.x
        y: touch1.y
    }

    Rectangle {
        width: 30; height: 30
        color: "yellow"
        x: touch2.x
        y: touch2.y
    }

    function touchChange(itemX, itemY)
    {
        if(itemX > 0 && itemX < rightWidget.x)
            return 0;
        else if(itemX> rightWidget.x && (itemX < rightWidget.x + rightWidget.width))
            return 1;
        else
            return 3;
    }

    function updatePoints(touchPoints) {
        for(var i = 0; i < touchPoints.length; i++)
        {
            var type = touchChange(touchPoints[i].x, touchPoints[i].y);
            console.log("~~~~~~~~~~~~~~~" , type, touchPoints[i].x, touchPoints[i].y, i, rightWidget.x)
            switch(type) {
            case 0:
                leftWidget.touchPoint = Qt.point(touchPoints[i].x, touchPoints[i].y)
                break;
            case 1:
                rightWidget.touchPoint = Qt.point(touchPoints[i].x, touchPoints[i].y)
                break;
            }
        }
    }

    MultiPointTouchArea {
        anchors.fill: parent
        minimumTouchPoints: 1
        maximumTouchPoints: 2
        touchPoints: [
            TouchPoint { id: touch1 },
            TouchPoint { id: touch2 }
        ]
        onTouchUpdated: updatePoints(touchPoints)
        onUpdated: updatePoints(touchPoints)
    }

}
