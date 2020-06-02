#include "DesignBLL.h"




//用作测试，在实例化时先添加一些测试数据
DesignBLL::DesignBLL(){
    for(int i = 0; i < 35; i++){
        if(i % 4 == 1)
            data.append(new DesignModel("#EEDFCC"));
        else if(i % 4 == 2)
            data.append(new DesignModel("#FF00FF"));
        else if(i % 4 == 3)
            data.append(new DesignModel("#EE7942"));
        else
            data.append(new DesignModel("#FFFFFF"));
    }
}

QList<QObject*> DesignBLL::getModel(){
    return data;
}
