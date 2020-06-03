#include <QInputDialog>
#include <QStringList>
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    QStringList hobbits, yesno;
    hobbits << "Frodo" << "Bilbo" << "Samwise" << "Merry" << "Pippin";
    yesno << "yes" << "no";
    QString outcome, more, title("Hobbit Selector");
    QString query("Pick your favorite Hobbit");
    do {
        QString pick = 
            QInputDialog::getItem(0, title, query, hobbits);
        outcome = QString("You picked %1, try again?").arg(pick);
        more = QInputDialog::
            getItem(0, "Pick a Hobbit", outcome, yesno, 1, false);
    }  while (more == "yes");
}

