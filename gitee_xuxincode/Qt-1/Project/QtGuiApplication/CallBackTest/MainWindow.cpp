#include "MainWindow.h"
#include "ui_MainWindow.h"

QLineEdit * MainWindow::line1;
QLineEdit * MainWindow::line2;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    
    // ��ʼ��QLineEdit
    line1 = new QLineEdit();
    line2 = new QLineEdit();

    // ������line �Ž�gridLayout
    ui->gridLayout->addWidget(line1, 0, 1);
    ui->gridLayout->addWidget(line2, 0, 2);

    m_scene = new QGraphicsScene();       // ��ʼ��ͼ�γ���
    ui->graphicsView->setScene(m_scene);  // ���ó����� graphicsView
    m_scene->setSceneRect(0, 0, 300, 300);
    m_square = new Square();
    m_square->setCallbackFunc(getPosition);   // ��getPosition���ûص�  ����m_square���������
    m_square->setPos(100, 100);
    m_scene->addItem(m_square);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/** 
 * @fn     MainWindow::getPosition
 * @brief  �ص���������������λ�� д������lineEdit
 * @param  QPointF point
 * @return void
 */
void MainWindow::getPosition(QPointF point)
{
    line1->setText(QString::number(point.x()));
    line2->setText(QString::number(point.y()));
}
