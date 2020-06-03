
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QApplication>

QTreeWidgetItem *item(QString name, QTreeWidgetItem* parent=0) {
    QTreeWidgetItem *retval = new QTreeWidgetItem(parent);
    retval->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
        | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled |
        Qt::ItemIsEnabled);
    retval->setText(0, name);
    return retval;
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QTreeWidgetItem *root = item("root");
    QTreeWidgetItem *colors = item("colors", root);
    item("blue", colors);
    item("red", colors);
    item("orange", colors);
    
    QTreeWidgetItem *sports = item("sports", root);
    item("baseball", sports);
    item("hockey", sports);
    item("curling", sports);
    
    QTreeWidgetItem *food = item("food", root);
    item("rutabega", food);
    item("macademia nuts", food);
    item("bok-choy", food);
    
    QTreeWidget *tree = new QTreeWidget();
    tree->addTopLevelItem(root);
    tree->setColumnCount(1);
    tree->setVisible(true);
    return app.exec();
}
