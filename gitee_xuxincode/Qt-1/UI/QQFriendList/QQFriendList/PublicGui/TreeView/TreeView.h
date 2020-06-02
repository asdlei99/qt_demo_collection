/** @file    TreeView.h
 *  @date    2019/02/07 13:58
 *  @brief   ��QTreeView�̳г��Զ���TreeView
 *
 *  @author  yu
 *  @contact ylesliefish@gmail.com
 */
#pragma once

#include <QStandardItemModel>
#include <QTreeView>
#include <QEvent>
#include <QHoverEvent>
#include "StyledDelegate.h"

namespace publicgui
{
    class TreeView : public QTreeView
    {
        Q_OBJECT

    public:
        TreeView(QWidget *parent = Q_NULLPTR);
        ~TreeView();

    signals:
        // ���Item�ź�
        void signalClicked(const QModelIndex& iIndex);
        // ���Item�ź� ���嵽�㵽��Role
        void signalClicked(const QModelIndex& iIndex, int role);
        // ˫���ź�
        void signalDoubleClicked(const QModelIndex& iIndex);
        // hoverItem�ź� ���嵽hover��Role
        void signalHover(const QModelIndex& iIndex, int role);
    protected:
        virtual bool viewportEvent(QEvent* pEvent);
    };

}
