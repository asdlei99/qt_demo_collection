/**
 ** @author:	   浓咖啡
 ** @date:	   2017.9.26
 ** @brief:      仅做颜色测试使用
 */

#ifndef COLORTEST_H
#define COLORTEST_H

#include <QDialog>

namespace Ui {
class ColorTest;
}

class ColorTest : public QDialog
{
    Q_OBJECT

public:
    explicit ColorTest(QWidget *parent = 0);
    ~ColorTest();

private:
    Ui::ColorTest *ui;
};

#endif // COLORTEST_H
