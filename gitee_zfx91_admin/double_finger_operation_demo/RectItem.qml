import QtQuick 2.0

Rectangle {
    id: rectItem

    property point touchPoint: Qt.point(0, 0);

    Rectangle {
        id: targetItem
        x: 100; y: 100; width: 150; height: 80;
        color: "white";
    }

    function touchPointChange() {
        var targetX = touchPoint.x - rectItem.x - targetItem.x;
        var targetY = touchPoint.y - rectItem.y - targetItem.y;
        var flag = targetItem.contains(Qt.point(120, 120));
        //console.log("~~~~~",rectItem.x,rectItem.y , targetX, targetY)

        if(targetX >= 0 && targetX <= targetItem.width &&
                targetY >= 0 && targetY <= targetItem.height)
        {
            targetItem.color = "black"
        }
        else
            targetItem.color = "white"
    }

    onTouchPointChanged: touchPointChange();
}
