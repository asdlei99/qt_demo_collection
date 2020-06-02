/********************************************************************************
** Form generated from reading UI file 'DrawWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWWINDOW_H
#define UI_DRAWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawWindow
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DrawWindow)
    {
        if (DrawWindow->objectName().isEmpty())
            DrawWindow->setObjectName(QStringLiteral("DrawWindow"));
        DrawWindow->resize(570, 483);
        centralWidget = new QWidget(DrawWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DrawWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DrawWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 570, 28));
        DrawWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DrawWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DrawWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        DrawWindow->insertToolBarBreak(mainToolBar);
        statusBar = new QStatusBar(DrawWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DrawWindow->setStatusBar(statusBar);

        retranslateUi(DrawWindow);

        QMetaObject::connectSlotsByName(DrawWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DrawWindow)
    {
        DrawWindow->setWindowTitle(QApplication::translate("DrawWindow", "DrawWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class DrawWindow: public Ui_DrawWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWWINDOW_H
