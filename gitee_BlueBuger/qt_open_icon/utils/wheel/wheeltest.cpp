#include "wheeltest.h"

WheelTest::WheelTest(bool touch)
{
    if (QApplication::desktop()->width() > 1000) {
        QFont f = font();
        f.setPointSize(f.pointSize() * 2);
        setFont(f);
    }

    QStringList colors;
    colors << "Red" << "Magenta" << "Peach" << "Orange" << "Yellow" << "Citro" << "Green" << "Cyan" << "Blue" << "Violet";
    stringWheelWidget = new StringWheelWidget(touch);
    stringWheelWidget->setItems(colors);
    stringWheelWidget->setParent(this);
    stringWheelWidget->setFixedSize(100, 200);
    setStyleSheet("background-color:#FFE4C4");
}
