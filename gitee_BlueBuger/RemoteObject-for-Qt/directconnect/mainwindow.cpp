#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QSharedPointer<TransferNewsReplica> ptr, QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(600, 400);
    setupUi();

    m_dc = new DirectConnect(ptr);
    connect(m_dc, SIGNAL(sig_newMessage(QString)), this, SLOT(onReceive(QString)));
}

void MainWindow::setupUi()
{
    m_textEdit = new QTextEdit;
    QTextCursor textCursor = m_textEdit->textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setBottomMargin(10);
    textCursor.setBlockFormat(textBlockFormat);
    m_textEdit->setTextCursor(textCursor);
    m_textEdit->setFocusPolicy(Qt::NoFocus);

    m_lineEdit = new QLineEdit;
    m_lineEdit->setFixedHeight(30);

    m_btn = new QToolButton;
    m_btn->setFixedSize(80, 30);
    m_btn->setText("Send");
    m_btn->setFocusPolicy(Qt::NoFocus);
    connect(m_btn, &QToolButton::clicked, this, &MainWindow::onSend);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_lineEdit);
    hlayout->addWidget(m_btn);
    hlayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_textEdit);
    layout->addLayout(hlayout);
    layout->setSpacing(8);
    layout->setContentsMargins(10, 10, 10, 10);

    setLayout(layout);
}

void MainWindow::onSend()
{
    QString msg = m_lineEdit->text();
    m_lineEdit->clear();

    emit m_dc->sig_sendMessage(msg);
}

void MainWindow::onReceive(QString msg)
{
    m_textEdit->append(msg);
}



