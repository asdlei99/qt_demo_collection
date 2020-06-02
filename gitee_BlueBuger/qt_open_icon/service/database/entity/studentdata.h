#ifndef STUDENTDATA_H
#define STUDENTDATA_H

#include <QString>

class StudentData
{
public:
    StudentData();

    int getID(){return id;}
    void setID(int id){this->id = id;}

    QString getName(){return name;}
    void setName(const QString &name){this->name = name;}

    int getScore(){return score;}
    void setScore(int score){this->score = score;}

private:
    int id;  //学号
    QString name;  //姓名
    float score;  //成绩
};

#endif // STUDENTDATA_H
