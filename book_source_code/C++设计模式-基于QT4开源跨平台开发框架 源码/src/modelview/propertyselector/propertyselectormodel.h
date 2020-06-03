#ifndef _PROPERTY_SELECTOR_MODEL_H_
#define _PROPERTY_SELECTOR_MODEL_H_

#include <QObject>
#include <QStringList>
#include <QAbstractListModel>
#include <QVariant>
#include <QItemSelection>

using namespace Qt;
class DataObject;
class QAction;

/** This class facilitates the use of the properties of another class as
column headers in a view. It has methods that allow the user to select
properties in the associated list view and it has accessors for
getting either the full list of properties or the list of selected properties.
*/
//start id=overrides
class PropertySelectorModel : public QAbstractListModel {
    Q_OBJECT
public:
    PropertySelectorModel(DataObject* propnamesrc, QObject* parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = DisplayRole) const;
    ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
//end
//start id=additional-methods
    void initializePropertyNames();
    QStringList getAllPropertyNames() const;
    QStringList getSelectedPropertyNames() const;
//end    
//start id=signals-slots
signals:
    void readyQuit();
    void readyCloseWindow(bool);
    void readyRestore(QList<QPersistentModelIndex>);
public slots:
    void updateSelects(QModelIndexList selects);
    void prepareShow();
//end
//start id=overrides
private:
    QStringList m_PropertyNames;
    DataObject* m_PropNameSource;
//stop
//start id=signals-slots
    QList<QPersistentModelIndex> m_SelectedIndexes;
//stop
//start id=overrides
};
//stop
#endif

