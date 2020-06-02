#include "inspector.h"
#include <QVBoxLayout>
#include <QtWebView/QtWebView>
#include <QWebEngineView>

Inspector::Inspector()
    :m_pWebView(new QWebEngineView(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_pWebView);
    setLayout(layout);

    m_pWebView->load(QUrl("http://localhost:1112"));

}

Inspector::~Inspector()
{
    if(m_pWebView == nullptr){
        delete m_pWebView;
        m_pWebView = nullptr;
    }
}
