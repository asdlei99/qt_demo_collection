/** @file    FriendTree.h
 *  @date    2019/02/04 11:01
 *  @brief   �����б���
 *
 *  @author  yu
 *  @contact ylesliefish@gmail.com
 */

#pragma once

#include <QTreeView>
#include "PublicGui/TreeView/TreeView.h"
#include "GlobalDefines.h"

using namespace publicgui;

namespace qqfriendlist
{
    class ItemDelegate;
    class FriendTree : public TreeView
    {
        Q_OBJECT

    public:
        FriendTree(QWidget *parent = Q_NULLPTR);
        ~FriendTree();

        // ��ֵ
        void setValues(const std::vector<Group>& groups);

    private:
        void initUi();
        void initConnection();
        // �Զ����hover����
        void onHoverHandle(const QModelIndex& index, int role);
        // �Զ���ĵ���¼�����
        void onClickedHandle(const QModelIndex& index, int role);
    private:
        QStandardItemModel* m_model{ nullptr }; // model
        ItemDelegate* m_delegate{ nullptr };
    };
}
