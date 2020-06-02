#include "DialogStar.h"
#include "ui_DialogStar.h"
#include <QTableWidget>

#include "stardelegate/StarRating.h"
#include "stardelegate/StarDelegate.h"

DialogStar::DialogStar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStar)
{
    ui->setupUi(this);

    tableWidget = new QTableWidget(4, 4, this);

    tableWidget->setItemDelegate(new StarDelegate);
    tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked
                                | QAbstractItemView::SelectedClicked);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList headerLabels;
    headerLabels << "Title" << "Genre" << "Artist" << "Rating";
    tableWidget->setHorizontalHeaderLabels(headerLabels);

    populateTableWidget(tableWidget);

    tableWidget->resizeColumnsToContents();
//    tableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    tableWidget->resize(700, 500);
}

DialogStar::~DialogStar()
{
    delete ui;
}

void DialogStar::populateTableWidget(QTableWidget *tableWidget)
{
    static const struct {
        const char *title;
        const char *genre;
        const char *artist;
        int rating;
    } staticData[] = {
//! [0] //! [1]
        { "Mass in B-Minor", "Baroque", "J.S. Bach", 5 },
//! [1]
        { "Three More Foxes", "Jazz", "Maynard Ferguson", 4 },
        { "Sex Bomb", "Pop", "Tom Jones", 3 },
        { "Barbie Girl", "Pop", "Aqua", 5 },
//! [2]
        { 0, 0, 0, 0 }
//! [2] //! [3]
    };
//! [3] //! [4]

    for (int row = 0; staticData[row].title != 0; ++row) {
        QTableWidgetItem *item0 = new QTableWidgetItem(staticData[row].title);
        QTableWidgetItem *item1 = new QTableWidgetItem(staticData[row].genre);
        QTableWidgetItem *item2 = new QTableWidgetItem(staticData[row].artist);
        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setData(0,
                       QVariant::fromValue(StarRating(staticData[row].rating)));

        tableWidget->setItem(row, 0, item0);
        tableWidget->setItem(row, 1, item1);
        tableWidget->setItem(row, 2, item2);
        tableWidget->setItem(row, 3, item3);
    }
}


