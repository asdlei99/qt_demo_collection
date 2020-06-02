#ifndef QT5DEMOSDLG_H
#define QT5DEMOSDLG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class Qt5DemosDlg;
}

class Qt5DemosDlg : public QDialog
{
    Q_OBJECT

public:
    explicit Qt5DemosDlg(QWidget *parent = 0);
    ~Qt5DemosDlg();

private slots:
    void on_Qt5DemosWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::Qt5DemosDlg *ui;
};

#endif // QT5DEMOSDLG_H
