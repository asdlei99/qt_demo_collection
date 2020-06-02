#include "mainwindow.h"

#include <QQmlContext>

#include "designbll.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(50, 100, 1100, 900);

    m_widget = new QQuickWidget(this);
    m_widget->setGeometry(0, 0, this->width(), this->height());
    m_widget->rootContext()->setContextProperty("main", this);

    //关键代码
    DesignBLL *designBLL=new DesignBLL();
    m_widget->rootContext()->setContextProperty("DesignBLL",designBLL);

    m_widget->setSource(QUrl("./main.qml"));
    m_widget->show();

}

MainWindow::~MainWindow()
{

}
