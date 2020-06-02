#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QLineEdit>
#include "Square.h"
namespace Ui { class MainWindow; };

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    QGraphicsScene* m_scene;
    Square *m_square;           // ���������� ����ص�
    static QLineEdit *line1;    // ����һ����̬QLineEdit, ִ�лص�
    static QLineEdit *line2;    // ����һ����̬QLineEdit, ִ�лص�

private:
    // ����һ���ص�����
    static void getPosition(QPointF point);
};
