/** @file    DelegatePainter.h
 *  @date    2019/02/04 10:58
 *  @brief   �����ı�/ͼƬ��  �ṩ��������ʹ��
 *
 *  @author  yu
 *  @contact ylesliefish@gmail.com
 */

#pragma once

#include <QPainter>
#include <QSvgRenderer>
#include <QStyleOptionViewItemV4>

namespace publicgui
{
    class DelegatePainter
    {

    public:
        DelegatePainter();
        ~DelegatePainter();

    public:
        // paint����
        void paintText(QPainter* painter, const QStyleOptionViewItemV4& op, const QModelIndex &index,
            int role, Qt::AlignmentFlag addFlag, const QColor& color, const QRect& paintRect, int fontSize, QString content = "");

        // SvgͼƬ
        void paintSvgImage(QPainter* painter, const QString& imagePath, const QRect& paintRect);

    private:
        // ���ش����֮����ı��ַ���
        QString getElidedText(const int weight, const int size, const QString& fontName, const QString& content, const int maxWidth, Qt::TextElideMode elider);

    private:
        QSvgRenderer* m_svgRenderer{ nullptr };
    };

}
