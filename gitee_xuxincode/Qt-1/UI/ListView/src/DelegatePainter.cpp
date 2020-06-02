#include "DelegatePainter.h"
#include <QDebug>

DelegatePainter::DelegatePainter()
{
    m_svgRenderer = new QSvgRenderer();
}

DelegatePainter::~DelegatePainter()
{
}

/** @fn     DelegatePainter::getElidedText
 *  @brief  �ı�����
 *  @param  const int weight �������� ����/������
 *  @param  const int size �����С
 *  @param  const QString & fontName ��������
 *  @param  const QString & content �ı�����
 *  @param  const int maxWidth �����
 *  @param  Qt::TextElideMode elider 
 *  @return QString 
 */
QString DelegatePainter::getElidedText(const int weight, const int size, const QString& fontName, const QString& content, const int maxWidth, Qt::TextElideMode elider)
{
    QString result = content;

    QFont wordfont;
    wordfont.setFamily(fontName);
    wordfont.setPixelSize(size);
    wordfont.setWeight(weight);

    QFontMetrics fontWidth(wordfont);
    int width = fontWidth.width(content);

    //���ַ������̫��Ļ�  �ұ���ʾʡ�Ժ�
    if (width >= maxWidth)  
    {
        result = fontWidth.elidedText(content, elider, maxWidth);
    }

    return result;
}

/** @fn     DelegatePainter::paintText
 *  @brief
 *  @param  QPainter * painter ����painter
 *  @param  const QStyleOptionViewItemV4 & op
 *  @param  const QModelIndex & index ����
 *  @param  int role ��ɫ
 *  @param  Qt::AlignmentFlag addFlag ������뷽ʽ
 *  @param  const QColor & color ��ɫ
 *  @param  const QRect & paintRect paint����
 *  @param  int fontSize �����С
 *  @param  QString content ��������
 *  @return void
 */
void DelegatePainter::paintText(QPainter* painter, const QStyleOptionViewItemV4& op, const QModelIndex &index,
    int role, Qt::AlignmentFlag addFlag, const QColor& color, const QRect& paintRect, int fontSize, QString content /*= ""*/)
{
    if (nullptr == painter)
    {
        return;
    }
    painter->save();
    if (content.isEmpty())
    {
        content = index.data(role).toString();

    }
    content = getElidedText(QFont::Normal, fontSize, "microsoft yahei", content, paintRect.width(), Qt::ElideRight);

    QFont font = painter->font();
    font.setFamily("microsoft yahei");
    font.setPixelSize(fontSize);
    painter->setFont(font);
    painter->setPen(color);
    painter->drawText(paintRect, addFlag | Qt::AlignVCenter, content);
    painter->save();
}

/** @fn     filemanagement::DelegatePainter::paintImage
*  @brief  ����SvgͼƬ ��ͼ��ʧ��
*  @param  QPainter * painter ��ͼָ��
*  @param  const QString & imagePath ͼƬ·��
*  @param  const QRect & paintRect ��ͼ����
*  @return void
*/
void DelegatePainter::paintSvgImage(QPainter* painter, const QString& imagePath, const QRect& paintRect)
{
    painter->save();
    
    if (!m_svgRenderer->load(imagePath))
    {
        return;
    }

    m_svgRenderer->render(painter, paintRect);
    painter->restore();
}
