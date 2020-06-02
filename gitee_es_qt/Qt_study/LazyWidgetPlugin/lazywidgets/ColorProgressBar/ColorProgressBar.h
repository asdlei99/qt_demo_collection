#ifndef COLORPROGRESSBAR_H
#define COLORPROGRESSBAR_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QWidget>

class ColorProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double Min READ getMin WRITE setMin)
    Q_PROPERTY(double Max READ getMax WRITE setMax)
    Q_PROPERTY(double Value READ getValue WRITE setValue)
    Q_PROPERTY(QColor BarBackGroundColor READ getBarBackGroundColor WRITE setBarBackGroundColor)
    Q_PROPERTY(QColor BarSplitLineColor READ getBarSplitLineColor WRITE setBarSplitLineColor)
    Q_PROPERTY(QColor BarColor READ getBarColor WRITE setBarColor)
    Q_PROPERTY(int Decimal READ getDecimal WRITE setDecimal)
    Q_PROPERTY(int BarSplitLineDelta READ getBarSplitLineDelta WRITE setBarSplitLineDelta)
    Q_PROPERTY(bool ShowBarSplitLine READ getShowBarSplitLine WRITE setShowBarSplitLine)
    Q_PROPERTY(int Space READ getSpace WRITE setSpace)
public:
    explicit ColorProgressBar(QWidget *parent = nullptr);
    ~ColorProgressBar();

    double getMin() const { return m_min; }
    void setMin(double min) { m_min = min; }
    double getMax() const { return m_max; }
    void setMax(double max) { m_max = max; }
    QColor getBarBackGroundColor() const { return m_barBackGroundColor; }
    void setBarBackGroundColor(QColor color);
    QColor getBarSplitLineColor() { return m_barSplitLineColor; }
    void setBarSplitLineColor(QColor color);
    QColor getBarColor() const { return m_barColor; }
    void setBarColor(QColor color);
    int getDecimal() const { return m_decimal; }
    void setDecimal(int decimal);
    int getBarSplitLineDelta() const { return m_barSplitLineDelta; }
    void setBarSplitLineDelta(int delta);
    bool getShowBarSplitLine() const { return m_showBarSplitLine; }
    void setShowBarSplitLine(bool show);
    int getSpace() const { return m_space; }
    void setSpace(int space);

public slots:
    double getValue() const { return m_value; }
    void setValue(double value);
    void setValue(int value);


protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void drawBackGround(QPainter& p, const QRectF& barRect, const QRectF& textRect);
    virtual void drawData(QPainter& p, const QRectF& barRect);
    virtual void drarBarSplitLine(QPainter& p, const QRectF& barRect);
    virtual void drawText(QPainter& p, const QRectF& textRect);
    virtual QSize sizeHint() const override { return QSize(300, 30); }

private:
    double m_min,m_max,m_value;
    QColor m_barBackGroundColor;//背景颜色
    QColor m_barSplitLineColor;//背景分割线颜色
    int m_barSplitLineDelta;//背景分割线间距
    bool m_showBarSplitLine;//是否显示背景分割线
    QColor m_barColor;
    int m_decimal;
    int m_space;//间隔

    int m_valueWidth;//数值宽度
    int m_xRadius;
    int m_yRadius;
};

#endif // COLORPROGRESSBAR_H
