/** @file    ItemDelegate.h
 *  @date    2019/02/04 13:09
 *  @brief   ����
 *
 *  @author  yu
 *  @contact ylesliefish@gmail.com
 */
#pragma once

#include "PublicGui/TreeView/StyledDelegate.h"

using namespace publicgui;

namespace qqfriendlist
{
    class ItemDelegate : public StyledDelegate
    {
        Q_OBJECT

    public:
        ItemDelegate(QObject *parent = Q_NULLPTR);
        ~ItemDelegate();

        // ���Item�������ݵĻ���
        virtual void paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

        // ����Ⱥ��
        virtual void paintGroup(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

        // ������ϵ��
        virtual void paintContact(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    protected:
        QSize sizeHint(const QStyleOptionViewItem &option,
            const QModelIndex &index) const Q_DECL_OVERRIDE;

        // hover��role
        virtual int getHoverEventRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex &index) const;

        // �����role
        virtual int getMouseEventRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex &index) const;
    };

}
