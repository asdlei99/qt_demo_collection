#include "window.h"

int main() {
    Window w(Point(15,99), 50, 100, Color(22));
    w.show();  /* calls ScreenRegion::show(); */
    w.move (Point(4,6)); /* calls Rectangle::move(); */
    return 0;
 }
