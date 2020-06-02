﻿import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Window {
    objectName: "rootObject";
    visible: true
    width: 360
    height: 360

    Text {
        objectName: "textLabel";
        text: "Hello World";
        anchors.centerIn: parent;
        font.pixelSize: 26
    }

    Button {
        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        text: "quit";
        objectName: "quitButton";
    }
}
