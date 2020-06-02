#ifndef LZRADIOBUTTONVIEW_H
#define LZRADIOBUTTONVIEW_H

#include <QDialog>
#include <QRadioButton>
#include <QButtonGroup>
#include <QToolButton>
#include <QLabel>

class LzRadioButtonView : public QDialog
{
    Q_OBJECT
public:

    // 设备操作模式类型（用于表示普通QButtonGroup）
    typedef enum {
        OM_Auto,
        OM_Manual,
        OM_ManualFullSpeed
    }operatingModeTypes;

    // 动物选项类型（用于表示QToolButton模拟的单选按钮）
    typedef enum {
        AN_PIG,
        AN_MONKEY,
        AN_CAT
    }animalTypes;

    explicit LzRadioButtonView(QWidget *parent = nullptr);
    ~LzRadioButtonView();

private slots:
    void operatingModeButtonsToggled(int, bool);
    void operatingModeButtonsClicked(int);

//    void customButtonsToggled(int, bool);
//    void customButtonsClicked(int);

private:
    // 设备操作模式组
    QButtonGroup *operatingModeGroup;
    QRadioButton *autoBtn;
    QRadioButton *manualBtn;
    QRadioButton *manualFullSpeedBtn;

    // 电源开关组
    QButtonGroup *powerGroup;
    QRadioButton *powerOnBtn;
    QRadioButton *powerOffBtn;

    // 动物选项组
//    QButtonGroup *customGroup;
//    QStringList animalStrList;  // 记录动物名称
//    QLabel *curAnimalLabel;     // 显式当前选中的动物名称
};

#endif // LZRADIOBUTTONVIEW_H
