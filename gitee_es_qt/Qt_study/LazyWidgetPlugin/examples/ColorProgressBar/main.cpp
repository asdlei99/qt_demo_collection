#include "ColorProgressBarTest.h"
#include <QApplication>

#include <QLabel>
#include "ColorProgressBar.h"

int run_mode = 2; // 1, call widget directly

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (1 == run_mode) {
        ColorProgressBar bar;
        bar.setValue(30);
        bar.show();
        return a.exec();
    }

    ColorProgressBarTest w;
    w.show();
    return a.exec();

}
