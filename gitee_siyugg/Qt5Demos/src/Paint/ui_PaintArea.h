/********************************************************************************
** Form generated from reading UI file 'PaintArea.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTAREA_H
#define UI_PAINTAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaintArea
{
public:

    void setupUi(QWidget *PaintArea)
    {
        if (PaintArea->objectName().isEmpty())
            PaintArea->setObjectName(QStringLiteral("PaintArea"));
        PaintArea->resize(400, 300);

        retranslateUi(PaintArea);

        QMetaObject::connectSlotsByName(PaintArea);
    } // setupUi

    void retranslateUi(QWidget *PaintArea)
    {
        PaintArea->setWindowTitle(QApplication::translate("PaintArea", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class PaintArea: public Ui_PaintArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTAREA_H
