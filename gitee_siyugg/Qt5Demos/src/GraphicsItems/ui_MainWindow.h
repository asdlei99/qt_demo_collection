/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openImg;
    QAction *quitAct;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QGroupBox *rotateGroup;
    QHBoxLayout *horizontalLayout;
    QLabel *rotateLabel;
    QSlider *rotateSlider;
    QGroupBox *scaleGroup;
    QHBoxLayout *horizontalLayout_2;
    QLabel *scaleLabel;
    QSlider *scaleSlider;
    QGroupBox *shearGroup;
    QHBoxLayout *horizontalLayout_3;
    QLabel *shearLabel;
    QSlider *shearSlider;
    QGroupBox *translateGroup;
    QHBoxLayout *horizontalLayout_4;
    QLabel *translateLabel;
    QSlider *translateSlider;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(663, 517);
        openImg = new QAction(MainWindow);
        openImg->setObjectName(QStringLiteral("openImg"));
        quitAct = new QAction(MainWindow);
        quitAct->setObjectName(QStringLiteral("quitAct"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_6 = new QHBoxLayout(centralWidget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

        horizontalLayout_5->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        rotateGroup = new QGroupBox(centralWidget);
        rotateGroup->setObjectName(QStringLiteral("rotateGroup"));
        rotateGroup->setMinimumSize(QSize(120, 0));
        horizontalLayout = new QHBoxLayout(rotateGroup);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        rotateLabel = new QLabel(rotateGroup);
        rotateLabel->setObjectName(QStringLiteral("rotateLabel"));
        rotateLabel->setLineWidth(3);

        horizontalLayout->addWidget(rotateLabel);

        rotateSlider = new QSlider(rotateGroup);
        rotateSlider->setObjectName(QStringLiteral("rotateSlider"));
        rotateSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(rotateSlider);

        rotateSlider->raise();

        verticalLayout->addWidget(rotateGroup);

        scaleGroup = new QGroupBox(centralWidget);
        scaleGroup->setObjectName(QStringLiteral("scaleGroup"));
        scaleGroup->setMinimumSize(QSize(100, 0));
        horizontalLayout_2 = new QHBoxLayout(scaleGroup);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        scaleLabel = new QLabel(scaleGroup);
        scaleLabel->setObjectName(QStringLiteral("scaleLabel"));
        scaleLabel->setLineWidth(3);

        horizontalLayout_2->addWidget(scaleLabel);

        scaleSlider = new QSlider(scaleGroup);
        scaleSlider->setObjectName(QStringLiteral("scaleSlider"));
        scaleSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(scaleSlider);


        verticalLayout->addWidget(scaleGroup);

        shearGroup = new QGroupBox(centralWidget);
        shearGroup->setObjectName(QStringLiteral("shearGroup"));
        shearGroup->setMinimumSize(QSize(100, 0));
        horizontalLayout_3 = new QHBoxLayout(shearGroup);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        shearLabel = new QLabel(shearGroup);
        shearLabel->setObjectName(QStringLiteral("shearLabel"));
        shearLabel->setLineWidth(3);

        horizontalLayout_3->addWidget(shearLabel);

        shearSlider = new QSlider(shearGroup);
        shearSlider->setObjectName(QStringLiteral("shearSlider"));
        shearSlider->setOrientation(Qt::Horizontal);
        shearSlider->setTickInterval(4);

        horizontalLayout_3->addWidget(shearSlider);

        shearSlider->raise();
        scaleGroup->raise();

        verticalLayout->addWidget(shearGroup);

        translateGroup = new QGroupBox(centralWidget);
        translateGroup->setObjectName(QStringLiteral("translateGroup"));
        translateGroup->setMinimumSize(QSize(100, 0));
        horizontalLayout_4 = new QHBoxLayout(translateGroup);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        translateLabel = new QLabel(translateGroup);
        translateLabel->setObjectName(QStringLiteral("translateLabel"));
        translateLabel->setLineWidth(3);

        horizontalLayout_4->addWidget(translateLabel);

        translateSlider = new QSlider(translateGroup);
        translateSlider->setObjectName(QStringLiteral("translateSlider"));
        translateSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(translateSlider);


        verticalLayout->addWidget(translateGroup);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalLayout_5->setStretch(0, 3);
        horizontalLayout_5->setStretch(1, 1);

        horizontalLayout_6->addLayout(horizontalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 663, 28));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(openImg);
        menu->addSeparator();
        menu->addAction(quitAct);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        openImg->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0));
        openImg->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        quitAct->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        quitAct->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        rotateGroup->setTitle(QApplication::translate("MainWindow", "Rotate", 0));
        rotateLabel->setText(QApplication::translate("MainWindow", "0", 0));
        scaleGroup->setTitle(QApplication::translate("MainWindow", "Scale", 0));
        scaleLabel->setText(QApplication::translate("MainWindow", "0", 0));
        shearGroup->setTitle(QApplication::translate("MainWindow", "Shear", 0));
        shearLabel->setText(QApplication::translate("MainWindow", "0", 0));
        translateGroup->setTitle(QApplication::translate("MainWindow", "Translate", 0));
        translateLabel->setText(QApplication::translate("MainWindow", "0", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
