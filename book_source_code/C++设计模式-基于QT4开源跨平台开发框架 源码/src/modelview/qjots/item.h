#ifndef ITEM_H
#define ITEM_H

#include <QTreeWidgetItem>
#include <QDomElement>
#include "dataobject.h"

class QDomDocument;
//start
class Item : public DataObject, public QTreeWidgetItem {
 Q_OBJECT
  Q_PROPERTY( QString Name READ name WRITE setName );
 public:
    Item();
    virtual ~Item() {}    
    QTreeWidgetItem* parent() const { /* Required to disambiguate between
										 the two base class versions */
       return QTreeWidgetItem::parent();
    }
    virtual void setName(QString name) ;
    /**
    @param doc a QDomDocument for creating new elements. 
    @return a DOM element (tree) which corresponds to this item.
            Ignores children - Non-recursive. */ 
    virtual QDomElement element( QDomDocument doc)=0;
    /**
    @return a widget which gives a detailed view of the
        information in this item. For a Bookmark, it retruns
        a QTextBrowser. For an ordinary Note, it returns a
        QTextEdit. 
     */
    virtual QWidget* detailView() =0;
    /**
    @return what is to be displayed in the treeview.
    */
    virtual QString name() const ;
};
//end
#endif        //  #ifndef ITEM_H

