/********************************************************************************
** Form generated from reading UI file 'InforDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORDIALOG_H
#define UI_INFORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InforDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *questionDia;
    QPushButton *informationDia;
    QPushButton *warningDia;
    QPushButton *criticalDia;
    QPushButton *aboutDia;
    QPushButton *aboutQtDia;
    QPushButton *customDia;
    QLabel *content;

    void setupUi(QDialog *InforDialog)
    {
        if (InforDialog->objectName().isEmpty())
            InforDialog->setObjectName(QStringLiteral("InforDialog"));
        InforDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(InforDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        questionDia = new QPushButton(InforDialog);
        questionDia->setObjectName(QStringLiteral("questionDia"));

        gridLayout->addWidget(questionDia, 0, 0, 1, 1);

        informationDia = new QPushButton(InforDialog);
        informationDia->setObjectName(QStringLiteral("informationDia"));

        gridLayout->addWidget(informationDia, 0, 1, 1, 1);

        warningDia = new QPushButton(InforDialog);
        warningDia->setObjectName(QStringLiteral("warningDia"));

        gridLayout->addWidget(warningDia, 1, 0, 1, 1);

        criticalDia = new QPushButton(InforDialog);
        criticalDia->setObjectName(QStringLiteral("criticalDia"));

        gridLayout->addWidget(criticalDia, 1, 1, 1, 1);

        aboutDia = new QPushButton(InforDialog);
        aboutDia->setObjectName(QStringLiteral("aboutDia"));

        gridLayout->addWidget(aboutDia, 2, 0, 1, 1);

        aboutQtDia = new QPushButton(InforDialog);
        aboutQtDia->setObjectName(QStringLiteral("aboutQtDia"));

        gridLayout->addWidget(aboutQtDia, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        customDia = new QPushButton(InforDialog);
        customDia->setObjectName(QStringLiteral("customDia"));

        verticalLayout->addWidget(customDia);

        content = new QLabel(InforDialog);
        content->setObjectName(QStringLiteral("content"));
        content->setFrameShape(QFrame::WinPanel);
        content->setFrameShadow(QFrame::Raised);
        content->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(content);


        retranslateUi(InforDialog);

        QMetaObject::connectSlotsByName(InforDialog);
    } // setupUi

    void retranslateUi(QDialog *InforDialog)
    {
        InforDialog->setWindowTitle(QApplication::translate("InforDialog", "Dialog", 0));
        questionDia->setText(QApplication::translate("InforDialog", "Question\345\257\271\350\257\235\346\241\206", 0));
        informationDia->setText(QApplication::translate("InforDialog", "Information\345\257\271\350\257\235\346\241\206", 0));
        warningDia->setText(QApplication::translate("InforDialog", "Warning\345\257\271\350\257\235\346\241\206", 0));
        criticalDia->setText(QApplication::translate("InforDialog", "Critical\345\257\271\350\257\235\346\241\206", 0));
        aboutDia->setText(QApplication::translate("InforDialog", "About\345\257\271\350\257\235\346\241\206", 0));
        aboutQtDia->setText(QApplication::translate("InforDialog", "AboutQt\345\257\271\350\257\235\346\241\206", 0));
        customDia->setText(QApplication::translate("InforDialog", "Custom\345\257\271\350\257\235\346\241\206", 0));
        content->setText(QApplication::translate("InforDialog", "\350\277\224\345\233\236\345\206\205\345\256\271", 0));
    } // retranslateUi

};

namespace Ui {
    class InforDialog: public Ui_InforDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORDIALOG_H
