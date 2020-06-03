#ifndef _INPUT_FORM_H_
#define _INPUT_FORM_H_

#include <QMainWindow>

class QGridLayout;
class QLineEdit;
class QIntValidator;
class QDoubleValidator;
class QLabel;
//start
class InputForm : public QMainWindow {
    Q_OBJECT
        public:
    InputForm(int ibot, int itop, double dbot, double dtop);
    void setupForm();
    public slots:
        void computeResult();
 private:
    int m_BotI, m_TopI;
    double m_BotD, m_TopD;
    QIntValidator* m_IValid;
    QDoubleValidator* m_DValid;
    QGridLayout* m_Layout;
    QLineEdit *m_IntEntry, *m_DoubleEntry;
    QLabel* m_Result;
    QWidget* m_Center;
};
//end
#endif

