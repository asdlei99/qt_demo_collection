#ifndef _RINPUT_FORM_H_
#define _RINPUT_FORM_H_

#include <QMainWindow>
#include <QRegExp>

class QGridLayout;
class QLineEdit;
class QRegExpValidator;
class QLabel;
//start

class RinputForm : public QMainWindow {
    Q_OBJECT
 public:
    RinputForm();
    void setupForm();
 public slots:
    void computeResult();
 private:
    QRegExpValidator* m_PhoneValid;
    QGridLayout* m_Layout;
    QLineEdit* m_PhoneEntry;
    QWidget* m_Center;
    QLabel* m_PhoneResult;
    QString m_Phone;
    static QRegExp sm_PhoneFormat; 
};
//end
#endif

