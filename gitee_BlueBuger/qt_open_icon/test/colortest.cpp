/**
 ** @author:	   浓咖啡
 ** @date:	   2017.9.26
 ** @brief:      仅做颜色测试使用
 */

#include "colortest.h"
#include "ui_colortest.h"

ColorTest::ColorTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorTest)
{
    ui->setupUi(this);
}

ColorTest::~ColorTest()
{
    delete ui;
}
