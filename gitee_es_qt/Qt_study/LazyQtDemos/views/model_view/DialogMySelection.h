#ifndef DIALOGMYSELECTION_H
#define DIALOGMYSELECTION_H

#include <QDialog>

class QTableView;

namespace Ui {
class DialogMySelection;
}

class DialogMySelection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMySelection(QWidget *parent = 0);
    ~DialogMySelection();

public slots:
    void getCurrentItemData();
    void toggleSelection();

private:
    Ui::DialogMySelection *ui;

    QTableView *tableView;
};

#endif // DIALOGMYSELECTION_H
