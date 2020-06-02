#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QToolButton>
#include <QTextEdit>
#include <QLineEdit>

#include "directconnect.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QSharedPointer<TransferNewsReplica> ptr, QWidget *parent = nullptr);

public Q_SLOTS:
    void onSend();
    void onReceive(QString);

protected:
    void setupUi();

private:
    QTextEdit *m_textEdit;
    QLineEdit *m_lineEdit;

    QToolButton *m_btn;

    DirectConnect *m_dc;
};

#endif // MAINWINDOW_H
