#include "DesignBLL.h"

#include <QRect>

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#include <QDebug>

//用作测试，在实例化时先添加一些测试数据
DesignBLL::DesignBLL(QObject *parent) : QObject(parent)
{
    memset(GameMap,0,sizeof(GameMap));
}

void DesignBLL::init(int sizeW, int sizeH, int mineSize)
{
    for(int i = 0; i < sizeW; i++)
    {
        for(int j = 0; j < sizeH; j++){
            DesignModel* item = new DesignModel(this);
            item->SetPos(i, j);
            m_data.append(item);
        }
    }

    //存储不重复的随机数
    QList<int> random_list;
    srand((int)time(0));  // 产生随机种子  把0换成NULL也行
    while(random_list.size() < mineSize)
    {
        int num = rand()%(sizeW * sizeH);
        //去重复数字
        if(!random_list.contains(num))
            random_list.append(num);
    }

    //通过雷去设置周边item的标记。
    //每个雷帮别的item标记+1，其他的为0
    QRect rect = QRect(0, 0, sizeW, sizeH);
    for (auto num : random_list)
    {
        DesignModel *item = reinterpret_cast<DesignModel*>(m_data[num]);
        item->SetItemType(CEnum::MSMine);
        QPoint pos = item->GetPos();
        int rowNum = pos.x();
        int columnNum = pos.y();
        GameMap[rowNum][columnNum] = {CEnum::MSMine};

        //找到周边8个点
        QPoint pos_left_top = QPoint(rowNum - 1, columnNum - 1);
        checkMine(rect, pos_left_top);

        QPoint pos_top = QPoint(rowNum, columnNum - 1);
        checkMine(rect, pos_top);

        QPoint pos_right_top = QPoint(rowNum + 1, columnNum - 1);
        checkMine(rect, pos_right_top);

        QPoint pos_left = QPoint(rowNum - 1, columnNum);
        checkMine(rect, pos_left);

        QPoint pos_right = QPoint(rowNum + 1, columnNum);
        checkMine(rect, pos_right);

        QPoint pos_left_bottom = QPoint(rowNum - 1, columnNum + 1);
        checkMine(rect, pos_left_bottom);

        QPoint pos_bottom = QPoint(rowNum, columnNum + 1);
        checkMine(rect, pos_bottom);

        QPoint pos_right_bottom = QPoint(rowNum + 1, columnNum + 1);
        checkMine(rect, pos_right_bottom);
    }
//    for(int i = 0; i < sizeW; i++)
//    {
//        for(int j = 0; j < sizeH; j++){
//            cout << "  " << GameMap[i][j];
//        }
//        cout << endl;
//    }

    for(int i = 0; i < sizeW; i++)
    {
        for(int j = 0; j < sizeH; j++){
            int value = GameMap[i][j];

            int index = j * sizeW + i;
            DesignModel *item = reinterpret_cast<DesignModel*>(m_data[index]);
            CEnum::CItemType type =  (CEnum::CItemType)(value);
            item->SetItemType(type);
        }
    }
}

QList<QObject*> DesignBLL::getModel(){
    return m_data;
}

bool DesignBLL::ClickItem(const int index)
{
    bool flag = false;
    DesignModel *item = reinterpret_cast<DesignModel*>(m_data[index]);
    switch(item->GetItemType()) {
    case CEnum::MSMine: {
        flag = false;
        break;
    }
    case CEnum::MSZore:
    case CEnum::MSOne:
    case CEnum::MSTwo:
    case CEnum::MSThree:
    case CEnum::MSFour:
    case CEnum::MSFive:
    case CEnum::MSSix:
    case CEnum::MSSeven:
    case CEnum::MSEight: {
        flag = true;
        break;
    }
    }
    return flag;
}

QString DesignBLL::GetPath(const int index)
{
    DesignModel *item = reinterpret_cast<DesignModel*>(m_data[index]);
    CEnum::CItemType type = item->GetItemType();

    QString path = "qrc:/image/";
    switch (type) {
    case CEnum::MSMine: {
        path += "lei.jpg";
        break;
    }
    case CEnum::MSZore: {
        path += "0.jpg";
        break;
    }
    case CEnum::MSOne: {
        path += "1.jpg";
        break;
    }
    case CEnum::MSTwo: {
        path += "2.jpg";
        break;
    }
    case CEnum::MSThree: {
        path += "3.jpg";
        break;
    }
    case CEnum::MSFour: {
        path += "4.jpg";
        break;
    }
    case CEnum::MSFive: {
        path += "5.jpg";
        break;
    }
    case CEnum::MSSix: {
        path += "6.jpg";
        break;
    }
    case CEnum::MSSeven: {
        path += "7.jpg";
        break;
    }
    case CEnum::MSEight: {
        path += "8.jpg";
        break;
    }
    default:
        break;
    }

    return path;
}

void DesignBLL::checkMine(QRect rect, QPoint pos)
{
    if(rect.contains(pos))
    {
        int sizeW = rect.width();
        int row = pos.x();
        int column = pos.y();

        int index = column * sizeW + row;
        DesignModel *targetItem = reinterpret_cast<DesignModel*>(m_data[index]);
        //检查item是否是雷
        if(GameMap[row][column] == -1)
        {
            targetItem->SetMineNum(-1);
            return;
        }

        GameMap[row][column]++;
    }
}
