#pragma once

#include <QStandardItemModel>
#include <QListView>
#include <QEvent>
#include <QHoverEvent>
#include "StyledDelegate.h"

class ListView : public QListView
{
    Q_OBJECT

public:
    ListView(QWidget *parent = Q_NULLPTR);
    ~ListView();

signals:
    // ���Item�ź�
    void signalClicked(const QModelIndex& iIndex);
    // ���Item�ź� ���嵽�㵽��Role
    void signalClicked(const QModelIndex& iIndex, int role);
    // ˫���ź�
    void signalDoubleClicked(const QModelIndex& iIndex);

protected:
    virtual bool viewportEvent(QEvent* pEvent);

private:
    StyledDelegate m_itemDelegate;
    QStandardItemModel m_model;
};
