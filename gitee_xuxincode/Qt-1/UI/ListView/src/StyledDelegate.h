#pragma once

#include <QStyledItemDelegate>
#include <QHoverEvent>
#include <QAbstractItemView>

class StyledDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit StyledDelegate(QObject *parent = Q_NULLPTR);
    virtual ~StyledDelegate();

public:
    enum ItemRole
    {
        PosRole = Qt::UserRole + 10000, // λ��
        MousePressRole,                 // ���
        MouseHoverRole,                 // hover
    };

    // ������Ϊ
    struct OperateActions
    {
        bool isHovered{ false };
        bool isPressed{ false };
        bool isSelected{ false };
        int mousePosX{ 0 };
        int mousePosY{ 0 };
    };

    // ���Item�������ݵĻ���
    virtual void paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    // ��ȡ��ǰItem����Ϊ״̬��Ϣ
    virtual OperateActions getOperateActions(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    // ���ر�����Ľ�ɫ �������Item�ϵ���һ���ؼ�
    virtual int getMouseEventRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex &index) const;

public slots:
    // view�ϲ��������������
    Q_INVOKABLE virtual void hoverEvent(QHoverEvent* hoverEvent, QAbstractItemView* view, const QStyleOptionViewItem& option, const QModelIndex& modelIndex);
    Q_INVOKABLE virtual int mouseEvent(QMouseEvent* mouseEvent, QAbstractItemView* view, const QStyleOptionViewItem& option, const QModelIndex& modelIndex);

};
