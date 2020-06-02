/********************************************************************************
** Form generated from reading UI file 'Qt5DemosDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT5DEMOSDIALOG_H
#define UI_QT5DEMOSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Qt5DemosDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *Qt5DemosWidget;

    void setupUi(QDialog *Qt5DemosDialog)
    {
        if (Qt5DemosDialog->objectName().isEmpty())
            Qt5DemosDialog->setObjectName(QStringLiteral("Qt5DemosDialog"));
        Qt5DemosDialog->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(Qt5DemosDialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        Qt5DemosWidget = new QTreeWidget(Qt5DemosDialog);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/StdDlgs.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(Qt5DemosWidget);
        __qtreewidgetitem->setIcon(0, icon);
        new QTreeWidgetItem(__qtreewidgetitem);
        Qt5DemosWidget->setObjectName(QStringLiteral("Qt5DemosWidget"));

        verticalLayout_2->addWidget(Qt5DemosWidget);


        retranslateUi(Qt5DemosDialog);

        QMetaObject::connectSlotsByName(Qt5DemosDialog);
    } // setupUi

    void retranslateUi(QDialog *Qt5DemosDialog)
    {
        Qt5DemosDialog->setWindowTitle(QApplication::translate("Qt5DemosDialog", "Qt5DemosDialog", 0));
        QTreeWidgetItem *___qtreewidgetitem = Qt5DemosWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Qt5DemosDialog", "Qt5Demos", 0));

        const bool __sortingEnabled = Qt5DemosWidget->isSortingEnabled();
        Qt5DemosWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = Qt5DemosWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("Qt5DemosDialog", "Qt5\346\240\207\345\207\206\345\257\271\350\257\235\346\241\206", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("Qt5DemosDialog", "Qt5\346\240\207\345\207\206\345\257\271\350\257\235\346\241\206", 0));
        Qt5DemosWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class Qt5DemosDialog: public Ui_Qt5DemosDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT5DEMOSDIALOG_H
