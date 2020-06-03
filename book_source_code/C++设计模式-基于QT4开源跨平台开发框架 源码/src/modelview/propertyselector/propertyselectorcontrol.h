#ifndef _PROPERTY_SELECTOR_CONTROL_
#define _PROPERTY_SELECTOR_CONTROL_

#include <QObject>
#include <QMainWindow>
#include <dataobject.h>

class PropertySelectorModel;
class PropertySelectorView;

/** This is a controler class that connects the model and the view classes
for an application that facilitates the selection of column headers for a gui
application that handles a class with properties.
*/
class PropertySelectorControl : public QMainWindow {
    Q_OBJECT
  public:
    PropertySelectorControl(DataObject* sourceptr);
    QString getSelectedPropertyNames() const;
  signals:
    void readyShow();
  public slots:
    void showWindow(bool);
    void outputSelects(bool);
  private:
    PropertySelectorModel* m_Chdm;
    PropertySelectorView*  m_Chdv;
};

#endif

