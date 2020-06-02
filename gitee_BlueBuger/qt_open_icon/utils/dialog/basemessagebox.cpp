#include "basemessagebox.h"
#include "assert.h"

/**
 * @brief 基础提示框组件
 * @param labIcon 提示框icon图标，需要外部初始化后传入
 * @param title 标题
 * @param info 提示信息
 * @param style 样式，没有用默认
 * @param showCancel 是否显示cancel按钮
 * @param w 宽
 * @param h 高
 */
BaseMessageBox::BaseMessageBox(BaseLabel *labIcon, const QString &title, \
                               const QString &info, const QString &style,\
                               bool showCancel, int w, int h)
    :mousePressed(false)
{
    assert(labIcon != NULL);
    this->labIcon = labIcon;
    labIcon->setFixedSize(20, 20);
    labIcon->setObjectName("labIcon");
    QLabel *labTitle = new QLabel(title);
    labTitle->setObjectName("labTitle");

    //标题栏
    QWidget *titleWig = new QWidget;
    titleWig->setObjectName("titleWig");
    titleWig->setFixedHeight(30);

    closeBtn = new BaseButton(FontawesomeWebfont(), FontawesomeWebfont::ICON_CLOSE, 40, 30);
    closeBtn->setObjectName("closeBtn");
    QHBoxLayout *titleLay = new QHBoxLayout(titleWig);
    titleLay->addSpacing(10);
    titleLay->addWidget(labIcon);
    titleLay->addWidget(labTitle);
    titleLay->addStretch(1);
    titleLay->addWidget(closeBtn);
    titleLay->setMargin(0);
    titleLay->setSpacing(0);

    //提示信息
    QLabel *labInfo = new QLabel;
    labInfo->setObjectName("labInfo");
    labInfo->setMinimumHeight(100);
    labInfo->setWordWrap(true);
    labInfo->setText(info);

    //按钮部分
    QWidget *btnWig = new QWidget;
    btnWig->setMinimumSize(200, 60);
    okBtn = new QPushButton("确定");
    okBtn->setMinimumSize(60, 30);
    cancelBtn = new QPushButton("取消");
    cancelBtn->setMinimumSize(60, 30);
    okBtn->setFocusPolicy(Qt::NoFocus);
    cancelBtn->setFocusPolicy(Qt::NoFocus);
    utilscommon::setShadow(okBtn);
    utilscommon::setShadow(cancelBtn);
    QHBoxLayout *btnLay = new QHBoxLayout(btnWig);
    btnLay->addStretch(1);
    btnLay->addWidget(cancelBtn);
    btnLay->addSpacing(10);
    btnLay->addWidget(okBtn);
    btnLay->setMargin(20);

    if(!showCancel){
        cancelBtn->hide();
    }

    //主布局
    QVBoxLayout *mainLay = new QVBoxLayout;
    mainLay->setMargin(0);
    mainLay->setSpacing(0);
    mainLay->addWidget(labInfo, 1);
    mainLay->addWidget(btnWig);

    //总布局
    QVBoxLayout *totalLay = new QVBoxLayout(this);
    totalLay->addWidget(titleWig);
    totalLay->addLayout(mainLay);
    totalLay->setMargin(0);
    totalLay->setSpacing(0);

    setStyle(style);
    setMinimumSize(250, 150);
    resize(w, h);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    showInCenter();

    connect(closeBtn, SIGNAL(btnReleased()), this, SLOT(cancelSlot()));
    connect(cancelBtn, SIGNAL(released()), this, SLOT(cancelSlot()));
    connect(okBtn, SIGNAL(released()), this, SLOT(okSlot()));
}

/**
 * @brief 设置样式
 */
void BaseMessageBox::setStyle(const QString &style)
{
    QString qss;
    if(style == QString()){
        qss = utilscommon::readFile(":/qss/resourse/qss/dialog/default.qss");
    }else{
        qss = style;
    }

    this->setStyleSheet(qss);
    labIcon->setStyleSheet(qss);
    closeBtn->setStyleSheet(qss);
}

/**
 * 窗体居中显示
 */
void BaseMessageBox::showInCenter()
{
    int frmX = width();
    int frmY = height();
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    this->move(movePoint);
}

void BaseMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void BaseMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void BaseMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void BaseMessageBox::okSlot()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(doneOk()));
}

void BaseMessageBox::cancelSlot()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(200);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(doneCancel()));
}

void BaseMessageBox::doneOk()
{
    done(OK);
}

void BaseMessageBox::doneCancel()
{
    done(CANCEL);
}

