#ifndef X_WEB_WIDGET_H
#define X_WEB_WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QWebEngineView>
#include <QStackedLayout>
#include <QThread>
#include <QLineEdit>
#include <QTextEdit>

#include "webview.h"
class WebWidget : public QWidget
{
    Q_OBJECT

public:
    static QString renbaoLoginUrl;
    static QString renbaoSelectUrl;
    static QString renbaoSelectUrl2;
private:

    QStackedLayout * StackedLayout ;
    QWidget *emptyWidget;

    WebView *webView;
    QComboBox *insuranceCombo;
    QPushButton *useXAccountBtn;
    QPushButton *toSelectPageBtn;
    QPushButton *runJsBtn;
    QTextEdit *js;

    QPushButton *loginBtn;
    QPushButton *runBtn;
    QLineEdit *findTextEdit;
    QPushButton *findTextBtn;

    int pageIndex;

public:
    WebWidget(QWidget *parent = 0);
    ~WebWidget();

    void initWidget();
    // 切换页面
    void switchPage();

    void beginToRun();
    void runOnce();
    void parseData(QString data);
public slots:
    void defaultUserBtnClicked(); //使用默认用户
    void toSelectPageBtnClicked(); //跳转到查询页面
    void runJsBtnSlot();
    void loginBtnClicked(); //登录
    void runBtnClicked();
    void findTextBtnClicked(); //
    void insuranceCompanyChange(int index);
    void loadFinishedX(QString data,bool success);
};

#endif // WIDGET_H
