#include "DelegatePainter.h"
#include <QDebug>

namespace publicgui
{
    DelegatePainter::DelegatePainter()
    {
        m_svgRenderer = new QSvgRenderer();
    }

    DelegatePainter::~DelegatePainter()
    {
    }

    /****************************************!
     * @brief  �ı�����
     * @param  [in]  const int weight �������� ����/������
     * @param  [in]  const int size �����С
     * @param  [in]  const QString & fontName ��������
     * @param  [in]  const QString & content �ı�����
     * @param  [in]  const int maxWidth �����
     * @param  [in]  Qt::TextElideMode elider
     * @return QT_NAMESPACE::QString
     ****************************************/
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

    /****************************************!
     * @brief  �����ı�
     * @param  [in]  QPainter * painter ����painter
     * @param  [in]  const QStyleOptionViewItemV4 & op
     * @param  [in]  const QModelIndex & index ����
     * @param  [in]  int role ��ɫ
     * @param  [in]  Qt::AlignmentFlag addFlag ������뷽ʽ
     * @param  [in]  const QColor & color ��ɫ
     * @param  [in]  const QRect & paintRect paint����
     * @param  [in]  int fontSize �����С
     * @param  [in]  QString content ��������
     * @return void
     ****************************************/
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
        painter->restore();
    }

    /****************************************!
     * @brief  ����SvgͼƬ ��ͼ��ʧ��
     * @param  [in]  QPainter * painter ��ͼָ��
     * @param  [in]  const QString & imagePath ͼƬ·��
     * @param  [in]  const QRect & paintRect ��ͼ����
     * @return void
     ****************************************/
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
}
