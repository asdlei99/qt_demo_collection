/********************************************************************************
** Form generated from reading UI file 'InputDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDIALOG_H
#define UI_INPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InputDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QLabel *nameDisplay;
    QPushButton *nameModBtn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *sexLabel;
    QLabel *sexDisplay;
    QPushButton *sexModBtn;
    QHBoxLayout *horizontalLayout_3;
    QLabel *mathLabel;
    QLabel *mathDisplay;
    QPushButton *mathModBtn;
    QHBoxLayout *horizontalLayout_4;
    QLabel *literalLabel_4;
    QLabel *literalDisplay;
    QPushButton *literalModBtn;

    void setupUi(QDialog *InputDialog)
    {
        if (InputDialog->objectName().isEmpty())
            InputDialog->setObjectName(QStringLiteral("InputDialog"));
        InputDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(InputDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        nameLabel = new QLabel(InputDialog);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        horizontalLayout->addWidget(nameLabel);

        nameDisplay = new QLabel(InputDialog);
        nameDisplay->setObjectName(QStringLiteral("nameDisplay"));
        nameDisplay->setFrameShape(QFrame::Panel);
        nameDisplay->setFrameShadow(QFrame::Plain);

        horizontalLayout->addWidget(nameDisplay);

        nameModBtn = new QPushButton(InputDialog);
        nameModBtn->setObjectName(QStringLiteral("nameModBtn"));

        horizontalLayout->addWidget(nameModBtn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        sexLabel = new QLabel(InputDialog);
        sexLabel->setObjectName(QStringLiteral("sexLabel"));

        horizontalLayout_2->addWidget(sexLabel);

        sexDisplay = new QLabel(InputDialog);
        sexDisplay->setObjectName(QStringLiteral("sexDisplay"));
        sexDisplay->setFrameShape(QFrame::Panel);
        sexDisplay->setFrameShadow(QFrame::Plain);

        horizontalLayout_2->addWidget(sexDisplay);

        sexModBtn = new QPushButton(InputDialog);
        sexModBtn->setObjectName(QStringLiteral("sexModBtn"));

        horizontalLayout_2->addWidget(sexModBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        mathLabel = new QLabel(InputDialog);
        mathLabel->setObjectName(QStringLiteral("mathLabel"));

        horizontalLayout_3->addWidget(mathLabel);

        mathDisplay = new QLabel(InputDialog);
        mathDisplay->setObjectName(QStringLiteral("mathDisplay"));
        mathDisplay->setFrameShape(QFrame::Panel);
        mathDisplay->setFrameShadow(QFrame::Plain);

        horizontalLayout_3->addWidget(mathDisplay);

        mathModBtn = new QPushButton(InputDialog);
        mathModBtn->setObjectName(QStringLiteral("mathModBtn"));

        horizontalLayout_3->addWidget(mathModBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        literalLabel_4 = new QLabel(InputDialog);
        literalLabel_4->setObjectName(QStringLiteral("literalLabel_4"));

        horizontalLayout_4->addWidget(literalLabel_4);

        literalDisplay = new QLabel(InputDialog);
        literalDisplay->setObjectName(QStringLiteral("literalDisplay"));
        literalDisplay->setFrameShape(QFrame::Panel);
        literalDisplay->setFrameShadow(QFrame::Plain);

        horizontalLayout_4->addWidget(literalDisplay);

        literalModBtn = new QPushButton(InputDialog);
        literalModBtn->setObjectName(QStringLiteral("literalModBtn"));

        horizontalLayout_4->addWidget(literalModBtn);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(InputDialog);

        QMetaObject::connectSlotsByName(InputDialog);
    } // setupUi

    void retranslateUi(QDialog *InputDialog)
    {
        InputDialog->setWindowTitle(QApplication::translate("InputDialog", "Dialog", 0));
        nameLabel->setText(QApplication::translate("InputDialog", "\345\247\223\345\220\215\357\274\232", 0));
        nameDisplay->setText(QString());
        nameModBtn->setText(QApplication::translate("InputDialog", "\344\277\256\346\224\271\345\247\223\345\220\215", 0));
        sexLabel->setText(QApplication::translate("InputDialog", "\346\200\247\345\210\253\357\274\232", 0));
        sexDisplay->setText(QString());
        sexModBtn->setText(QApplication::translate("InputDialog", "\344\277\256\346\224\271\346\200\247\345\210\253", 0));
        mathLabel->setText(QApplication::translate("InputDialog", "\346\225\260\345\255\246\346\210\220\347\273\251\357\274\232", 0));
        mathDisplay->setText(QString());
        mathModBtn->setText(QApplication::translate("InputDialog", "\344\277\256\346\224\271\346\210\220\347\273\251", 0));
        literalLabel_4->setText(QApplication::translate("InputDialog", "\350\257\255\346\226\207\346\210\220\347\273\251\357\274\232", 0));
        literalDisplay->setText(QString());
        literalModBtn->setText(QApplication::translate("InputDialog", "\344\277\256\346\224\271\346\210\220\347\273\251", 0));
    } // retranslateUi

};

namespace Ui {
    class InputDialog: public Ui_InputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDIALOG_H
