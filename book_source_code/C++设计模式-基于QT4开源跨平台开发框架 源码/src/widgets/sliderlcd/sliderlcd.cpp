#include <QDockWidget>
#include <QSlider>
#include <QErrorMessage>
#include <QLCDNumber>

#include <logwindow.h>
#include "sliderlcd.h"

//start id=main
SliderLCD::SliderLCD(int min, int max) : m_Minval(min), m_Maxval(max) {
    initSliderLCD();
}

void SliderLCD::initSliderLCD() {
    m_LogWin = new LogWindow(); /* defined in the utils library */
    QDockWidget *logDock = new QDockWidget("Debug Log");
    logDock->setWidget(m_LogWin);
    logDock->setFeatures(0); /* cannot be closed, moved, or floated */
    setCentralWidget(logDock);

    m_LCD = new QLCDNumber();
    m_LCD->setSegmentStyle(QLCDNumber::Filled);
    QDockWidget *lcdDock = new QDockWidget("LCD");
    lcdDock->setFeatures(QDockWidget::DockWidgetClosable); /* can be closed */
    lcdDock->setWidget(m_LCD);
    addDockWidget(Qt::LeftDockWidgetArea, lcdDock);

    m_Slider = new QSlider( Qt::Horizontal);
    QDockWidget* sliderDock = new QDockWidget("How cold is it today?");
    sliderDock->setWidget(m_Slider);
    sliderDock->setFeatures(QDockWidget::DockWidgetMovable);
    /* can be moved between doc areas */
    addDockWidget(Qt::BottomDockWidgetArea, sliderDock);

    m_Slider->setRange(m_Minval, m_Maxval);
    m_Slider->setValue(0);
    m_Slider->setFocusPolicy(Qt::StrongFocus);  
    m_Slider->setSingleStep(1); /* step each time left or right arrow 
           key is pressed */
    m_Slider->setPageStep(20); /* step each time PageUp/PageDown key is pressed*/
    m_Slider->setFocus(); /* Give the slider focus. */

    connect(m_Slider, SIGNAL(valueChanged(int)),  /* SliderLCD is a QObject so
        connect does not need scope resolution. */
            this, SLOT(checkValue(int)));
    connect(m_Slider, SIGNAL(valueChanged(int)),
             m_LCD, SLOT(display(int)));

    connect(this, SIGNAL(toomuch()), 
            this, SLOT(showMessage())); /* Normally there is no 
        point in connecting a signal to a slot on the same
        object, but we do it for demonstration purposes. */ 
    m_ErrorMessage = NULL;

}
//end

//start id=emit
void SliderLCD::checkValue(int newValue) {
    if (newValue> 120) {
        emit toomuch(); /* Emit a signal to anyone interested. */
    }
    
}

/* This slot is called indirectly via emit because
   of the connect. */
void SliderLCD::showMessage() {
    if (m_ErrorMessage == NULL) {
        m_ErrorMessage = new QErrorMessage(this);
    }
    if (!m_ErrorMessage->isVisible()) {
        QString message("Too hot outside! Stay in. ");
        m_ErrorMessage->showMessage(message); /* This is a direct
        call to a slot. It's a member function. */
    }
}
//end

