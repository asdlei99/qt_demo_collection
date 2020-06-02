#ifndef DIALOGSTAR_H
#define DIALOGSTAR_H

#include <QDialog>

class QTableWidget;

namespace Ui {
class DialogStar;
}

class DialogStar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStar(QWidget *parent = 0);
    ~DialogStar();

private:
    void populateTableWidget(QTableWidget *tableWidget);

private:
    Ui::DialogStar *ui;

    QTableWidget *tableWidget;
};

#endif // DIALOGSTAR_H
