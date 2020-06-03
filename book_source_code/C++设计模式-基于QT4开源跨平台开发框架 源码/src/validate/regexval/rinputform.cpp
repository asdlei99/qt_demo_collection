#include "rinputform.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QLabel>
#include <QFrame>
#include <QString>
//start
QRegExp RinputForm::sm_PhoneFormat(
  "(\\+?1[- ]?)?\\(?(\\d{3,3})\\)?[\\s-]?(\\d{3,3})[\\s-]?(\\d{4,4})");

RinputForm::RinputForm() :
    m_PhoneValid(new QRegExpValidator(sm_PhoneFormat, this)),
    //end
    m_Layout(new QGridLayout),
    m_PhoneEntry(new QLineEdit),
    m_Center(new QWidget(this)),
    m_PhoneResult(new QLabel) {
    setCentralWidget(m_Center);
    setupForm();
}
//start
void RinputForm::setupForm() {
    //end
    setWindowTitle("Phone Number Validator");
    QLabel *label = new QLabel("Phone number:", m_Center);
    m_Layout->addWidget(label, 0,0);
    m_Layout->addWidget(m_PhoneEntry,0,1);
    label = new QLabel("Phone result: ", m_Center);
    m_Layout->addWidget(label, 1,0);
    m_PhoneResult->setFrameStyle(QFrame::Panel);
    m_PhoneResult->setFrameShadow(QFrame::Raised);
    m_Layout->addWidget(m_PhoneResult,1,1);
    m_Center->setLayout(m_Layout);
    //start
    m_PhoneEntry->setValidator(m_PhoneValid);
    connect(m_PhoneEntry, SIGNAL(returnPressed()), 
            this, SLOT(computeResult()));
}

void RinputForm::computeResult() {
    m_Phone = m_PhoneEntry->text();
    if (sm_PhoneFormat.exactMatch(m_Phone)) {
        QString areacode = sm_PhoneFormat.cap(2);
        QString exchange = sm_PhoneFormat.cap(3);
        QString number = sm_PhoneFormat.cap(4);
        m_PhoneResult->setText(QString("(US/Canada) +1 %1-%2-%3")
              .arg(areacode).arg(exchange).arg(number));
    }
}
//end

