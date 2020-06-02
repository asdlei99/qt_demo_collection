#include <QCoreApplication>
#include <QtConcurrent>
#include <qdebug.h>
#include <qthread.h>
#include <qfuture.h>

//pro文件中添加QT += concurrent

void debugFun(){
    qDebug()<<"debugFun,thread id:"<<QThread::currentThreadId();
}
void paramFun(int &num,const QString &name){
    num = 21;
    qDebug()<<"paramFun,num\\name:"<<num<<"\\"<<name;
}
QString returnFun(){
    return "returnFun return str.";
}
void map6Fun(int &num){
    num = num * 10;
}
int mapedFun(const int& num){
    return num *10;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"main thread id:"<<QThread::currentThreadId();
    //1.
    QtConcurrent::run(debugFun);
    /*
     * 2.子线程运行的函数的参数，传参时都会复制一份副本
     *  即使传递引用也会复制一份。。
     */
    int num = 0;
    QString name = "laowang";

    QtConcurrent::run(paramFun,num,name);
    qDebug()<<"main2 param,num\\name:"<<num<<"\\"<<name;
    qDebug()<<"main2 param,num\\name:"<<num<<"\\"<<name;
    qDebug()<<"main2 param,num\\name:"<<num<<"\\"<<name;
    /*
     * 3.QFuture::result() 函数会阻塞，直到结果可用。
     */
    QFuture<QString> future = QtConcurrent::run(returnFun);
    QString result = future.result();
    qDebug()<<"main3 future result:"<<result;
    /*
     * 4.QtConcurrent::run() 函数还可以接收成员函数的指针
     */
    QByteArray bytearray = "hello,world";
    QFuture<QList<QByteArray> > ff = QtConcurrent::run(bytearray, &QByteArray::split, ',');
    QList<QByteArray> blist = ff.result();
    qDebug()<<"main4 bytearray:"<<bytearray;
    qDebug()<<"main4 blist:"<<blist;
    /*
     * 5.使用lambda匿名函数
     */
    QFuture<void> f5 = QtConcurrent::run([=](){
        qDebug()<<"main5 thread id:"<<QThread::currentThreadId();
    });
    /*
    * 6.QtConcurrent::map()：直接操作容器中的每一项。
    * QtConcurrent::mapped()：操作容器中的每一项，将处理结果返回一个新的容器，原容器不变。
    * QtConcurrent::mappedReduced()：在 mapped() 的基础上将处理结果进一步传递给一个函数继续处理。
    *
    * 6.1.QtConcurrent::map() 可以直接修改容器的每一项，处理函数必须是“U function(T &t)”的形式。
    * 因为是直接修改，所以 map() 函数不会返回任何 QFuture 结果，但仍然可以使用 QFuture 和 QFutureWatcher 来监视状态。
    */
    QList<int> intList = {1,2,3,4};
    QFuture<void> f6 = QtConcurrent::map(intList,map6Fun);
    //等待子线程运算完成再打印
    f6.waitForFinished();
    qDebug()<<"main6 intList:"<<intList;
    /*
     * 6.2.QtConcurrent::mapped() 不直接修改容器的每一项，而是将处理后的结果返回一个新的容器，
     * 处理函数必须是“U function(const T &t)”的形式。
     */
    QList<int> mapedList = {1,2,3,4,5};
    QFuture<int> mapedFt = QtConcurrent::mapped(mapedList, mapedFun);
//    QFutureIterator<int> (mapedFt);
    for(auto &item:mapedFt.results()){
        qDebug()<<"maped:"<<item;
    }
    /*
     * 6.3.QtConcurrent::mappedReduced() 类似于 mapped()，区别在于将结果继续传递给一个新函数，
     * 并在新函数里再处理成一个单值。新函数必须是“V function(T &result，const U &intermediate)”的形式。
     */




    return a.exec();
}













































