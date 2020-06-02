#include "footwidget.h"

#include <qpainter.h>
#include <qfile.h>
#include <QTextStream>
#include <qdebug.h>
#include <QTime>

#include <iostream>
#include <cmath>

using namespace std;

uint GFrameBuff[44][52];
uint GColorBuff[44][52];
vector<vector<uint> >GDataVtr;
//vector<vector<uint> >GColorVtr;

FootWidget::FootWidget(QWidget *parent) : QWidget(parent)
{
    resize(666,666);
    readData();
    repaint();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

void FootWidget::paintEvent(QPaintEvent *event)
{
    QPainter *paint=new QPainter;
    paint->begin(this);
    paint->setPen(QPen(Qt::blue,1,Qt::NoPen));//设置画笔形式
    paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
    paint->drawRect(20,20,21,21);

    QPoint p(22,22);
    QRect rect;
    //            p.setX(p.x() + 24);
//    cout<<"paint"<<endl;
#if 1
    for(int i = 0; i < 44; ++i){
        //        p.setX(p.x() + 12);

        for(int key = 0;key < 52; ++key){
            p.setX(p.x() + 12);
            rect.setTopLeft(p);
            rect.setSize(QSize(11,11));

            QColor color;

            //            color.setHsv(GFrameBuff[i][key],255,128);
            color = getColor(GFrameBuff[i][key]);

            //            int colorHnum = qrand()%240;
            //            cout<<"colorHnum:"<<colorHnum<<endl;
            //            color.setHsl(colorHnum,1,1);
            //            color.setHsv(colorHnum,255,128);
            paint->setBrush(QBrush(color,Qt::SolidPattern));//设置画刷形式

            paint->drawRect(rect);

            //            cout<<GFrameBuff[i][key]<<" ";
        }
        p.setX(22);
        p.setY(p.y() + 12);

        //        cout<<endl;
    }
#endif

    paint->end();
}

void FootWidget::readData()
{
    QFile file("data.csv") ;
    if(false == file.open(QIODevice::ReadOnly)){
        cout<<"read file failed"<<endl;
        exit(0);
    }

    QTextStream ts(&file);
    QString s = ts.readAll();
    cout<<"line:"<<s.toStdString()<<endl;
    //    QStringList list = s.split("\r");
    QStringList list = s.split("\n");

    cout<<"list size:"<<list.size()<<endl;
    for(int i = 0; i < list.size(); ++i){
        QString dataStr = list[i];
        QStringList subList = dataStr.split(",");
        vector<uint> tmpVtr;
        if(subList.size() == 0){
            continue;
        }

        for(int key = 0; key < subList.size(); ++key){
            GFrameBuff[i][key] = subList.value(key).toInt();
            tmpVtr.push_back(subList.value(key).toInt());
        }
        GDataVtr.push_back(tmpVtr);
    }
#if 0
    cout<<"GDataVtr"<<endl;
    for(auto &item:GDataVtr){
        for(auto &subItem:item){
            cout<<subItem<<" ";
        }
        cout<<endl;
    }
#endif


    //    colorParser();


#if 1
    cout<<"buff"<<endl;
    cout<<"buff"<<endl;
    cout<<"buff"<<endl;

    for(int i = 0; i < 44; ++i){
        vector<uint> tmpVtr;
        for(int key = 0; key < 52; ++key){
            cout<<GFrameBuff[i][key]<<" ";
        }
        cout<<endl;
    }

#endif

}

void FootWidget::colorParser()
{
    //    GColorVtr
    vector<uint> subMaxVtr;
    for(auto &item:GDataVtr){
        uint subMax = *max_element(item.begin(),item.end());
        subMaxVtr.push_back(subMax);
    }

    uint max = *max_element(subMaxVtr.begin(),subMaxVtr.end());

    double scale = 240 / max;

#if 0
    //    GColorVtr
    for(auto &item:GDataVtr){
        vector<uint> tmpVtr;
        for(auto &subItem:item){
            //            cout<<subItem<<" ";
            //            uint num = ;
            tmpVtr.push_back(round(subItem * scale));
            cout<<"color:"
               <<subItem * scale
              <<subItem<<" ";
        }
        GColorVtr.push_back(tmpVtr);
        cout<<endl;
    }
#endif

    cout<<endl;
    cout<<endl;
}

double FootWidget::getScale()
{
    vector<uint> subMaxVtr;
    vector<uint> subMinVtr;
    for(auto &item:GDataVtr){
        uint subMax = *max_element(item.begin(),item.end());
        subMaxVtr.push_back(subMax);

        //求所有有效点的最小值
        for(auto &subItem:item){
            if(subItem <= 10){
                continue;
            }
            subMinVtr.push_back(subItem);
        }
    }

    m_max = *max_element(subMaxVtr.begin(),subMaxVtr.end());
    m_min = *min_element(subMinVtr.begin(),subMinVtr.end());

    double scale =  (m_max - m_min) / 240;
    return scale;
}

QColor FootWidget::getColor(uint num)
{
    double scale = getScale();
    //    cout<<"getColor:"<<num<<endl;
    cout<<"max:"<<m_max<<"min:"<<m_min<<endl;
    cout<<"scale:"<<scale<<endl;
    QColor color;
    if(num <= 10){
        color = Qt::white;
    }else{
        //        uint colorNum = round((m_max - num) * scale);
        int colorNum = int((m_max - num) * scale + 0.5);
        color.setHsv(colorNum,255,128);


                cout<<"getColor:"<<colorNum<<"|"<<num<<endl;
        //                        color = Qt::red;
    }
    return color;
}
