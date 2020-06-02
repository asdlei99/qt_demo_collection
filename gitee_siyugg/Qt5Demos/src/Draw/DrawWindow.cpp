#include "DrawWindow.h"
#include "DrawArea.h"
#include "ui_DrawWindow.h"
#include <QLabel>
#include <QComboBox>
#include <QAction>
#include <QSpinBox>
#include <QColorDialog>
#include <QIcon>
#include <QVariant>
#include <QCursor>

DrawWindow::DrawWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::DrawWindow),drawArea(new DrawArea(this)),styleLabel(new QLabel(tr("线型选择"),this)),styleBox(new QComboBox(this)),
    widthLabel(new QLabel(tr("线宽选择"),this)),widthBox(new QSpinBox(this)),colorAct(new QAction(this)),clearAct(new QAction(tr("清除"),this))

{
    ui->setupUi(this);
    setCentralWidget(drawArea);
//    setCursor(QCursor(QPixmap(":/icon/pencil.png")));

    colorAct->setIcon(QIcon(":/icon/selectcolor.png"));

    currentStyleLabel = new QLabel(tr("Style : SolidLine"),this);
    currentWidthLabel = new QLabel(tr("Width : 1"),this);
    ui->statusBar->addWidget(currentStyleLabel);
    ui->statusBar->addWidget(currentWidthLabel);

    widthBox->setValue(1);
    widthBox->setMaximum(20);
    widthBox->setMinimum(0);
    createTools();

    connect(colorAct,SIGNAL(triggered()),this,SLOT(selectColor()));
    connect(styleBox,SIGNAL(activated(int)),drawArea,SLOT(setPenStyle(int)));
    connect(styleBox,SIGNAL(activated(QString)),this,SLOT(showCurrentStyle(QString)));
    connect(widthBox,SIGNAL(valueChanged(int)),drawArea,SLOT(setPenWidth(int)));
    connect(widthBox,SIGNAL(valueChanged(QString)),this,SLOT(showCurrentWidth(QString)));
    connect(clearAct,SIGNAL(triggered()),drawArea,SLOT(clear()));
}

DrawWindow::~DrawWindow()
{
    delete ui;
}

void DrawWindow::createTools()
{
    styleBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    styleBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
    styleBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
    styleBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotLine));
    styleBox->addItem(tr("DashDotDotLine"),static_cast<int>(Qt::DashDotDotLine));
    styleBox->addItem(tr("CustomDashLine"),static_cast<int>(Qt::CustomDashLine));

    ui->mainToolBar->addWidget(styleLabel);
    ui->mainToolBar->addWidget(styleBox);
    ui->mainToolBar->addWidget(widthLabel);
    ui->mainToolBar->addWidget(widthBox);
    ui->mainToolBar->addAction(colorAct);
    ui->mainToolBar->addAction(clearAct);
}
void DrawWindow::selectColor()
{
    QColor color = QColorDialog::getColor(Qt::white,this,tr("选择颜色"));
    if (color.isValid())
        drawArea->setPenColor(color);
}

void DrawWindow::showCurrentStyle(QString _style)
{
    currentStyleLabel->setText(QString("Style : ") + _style);
}
void DrawWindow::showCurrentWidth(QString _width)
{
    currentWidthLabel->setText(QString("Width : ") + _width);
}
