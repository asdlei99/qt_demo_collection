#include <QLayout>
#include <QColorDialog>
#include "PaintWindow.h"

PaintWindow::PaintWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget(this);

    paintArea = new PaintArea(mainWidget);
    shapeLabel = new QLabel(tr("形状:"),mainWidget);
    shapeComboBox = new QComboBox(mainWidget);
    shapeComboBox->addItem(tr("None"),static_cast<int>(PaintArea::Shape::None));
    shapeComboBox->addItem(tr("Line"),static_cast<int>(PaintArea::Shape::Line));
    shapeComboBox->addItem(tr("Rectangle"),static_cast<int>(PaintArea::Shape::Rectangle));
    shapeComboBox->addItem(tr("RoundRect"),static_cast<int>(PaintArea::Shape::RoundRect));
    shapeComboBox->addItem(tr("Ellipse"),static_cast<int>(PaintArea::Shape::Ellipse));
    shapeComboBox->addItem(tr("Polygon"),static_cast<int>(PaintArea::Shape::Polygon));
    shapeComboBox->addItem(tr("Polyline"),static_cast<int>(PaintArea::Shape::Polyline));
    shapeComboBox->addItem(tr("Points"),static_cast<int>(PaintArea::Shape::Points));
    shapeComboBox->addItem(tr("Arc"),static_cast<int>(PaintArea::Shape::Arc));
    shapeComboBox->addItem(tr("Path"),static_cast<int>(PaintArea::Shape::Path));
    shapeComboBox->addItem(tr("Text"),static_cast<int>(PaintArea::Shape::Text));
    shapeComboBox->addItem(tr("Pixmap"),static_cast<int>(PaintArea::Shape::Pixmap));

    penColorLabel = new QLabel(tr("画笔颜色"),mainWidget);
    penColorFrame = new QFrame(mainWidget);
    penColorFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    penColorFrame->setAutoFillBackground(true);
    penColorFrame->setPalette(QPalette(Qt::black));
    penColorBtn = new QPushButton(tr("更改"),mainWidget);

    penWidthLabel = new QLabel(tr("画笔线宽:"),mainWidget);
    penWidthSpinBox = new QSpinBox(mainWidget);
    penWidthSpinBox->setRange(0,20);

    penStyleLabel = new QLabel(tr("画笔风格:"),mainWidget);
    penStyleComboBox = new QComboBox(mainWidget);
    penStyleComboBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("DashDotDotLine"),static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem(tr("CustomDashLine"),static_cast<int>(Qt::CustomDashLine));

    penCapLabel = new QLabel(tr("画笔顶帽:"),mainWidget);
    penCapComboBox = new QComboBox(mainWidget);
    penCapComboBox->addItem(tr("SquareCap"),Qt::SquareCap);
    penCapComboBox->addItem(tr("FlatCap"),Qt::FlatCap);
    penCapComboBox->addItem(tr("RoundCap"),Qt::RoundCap);

    penJoinLabel = new QLabel(tr("画笔连接点:"),mainWidget);
    penJoinComboBox = new QComboBox(mainWidget);
    penJoinComboBox->addItem(tr("BevelJoin"),Qt::BevelJoin);
    penJoinComboBox->addItem(tr("MiterJoin"),Qt::MiterJoin);
    penJoinComboBox->addItem(tr("RoundJoin"),Qt::RoundJoin);

    fillRuleLabel = new QLabel(tr("填充模式:"),mainWidget);
    fillRuleComboBox = new QComboBox(mainWidget);
    fillRuleComboBox->addItem(tr("Odd Even"),Qt::OddEvenFill);
    fillRuleComboBox->addItem(tr("Winding"),Qt::WindingFill);

    spreadLabel = new QLabel(tr("铺展效果:"),mainWidget);
    spreadComboBox = new QComboBox(mainWidget);
    spreadComboBox->addItem(tr("PadSpread"),QGradient::PadSpread);
    spreadComboBox->addItem(tr("RepeatSpread"),QGradient::RepeatSpread);
    spreadComboBox->addItem(tr("ReflectSpread"),QGradient::ReflectSpread);

    brushColorLabel = new QLabel(tr("花刷颜色:"),mainWidget);
    brushColorFrame = new QFrame(mainWidget);
    brushColorFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    brushColorFrame->setAutoFillBackground(true);
    brushColorFrame->setPalette(QPalette(Qt::black));
    brushColorBth = new QPushButton(tr("更改"),mainWidget);

    brushStyleLabel = new QLabel(tr("花刷风格"),mainWidget);
    brushStyleComboBox = new QComboBox(mainWidget);
    brushStyleComboBox->addItem(tr("SolidPattern"),static_cast<int>(Qt::SolidPattern));
    brushStyleComboBox->addItem(tr("Dense1Pattern"),static_cast<int>(Qt::Dense1Pattern));
    brushStyleComboBox->addItem(tr("Dense2Pattern"),static_cast<int>(Qt::Dense2Pattern));
    brushStyleComboBox->addItem(tr("Dense3Pattern"),static_cast<int>(Qt::Dense3Pattern));
    brushStyleComboBox->addItem(tr("Dense4Pattern"),static_cast<int>(Qt::Dense4Pattern));
    brushStyleComboBox->addItem(tr("Dense5Pattern"),static_cast<int>(Qt::Dense5Pattern));
    brushStyleComboBox->addItem(tr("Dense6Pattern"),static_cast<int>(Qt::Dense6Pattern));
    brushStyleComboBox->addItem(tr("Dense7Pattern"),static_cast<int>(Qt::Dense7Pattern));
    brushStyleComboBox->addItem(tr("HorPattern"),static_cast<int>(Qt::HorPattern));
    brushStyleComboBox->addItem(tr("VerPattern"),static_cast<int>(Qt::VerPattern));
    brushStyleComboBox->addItem(tr("CrossPattern"),static_cast<int>(Qt::CrossPattern));
    brushStyleComboBox->addItem(tr("BDiagPattern"),static_cast<int>(Qt::BDiagPattern));
    brushStyleComboBox->addItem(tr("FDiagPattern"),static_cast<int>(Qt::FDiagPattern));
    brushStyleComboBox->addItem(tr("DiagCrossPattern"),static_cast<int>(Qt::DiagCrossPattern));
    brushStyleComboBox->addItem(tr("LinearGradientPattern"),static_cast<int>(Qt::LinearGradientPattern));
    brushStyleComboBox->addItem(tr("ConicalGradientPattern"),static_cast<int>(Qt::ConicalGradientPattern));
    brushStyleComboBox->addItem(tr("RadialGradientPattern"),static_cast<int>(Qt::RadialGradientPattern));
    brushStyleComboBox->addItem(tr("TexturePattern"),static_cast<int>(Qt::TexturePattern));

    QGridLayout *funLayout = new QGridLayout;
    funLayout->addWidget(shapeLabel,0,0);
    funLayout->addWidget(shapeComboBox,0,1);
    funLayout->addWidget(penColorLabel,1,0);
    funLayout->addWidget(penColorFrame,1,1);
    funLayout->addWidget(penColorBtn,1,2);
    funLayout->addWidget(penWidthLabel,2,0);
    funLayout->addWidget(penWidthSpinBox,2,1);
    funLayout->addWidget(penStyleLabel,3,0);
    funLayout->addWidget(penStyleComboBox,3,1);
    funLayout->addWidget(penCapLabel,4,0);
    funLayout->addWidget(penCapComboBox,4,1);
    funLayout->addWidget(penJoinLabel,5,0);
    funLayout->addWidget(penJoinComboBox,5,1);
    funLayout->addWidget(fillRuleLabel,6,0);
    funLayout->addWidget(fillRuleComboBox,6,1);
    funLayout->addWidget(spreadLabel,7,0);
    funLayout->addWidget(spreadComboBox,7,1);
    funLayout->addWidget(brushColorLabel,8,0);
    funLayout->addWidget(brushColorFrame,8,1);
    funLayout->addWidget(brushColorBth,8,2);
    funLayout->addWidget(brushStyleLabel,9,0);
    funLayout->addWidget(brushStyleComboBox,9,1);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(paintArea);
    mainLayout->addLayout(funLayout);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    connect(shapeComboBox,SIGNAL(activated(int)),this,SLOT(slot_showShape(int)));
    connect(penColorBtn,SIGNAL(clicked()),this,SLOT(slot_showPenColor()));
    connect(penWidthSpinBox,SIGNAL(valueChanged(int)),this,SLOT(slot_showPenWidth(int)));
    connect(penStyleComboBox,SIGNAL(activated(int)),this,SLOT(slot_showPenStyle(int)));
    connect(penCapComboBox,SIGNAL(activated(int)),this,SLOT(slot_showPenCap(int)));
    connect(penJoinComboBox,SIGNAL(activated(int)),this,SLOT(slot_showPenJoin(int)));
    connect(fillRuleComboBox,SIGNAL(activated(int)),this,SLOT(slot_showFillRule()));
    connect(spreadComboBox,SIGNAL(activated(int)),this,SLOT(slot_showSpreadStyle()));
    connect(brushColorBth,SIGNAL(clicked()),this,SLOT(slot_showBrushColor()));
    connect(brushStyleComboBox,SIGNAL(activated(int)),this,SLOT(slot_showBrush(int)));
}

PaintWindow::~PaintWindow()
{
    delete paintArea;
}

void PaintWindow::slot_showShape(int value)
{
    PaintArea::Shape shape = PaintArea::Shape(shapeComboBox->itemData(value,Qt::UserRole).toInt());
    paintArea->setShape(shape);
}

void PaintWindow::slot_showPenWidth(int value)
{
    QPen tmpPen = paintArea->retPen();
    tmpPen.setWidth(value);
    paintArea->setPen(tmpPen);
}
void PaintWindow::slot_showPenColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black));
    QPen tmpPen = paintArea->retPen();
    tmpPen.setColor(color);
    paintArea->setPen(tmpPen);
}
void PaintWindow::slot_showPenStyle(int styleValue)
{
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(styleValue,Qt::UserRole).toInt());

    QPen tmpPen = paintArea->retPen();
    tmpPen.setStyle(style);
    paintArea->setPen(tmpPen);
}
void PaintWindow::slot_showPenCap(int capValue)
{
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(capValue,Qt::UserRole).toInt());

    QPen tmpPen = paintArea->retPen();
    tmpPen.setCapStyle(cap);
    paintArea->setPen(tmpPen);
}

void PaintWindow::slot_showPenJoin(int joinValue)
{
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(joinValue,Qt::UserRole).toInt());

    QPen tmpPen = paintArea->retPen();
    tmpPen.setJoinStyle(join);
    paintArea->setPen(tmpPen);
}

void PaintWindow::slot_showFillRule()
{
    Qt::FillRule rule = Qt::FillRule(fillRuleComboBox->itemData(fillRuleComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setFillRule(rule);
}
void PaintWindow::slot_showSpreadStyle()
{
    spread = QGradient::Spread(spreadComboBox->itemData(spreadComboBox->currentIndex(),Qt::UserRole).toInt());
}

void PaintWindow::slot_showBrushColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black));
    brushColorFrame->setPalette(QPalette(color));
    slot_showBrush(brushStyleComboBox->currentIndex());
}

void PaintWindow::slot_showBrush(int)
{
    QColor color = brushColorFrame->palette().color(QPalette::Window);
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(brushStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    if (style == Qt::LinearGradientPattern)
    {
        QLinearGradient linearGradient(0,0,400,400);
        linearGradient.setColorAt(0.0,Qt::white);
        linearGradient.setColorAt(0.2,color);
        linearGradient.setColorAt(1.0,Qt::black);
        paintArea->setBrush(linearGradient);
    }
    else if (style == Qt::RadialGradientPattern)
    {
        QRadialGradient radialGradient(200,200,150,150,100);
        radialGradient.setColorAt(0.0,Qt::white);
        radialGradient.setColorAt(0.2,color);
        radialGradient.setColorAt(1.0,Qt::black);
        radialGradient.setSpread(spread);
        paintArea->setBrush(radialGradient);
    }
    else if (style == Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradient(200,200,30);
        conicalGradient.setColorAt(0.0,Qt::white);
        conicalGradient.setColorAt(0.2,color);
        conicalGradient.setColorAt(1.0,Qt::black);
        paintArea->setBrush(conicalGradient);
    }
    else if (style == Qt::TexturePattern)
    {
        paintArea->setBrush(QPixmap(":/image/image/Xbox.png"));
    }
    else
    {
        paintArea->setBrush(QBrush(color,style));
    }
}
