#include "selectcontainer.h"

bool SelectContainer::getCanMultiple() const
{
    return canMultiple;
}

void SelectContainer::setCanMultiple(bool value)
{
    canMultiple = value;
}



QSignalMapper *SelectContainer::getSignalMapper() const
{
    return signalMapper;
}

void SelectContainer::setSignalMapper(QSignalMapper *value)
{
    signalMapper = value;
}

bool SelectContainer::addAction(QAction *action)
{
    this->contaioner.append(action);
    //action点击后传递数据到map
    connect(action,SIGNAL(triggered(bool)),this->signalMapper,SLOT(map()));
    //绑定传递的数据
    this->signalMapper->setMapping(action,action->data().toInt());

    return true;
}


void SelectContainer::actionTrigger(int var)
{
    //如果不能多选 则取消其他项的选择
    if(!this->canMultiple){
        for(QAction *action:this->contaioner){
            if(action->data().toInt() ==var)
                continue;
            action->setChecked(false);
            emit actionUnTriggered(var);
        }
    }
    emit actionTriggered(var);
}

SelectContainer::SelectContainer(QObject *parent, bool canMultiple) : QObject(parent),canMultiple(canMultiple)
{
    this->signalMapper =new QSignalMapper(parent);
    //绑定所有的mapper到自定义槽函数
    connect(this->signalMapper,SIGNAL(mapped(int)),this,SLOT(actionTrigger(int)));
}

