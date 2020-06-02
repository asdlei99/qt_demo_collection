#include "WebTest.h"
#include <QFile>
#include <QCoreApplication>

WebTest::WebTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    initUi();
    initConncetion();
}

/** @fn     WebTest::initUi
 *  @brief  �����ʼ��
 *  @return void 
 */
void WebTest::initUi()
{
    m_pWebView = ui.webEngineView;
    m_pWebChannel = new QWebChannel(this);
    loadHtml();

    // ע��һ��qtui����  html��ͨ����������qt������Ϣ
    m_pWebChannel->registerObject(QString("qtui"), this);
    m_pWebView->page()->setWebChannel(m_pWebChannel);
}

/** @fn     WebTest::initConncetion
 *  @brief  ��ʼ���źŲۺ���
 *  @return void 
 */
void WebTest::initConncetion()
{
    // ����js
    connect(ui.callJSBtn, &QPushButton::clicked, [&]() 
    {
        QString jsStr = QString("addCircle()");
        m_pWebView->page()->runJavaScript(jsStr);
    });

    // ��ȡjs����ֵ
    connect(ui.getJsRetBtn, &QPushButton::clicked, [&]() 
    {
        auto str = getJsRetString();
        ui.label->setText(str);
    });
}

/** @fn     WebTest::loadHtml
 *  @brief  ���ص�ͼ
 *  @return void 
 */
void WebTest::loadHtml()
{
    QString htmlPath = QCoreApplication::applicationDirPath() + "/BMap.html";

    QFile file(htmlPath);
    if (!file.exists())
    {
        return;
    }

    m_pWebView->load(QUrl("file:///" + htmlPath));
}

/** @fn     WebTest::getJsRetString
 *  @brief  ��ȡweb�˷���ֵ
 *  @return QString 
 */
QString WebTest::getJsRetString()
{
    QEventLoop loop;
    QString jsStr = "getInfo();";

    QString retStr{}; // ����ֵ
    // ͨ��loopѭ���ȵ��ص����������ټ���
    m_pWebView->page()->runJavaScript(jsStr, [&](const QVariant &v)
    {
        retStr = v.toString();
        loop.quit();
    });
    loop.exec();

    return retStr;
}

/** @fn     WebTest::recieveJsMessage
 *  @brief  ��������webhtml����Ϣ
 *  @param  const QString & jsMsg web��֪ͨ����Ϣ
 *  @return void 
 */
void WebTest::recieveJsMessage(const QString& jsMsg)
{
    ui.label->setText(jsMsg);
}
