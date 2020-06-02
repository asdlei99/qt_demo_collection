/********************************************************************************
** Form generated from reading UI file 'Qt5DemosDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT5DEMOSDLG_H
#define UI_QT5DEMOSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Qt5DemosDlg
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *Qt5DemosWidget;

    void setupUi(QDialog *Qt5DemosDlg)
    {
        if (Qt5DemosDlg->objectName().isEmpty())
            Qt5DemosDlg->setObjectName(QStringLiteral("Qt5DemosDlg"));
        Qt5DemosDlg->resize(400, 300);
        verticalLayout = new QVBoxLayout(Qt5DemosDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Qt5DemosWidget = new QTreeWidget(Qt5DemosDlg);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/StdDlgs.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(Qt5DemosWidget);
        __qtreewidgetitem->setIcon(0, icon);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(Qt5DemosWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        Qt5DemosWidget->setObjectName(QStringLiteral("Qt5DemosWidget"));
        Qt5DemosWidget->header()->setHighlightSections(true);

        verticalLayout->addWidget(Qt5DemosWidget);


        retranslateUi(Qt5DemosDlg);

        QMetaObject::connectSlotsByName(Qt5DemosDlg);
    } // setupUi

    void retranslateUi(QDialog *Qt5DemosDlg)
    {
        Qt5DemosDlg->setWindowTitle(QApplication::translate("Qt5DemosDlg", "Dialog", 0));
        QTreeWidgetItem *___qtreewidgetitem = Qt5DemosWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Qt5DemosDlg", "Qt5Demos", 0));

        const bool __sortingEnabled = Qt5DemosWidget->isSortingEnabled();
        Qt5DemosWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = Qt5DemosWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("Qt5DemosDlg", "Qt5\345\237\272\346\234\254\345\257\271\350\257\235\346\241\206", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("Qt5DemosDlg", "Qt5\346\240\207\345\207\206\345\257\271\350\257\235\346\241\206", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("Qt5DemosDlg", "\350\277\233\345\272\246\346\235\241", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("Qt5DemosDlg", "Qt\344\275\215\347\275\256\345\207\275\346\225\260\345\257\271\350\257\235\346\241\206", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QApplication::translate("Qt5DemosDlg", "\350\260\203\350\211\262\346\235\277", 0));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem6->setText(0, QApplication::translate("Qt5DemosDlg", "\347\224\265\345\255\220\351\222\237", 0));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem1->child(5);
        ___qtreewidgetitem7->setText(0, QApplication::translate("Qt5DemosDlg", "\345\217\257\346\211\251\345\261\225\345\257\271\350\257\235\346\241\206", 0));
        QTreeWidgetItem *___qtreewidgetitem8 = Qt5DemosWidget->topLevelItem(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("Qt5DemosDlg", "Qt5\344\270\273\347\252\227\344\275\223", 0));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(0, QApplication::translate("Qt5DemosDlg", "\345\233\276\347\211\207\346\265\217\350\247\210\345\231\250", 0));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem8->child(1);
        ___qtreewidgetitem10->setText(0, QApplication::translate("Qt5DemosDlg", "\346\226\207\345\255\227\345\244\204\347\220\206\345\231\250", 0));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem8->child(2);
        ___qtreewidgetitem11->setText(0, QApplication::translate("Qt5DemosDlg", "\345\233\276\345\275\242\347\224\273\346\235\277", 0));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem8->child(3);
        ___qtreewidgetitem12->setText(0, QApplication::translate("Qt5DemosDlg", "\347\273\230\347\224\273", 0));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem8->child(4);
        ___qtreewidgetitem13->setText(0, QApplication::translate("Qt5DemosDlg", "\345\233\276\345\205\203\347\232\204\346\227\213\350\275\254\343\200\201\347\274\251\346\224\276\347\255\211\345\217\230\346\215\242", 0));
        Qt5DemosWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class Qt5DemosDlg: public Ui_Qt5DemosDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT5DEMOSDLG_H
