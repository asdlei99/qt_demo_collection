/********************************************************************************
** Form generated from reading UI file 'ProgressBar.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSBAR_H
#define UI_PROGRESSBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ProgressBar
{
public:
    QPushButton *startButton;
    QProgressBar *progressBar;

    void setupUi(QDialog *ProgressBar)
    {
        if (ProgressBar->objectName().isEmpty())
            ProgressBar->setObjectName(QStringLiteral("ProgressBar"));
        ProgressBar->resize(400, 300);
        startButton = new QPushButton(ProgressBar);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(80, 70, 231, 51));
        progressBar = new QProgressBar(ProgressBar);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(140, 180, 118, 23));
        progressBar->setValue(0);

        retranslateUi(ProgressBar);

        QMetaObject::connectSlotsByName(ProgressBar);
    } // setupUi

    void retranslateUi(QDialog *ProgressBar)
    {
        ProgressBar->setWindowTitle(QApplication::translate("ProgressBar", "ProgressBar", 0));
        startButton->setText(QApplication::translate("ProgressBar", "\347\202\271\345\207\273\345\274\200\345\220\257\350\277\233\345\272\246\346\235\241", 0));
    } // retranslateUi

};

namespace Ui {
    class ProgressBar: public Ui_ProgressBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSBAR_H
