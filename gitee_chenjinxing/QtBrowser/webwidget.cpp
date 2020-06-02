#include "webwidget.h"

#include <QPushButton>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QGridLayout>
#include <QWebChannel>
#include <QComboBox>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTextStream>
#include <QFile>
#include "public.h"
#include "bridge.h"
//QString WebWidget::renbaoLoginUrl ="https://www.baidu.com/";
//QString WebWidget::renbaoLoginUrl ="http://211.160.72.166:8080/ydsys/loginAction.do?method=init";

//QString WebWidget::renbaoLoginUrl ="https://www.axatp.com/service/";
QString WebWidget::renbaoLoginUrl ="https://xinbao.sinosig.com/app/customServ/policyQuery.html";

QString WebWidget::renbaoSelectUrl ="http://www.epicc.com.cn/fuwu/chexianbaodanlipei/";
QString WebWidget::renbaoSelectUrl2 ="http://www.epicc.com.cn/newecenter/views/serviceCenter/carPolicyQuery.html";



WebWidget::WebWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
    pageIndex = 0;
}

WebWidget::~WebWidget()
{
    //webView->deleteLater();
}
void WebWidget::loadFinishedX(QString data,bool success)
{
    if(!success)
        return;
    if(data.startsWith(Public::tiantianLoginFinishUrl)){
        qDebug()<<"登录成功";
        this->webView->setUrl(Public::tiantianDetailUrl);
    }else if(data.startsWith(Public::tiantianDetailUrl)){
        qDebug()<<"查询页面访问成功";
    }

}

void WebWidget::initWidget()
{
    //选择保险公司
    insuranceCombo =new QComboBox();
    insuranceCombo->addItem("中国人民保险");
    connect(insuranceCombo,SIGNAL(activated(int)),this,SLOT(insuranceCompanyChange(int)));

    //填写用户名和密码
    useXAccountBtn =new QPushButton("use default account");
    connect(useXAccountBtn,SIGNAL(clicked(bool)),this,SLOT(defaultUserBtnClicked()));
    //跳转到查询页面
    toSelectPageBtn =new QPushButton("toSelectPage");
    connect(toSelectPageBtn,SIGNAL(clicked(bool)),this,SLOT(toSelectPageBtnClicked()));

    js =new QTextEdit();
    runJsBtn =new QPushButton("runJsBtn");
    connect(runJsBtn,SIGNAL(clicked(bool)),this,SLOT(runJsBtnSlot()));

    //登录
    loginBtn =new QPushButton("login");
    runBtn =new QPushButton("runBtn");
    connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(loginBtnClicked()));
    connect(runBtn,SIGNAL(clicked(bool)),this,SLOT(runBtnClicked()));

    findTextEdit =new QLineEdit("asdfasdf");
    findTextBtn =new QPushButton("findText");
    connect(findTextBtn,SIGNAL(clicked(bool)),this,SLOT(findTextBtnClicked()));



    webView =new WebView();
    webView->setUrl(Public::tiantianLoginUrl);
    webView->resize(800,600);
    webView->setAttribute(Qt::WA_DeleteOnClose,true);
    connect(webView,SIGNAL(loadFinishedX(QString,bool)),this,SLOT(loadFinishedX(QString,bool)));

    QWebChannel *channel = new QWebChannel();
    channel->registerObject("bridge", (QObject*)bridge::instance());
    webView->page()->setWebChannel(channel);


    QHBoxLayout *hlayout =new QHBoxLayout();
    hlayout->addWidget(insuranceCombo);
    hlayout->addWidget(useXAccountBtn);
    hlayout->addWidget(runJsBtn);
    hlayout->addWidget(js);
    hlayout->addWidget(loginBtn);
    hlayout->addWidget(runBtn);
    hlayout->addWidget(findTextEdit);
    hlayout->addWidget(findTextBtn);

    QVBoxLayout *vlayout =new QVBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(webView);

//    QWidget *cenwgt =new QWidget();
//    cenwgt->setLayout(vlayout);
    this->setLayout(vlayout);
    this->resize(1000,800);
}

void WebWidget::defaultUserBtnClicked()
{
    QString userStr ="17770026710";
    QString pwdStr ="abcd12345";
    //填写用户名信息
    QString user ="document.getElementById(\"entryId\").value='"+ \
            userStr+"';";
    webView->page()->runJavaScript(user);
    //填写密码信息
    QString password ="document.getElementById(\"password\").value='"+ \
            pwdStr+"';";
    webView->page()->runJavaScript(password);
}

//跳转到查询页面
void WebWidget::toSelectPageBtnClicked()
{
    webView->setUrl(QUrl(WebWidget::renbaoSelectUrl));
}
void WebWidget::runJsBtnSlot()
{
    QString str =this->js->toPlainText();
    webView->page()->runJavaScript(str);
}
void WebWidget::loginBtnClicked()
{
    //调用网页的登录按钮的事件
    QString loginJs ="doLogin();";
    webView->page()->runJavaScript(loginJs);
    //跳转到查询页面
    //toSelectPageBtnClicked();
    //switchPage();
}
void WebWidget::beginToRun()
{
    pageIndex =0;
    //小于等于页数 该页数应该是输入查询日期后的页数，在查询的前一日 到 上次查询到的日期
    for(int i =0;i <6920;i++)
        runOnce();
}
void WebWidget::runOnce()
{
    QString jstr =" \
        function queryAll2(pageIndex,pageSize) { \
            var pIndex = pageIndex ? pageIndex: initPageInfo.startPage; \
            var pSize = pageSize ? pageSize :initPageInfo.pageSize; \
            var paramterData = $(\"#serarchForm\").serialize(); \
            $.ajax({ \
                url : \"../../services/deviceTravelService/queryAll/\"+pIndex+\"/\"+pSize, \
                type : 'POST', \
                data : paramterData, \
                async : false, \
                cache : false, \
                dataType : 'json', \
                success : function(data, textStatus, jqXHR) { \
                    $('#table').bootstrapTable(\"removeAll\"); \
                    $('#table').bootstrapTable(\"append\", data.list); \
                    p.render({count:data.total,pagesize:data.pageSize,current:data.pageNum}); \
                    setPrivileges(dataPri); \
                }, \
            }); \
            return JSON.stringify($('#table').bootstrapTable('getData')); \
        } \
        queryAll2("+QString::number(pageIndex)+",10); \
        ";
    pageIndex++;
    //调用网页的登录按钮的事件
    webView->page()->runJavaScript(jstr,[&](const QVariant &v){
        QString data =v.toString();
        data =data.replace(QRegExp("\\"),"");
        //data =data.remove(QRegExp("\\"));
        //qDebug() <<data;
        this->parseData(data);
    });
}

void WebWidget::runBtnClicked()
{
    beginToRun();
}
void WebWidget::parseData(QString data)
{
    QByteArray bytes = data.toUtf8();
    //解析JSON
    QJsonParseError json_error;
    //QTJSON所有的元素
    QJsonDocument parse_doucment = QJsonDocument::fromJson(bytes, &json_error);
    //检查json是否有错误
    if (json_error.error == QJsonParseError::NoError &&parse_doucment.isArray())
    {
        QJsonArray lines =parse_doucment.array();
        QFile outFile("data1.txt");
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);

        for(int i=0;i <lines.size();i++)
        {
            QJsonValue line =lines.at(i);
            QJsonObject lineJson =line.toObject();
            QJsonValue id =lineJson.take("id");
            QJsonValue device_code =lineJson.take("device_code");
            QJsonValue poweron_time =lineJson.take("poweron_time");
            QJsonValue poweron_receive_time =lineJson.take("poweron_receive_time");
            QJsonValue poweron_gps_longitude =lineJson.take("poweron_gps_longitude");
            QJsonValue poweron_gps_latitude =lineJson.take("poweron_gps_latitude");
            QJsonValue poweroff_time =lineJson.take("poweroff_time");
            QJsonValue poweroff_receive_time =lineJson.take("poweroff_receive_time");
            QJsonValue poweroff_gps_longitude =lineJson.take("poweroff_gps_longitude");
            QJsonValue poweroff_gps_latitude =lineJson.take("poweroff_gps_latitude");
            QJsonValue status =lineJson.take("status");
            QJsonValue linceNo =lineJson.take("linceNo");
            QJsonValue delete_flag =lineJson.take("delete_flag");

               ts << id.toString()<<","<<
                     device_code.toString()<<","<<
                     poweron_time.toString()<<","<<
                     poweron_receive_time.toString()<<","<<
                     poweron_gps_longitude.toDouble()<<","<<
                     poweron_gps_latitude.toDouble()<<","<<
                     poweroff_time.toString()<<","<<
                     poweroff_receive_time.toString()<<","<<
                     poweroff_gps_longitude.toDouble()<<","<<
                     poweroff_gps_latitude.toDouble()<<","<<
                     status.toInt()<<","<<
                     linceNo.toString()<<","<<
                     delete_flag.toInt()<<endl;
        }
    }else{
        qDebug()<<"error";
    }
}
void WebWidget::findTextBtnClicked()
{
    webView->page()->findText(findTextEdit->text(),QWebEnginePage::FindBackward,[&](const QVariant &v){
        bool i =v.toBool();
        QString str =v.toString();
    });
}

void WebWidget::insuranceCompanyChange(int index)
{
    QString text =insuranceCombo->itemText(index);
    if(0 ==text.compare("中国人民保险"))
    {
        webView->setUrl(QUrl(WebWidget::renbaoLoginUrl));
    }
}
// 切换页面
void WebWidget::switchPage()
{
    int nCount = StackedLayout->count();
    int nIndex = StackedLayout->currentIndex();

    // 获取下一个需要显示的页面索引
    ++nIndex;
    // 当需要显示的页面索引大于等于总页面时，切换至首页
    if (nIndex >= nCount)
        nIndex = 0;
    StackedLayout->setCurrentIndex(nIndex);
}
