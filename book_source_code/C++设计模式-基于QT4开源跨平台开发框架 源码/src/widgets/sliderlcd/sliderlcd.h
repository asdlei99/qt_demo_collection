#ifndef _SLIDER_LCD_H_
#define _SLIDER_LCD_H_

#include <QMainWindow>

/**
   Simple GUI class which includes a slider and an LCD display of the value
   of the slider
*/
//start
class QSlider;
class QLCDNumber;
class LogWindow;
class QErrorMessage;

class SliderLCD : public QMainWindow {
    Q_OBJECT
 public:
    enum {SUBZERO = -273, TOOHOT = 360 };
    SliderLCD(int minval = SUBZERO, int maxval = TOOHOT);
    void initSliderLCD();
    
  public slots:
    void checkValue(int newValue);
    void showMessage();
    
 signals:
    void toomuch();
 private:
    int m_Minval, m_Maxval;
    LogWindow* m_LogWin;
    QErrorMessage *m_ErrorMessage;
    QLCDNumber* m_LCD;
    QSlider* m_Slider;
};
#endif
//end

