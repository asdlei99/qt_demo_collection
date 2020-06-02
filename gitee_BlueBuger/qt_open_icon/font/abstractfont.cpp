/**
 ** @author:	   浓咖啡
 ** @date:	   2015.4.15
 ** @brief:      字体库基类
 ** 使用步骤:
 ** 1.按照官网教程增加字体库文件XX.ttf
 ** 2.把相应的资源文件添加到resource.qrc中
 ** 3.仿照MuiFont类增加相应的类文件,注意类构造传递字符串要和文件名相同
 ** 4.使用
 */

#include "abstractfont.h"

#define FONT_PATH ":/font/resourse/font/"

/**
 * @brief 所有子类都要调用这个构造
 * @param _name 字体库名称，也是代表ttf文件名称，会根据此名称加载字体库
 */
AbstractFont::AbstractFont(const QString &_name)
{
    name = _name;
    int fontId=QFontDatabase::addApplicationFont(FONT_PATH + _name + QString(".ttf"));
    QString fontName=QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);
}
