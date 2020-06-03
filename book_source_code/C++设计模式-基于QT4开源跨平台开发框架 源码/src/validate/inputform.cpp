#include "inputform.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QLabel>
#include <QFrame>
#include <QString>
//start
InputForm::InputForm(int ibot, int itop, double dbot, double dtop):
    m_BotI(ibot), m_TopI(itop), m_BotD(dbot), m_TopD(dtop),
    m_IValid(new QIntValidator(ibot, itop, this)),
    m_DValid(new QDoubleValidator(dbot, dtop, 2, this)),
    //end
    m_Layout(new QGridLayout),
    m_IntEntry(new QLineEdit("0")),
    m_DoubleEntry(new QLineEdit("0")),
    m_Result(new QLabel("0")), 
    m_Center(new QWidget(this)) {
    setCentralWidget(m_Center);
    setupForm();
}
//start
void InputForm::setupForm() {
    //end
    setWindowTitle("Work-Study Salary Calculator");
    QString ltext(QString("Hours Worked (between %1 and %2)")
                  .arg(m_BotI).arg(m_TopI));
    QLabel *label = new QLabel(ltext, m_Center);
    m_Layout->addWidget(label, 0,0);
    m_Layout->addWidget(m_IntEntry,0,1);
    ltext = QString("Hourly Pay Rate (between %1 and %2)")
        .arg(m_BotD).arg(m_TopD);
    label = new QLabel(ltext, m_Center);
    m_Layout->addWidget(label, 1,0);
    m_Layout->addWidget(m_DoubleEntry,1,1);
    label = new QLabel("Total Pay for the week: ", m_Center);
    m_Layout->addWidget(label, 2,0);
    m_Result->setFrameStyle(QFrame::Panel);
    m_Result->setFrameShadow(QFrame::Raised);
    m_Layout->addWidget(m_Result,2,1);
    m_Center->setLayout(m_Layout);
//start
    m_IntEntry->setValidator(m_IValid);
    m_DoubleEntry->setValidator(m_DValid);
    connect(m_IntEntry, SIGNAL(returnPressed()), 
            this, SLOT(computeResult()));
    connect(m_DoubleEntry, SIGNAL(returnPressed()),
            this, SLOT(computeResult()));
}
//end

void InputForm::computeResult() {
    double d = m_DoubleEntry->text().toDouble();
    int i = m_IntEntry->text().toInt();
    double res = d * i;
    m_Result->setText(QString("%1").arg(res));
}


