/********************************************************************************
** Form generated from reading UI file 'QtStdDialogs.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSTDDIALOGS_H
#define UI_QTSTDDIALOGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QtStdDialogs
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *fileDiaBtn;
    QLineEdit *fileDisplay;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *colorDiaBtn;
    QFrame *colorDisplay;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *fontDiaBtn;
    QLineEdit *fontDisplay;
    QPushButton *fontDiaBtn_2;
    QPushButton *pushButton;

    void setupUi(QDialog *QtStdDialogs)
    {
        if (QtStdDialogs->objectName().isEmpty())
            QtStdDialogs->setObjectName(QStringLiteral("QtStdDialogs"));
        QtStdDialogs->resize(400, 425);
        verticalLayout = new QVBoxLayout(QtStdDialogs);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fileDiaBtn = new QPushButton(QtStdDialogs);
        fileDiaBtn->setObjectName(QStringLiteral("fileDiaBtn"));

        horizontalLayout->addWidget(fileDiaBtn);

        fileDisplay = new QLineEdit(QtStdDialogs);
        fileDisplay->setObjectName(QStringLiteral("fileDisplay"));

        horizontalLayout->addWidget(fileDisplay);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        colorDiaBtn = new QPushButton(QtStdDialogs);
        colorDiaBtn->setObjectName(QStringLiteral("colorDiaBtn"));

        horizontalLayout_2->addWidget(colorDiaBtn);

        colorDisplay = new QFrame(QtStdDialogs);
        colorDisplay->setObjectName(QStringLiteral("colorDisplay"));
        colorDisplay->setMaximumSize(QSize(187, 16777215));
        colorDisplay->setAutoFillBackground(true);
        colorDisplay->setFrameShape(QFrame::StyledPanel);
        colorDisplay->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(colorDisplay);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        fontDiaBtn = new QPushButton(QtStdDialogs);
        fontDiaBtn->setObjectName(QStringLiteral("fontDiaBtn"));

        horizontalLayout_3->addWidget(fontDiaBtn);

        fontDisplay = new QLineEdit(QtStdDialogs);
        fontDisplay->setObjectName(QStringLiteral("fontDisplay"));
        fontDisplay->setEnabled(false);

        horizontalLayout_3->addWidget(fontDisplay);


        verticalLayout->addLayout(horizontalLayout_3);

        fontDiaBtn_2 = new QPushButton(QtStdDialogs);
        fontDiaBtn_2->setObjectName(QStringLiteral("fontDiaBtn_2"));

        verticalLayout->addWidget(fontDiaBtn_2);

        pushButton = new QPushButton(QtStdDialogs);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(QtStdDialogs);

        QMetaObject::connectSlotsByName(QtStdDialogs);
    } // setupUi

    void retranslateUi(QDialog *QtStdDialogs)
    {
        QtStdDialogs->setWindowTitle(QApplication::translate("QtStdDialogs", "QT\346\240\207\345\207\206\345\257\271\350\257\235\346\241\206", 0));
        fileDiaBtn->setText(QApplication::translate("QtStdDialogs", "\346\226\207\344\273\266\345\257\271\350\257\235\346\241\206", 0));
        colorDiaBtn->setText(QApplication::translate("QtStdDialogs", "\351\242\234\350\211\262\345\257\271\350\257\235\346\241\206", 0));
        fontDiaBtn->setText(QApplication::translate("QtStdDialogs", "\345\255\227\344\275\223\345\257\271\350\257\235\346\241\206", 0));
        fontDisplay->setText(QApplication::translate("QtStdDialogs", "\346\230\216\350\247\201\344\277\261\345\235\217\357\274\214\350\213\261\351\233\204\345\256\211\345\234\250\343\200\202", 0));
        fontDiaBtn_2->setText(QApplication::translate("QtStdDialogs", "\346\240\207\345\207\206\350\276\223\345\205\245\345\257\271\350\257\235\346\241\206", 0));
        pushButton->setText(QApplication::translate("QtStdDialogs", "\346\240\207\345\207\206\346\266\210\346\201\257\345\257\271\350\257\235\346\241\206", 0));
    } // retranslateUi

};

namespace Ui {
    class QtStdDialogs: public Ui_QtStdDialogs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSTDDIALOGS_H
