#include <QObject>

#pragma once

enum PaintRoleType
{
    NameRole = Qt::UserRole + 2000,     // �û���
    HeadPortraitRole,                   // ͷ��
    IsVipRole,                          // �Ƿ�vip
    DepartmentRole,                     // ����Role
};


struct UserInfo
{
    bool isVip{ false };
    QString name{};
    QString depart{};
    QString headPortraitPath{};
};