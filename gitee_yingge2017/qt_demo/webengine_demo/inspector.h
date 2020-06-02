#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

class QWebEngineView;
class Inspector:public QWidget
{
    Q_OBJECT
public:
    Inspector();
    ~Inspector();
private:
    QWebEngineView *m_pWebView;
};

#endif // INSPECTOR_H
