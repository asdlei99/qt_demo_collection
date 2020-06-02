#ifndef ECHOWINDOW_H
#define ECHOWINDOW_H

#include <QWidget>

#include "EchoInterface.h"

QT_BEGIN_NAMESPACE
class QString;
class QLineEdit;
class QLabel;
class QPushButton;
class QGridLayout;
QT_END_NAMESPACE

class EchoWindow : public QWidget
{
    Q_OBJECT

public:
    EchoWindow(QWidget *parent = 0);
    ~EchoWindow();

private slots:
    void sendEcho();

private:
    void createGUI();
    bool loadPlugin();

    EchoInterface *echoInterface;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *button;
    QGridLayout *layout;
};

#endif // ECHOWINDOW_H
