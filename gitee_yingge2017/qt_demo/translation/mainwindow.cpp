#include "mainwindow.h"
#include <qlabel.h>
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <qfile.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_languageType = E_CN;

    //    QLabel *label = new QLabel(this);
    //    label->setText(tr("中文，雷阿伦"));
    //    setCentralWidget(label);

    QString qmPath = QCoreApplication::applicationDirPath() +
            "/en.qm";

    qDebug()<<"qmPath:"<<qmPath;
    if(false == QFile::exists(qmPath) ){
        qDebug()<<"qmPath not exist.";
    }

    if(false == m_translator.load(qmPath,".")){
        qDebug()<<"load failed.";
    }else{
        qDebug()<<"load succ.";
    }

    //    if(false == QApplication::instance()->installTranslator(&m_translator)){
    //        qDebug()<<"installTranslator failed.";
    //    }else{
    //        qDebug()<<"installTranslator succ.";
    //    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_translateButton_clicked()
{
    qDebug()<<"on_translateButton_clicked";

    if(m_languageType == E_CN){
        if(false == QApplication::instance()->installTranslator(&m_translator)){
            qDebug()<<"installTranslator failed.";
        }else{
            qDebug()<<"installTranslator succ.";
            m_languageType = E_EN;
        }
    }else if(m_languageType == E_EN){
        //删除英文翻译，恢复默认的中文
        QApplication::instance()->removeTranslator(&m_translator);
        m_languageType = E_CN;
    }
    //必须要添加界面刷新语句
    ui->retranslateUi(this);

    /*
      此时已经可以完成当前界面的翻译，然后如果每个页面都需要，则需要在每个界面加入
void Dialog_Language::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
*/

}



























