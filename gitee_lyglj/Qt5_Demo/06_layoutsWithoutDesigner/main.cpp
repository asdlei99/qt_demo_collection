#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    // 3个按键水平布局
    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *b1 = new QPushButton("A");
    QPushButton *b2 = new QPushButton("B");
    QPushButton *b3 = new QPushButton("C");
    hLayout->addWidget (b1);
    hLayout->addWidget (b2);
    hLayout->addWidget (b3);

    // 3个按键垂直布局
    QVBoxLayout *vLayout = new QVBoxLayout;
    QPushButton *b4 = new QPushButton("D");
    QPushButton *b5 = new QPushButton("E");
    QPushButton *b6 = new QPushButton("F");
    vLayout->addWidget(b4);
    vLayout->addWidget(b5);
    vLayout->addWidget(b6);

    // 外部布局
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 添加前两个内部布局
    mainLayout->addLayout (hLayout);
    mainLayout->addLayout (vLayout);

    // 创建 QWidget
    QWidget *w = new QWidget();

    // 设置外部布局为主要布局
    w->setLayout (mainLayout);

    // 设置标题
    w->setWindowTitle (QString("layouts"));

    w->show ();

    return app.exec ();
}
