//start id=createconnection
//#include "mp3tablemodel.h"

#include "dbviewapp.h"
#include <QSqlTableModel>
#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlError>

bool DbViewApp::createConnection() 
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("mp3db"); /* It would be better to save/get
	     this info from QSettings. */
    db.setUserName("mp3user");
    db.setPassword("mp3dbpw"); /* If this was sensitive data,
	      we would not use QSettings but an encrypted file 
		  instead. */
		  
    
    if (!db.open()) {
        qCritical("Cannot open database: %s (%s)", 
                  db.lastError().text().toLatin1().data(),
                  qt_error_string().toLocal8Bit().data());
        return false;
    }
    else {
        qDebug() << "Database Opened";
        return true;
    }
    
}

//end


//start id=init
DbViewApp::DbViewApp(int argc, char* argv[]) :
    QApplication(argc, argv) {
      
    createConnection(); /* The connection must be created
                           before any models are created */
    model = new QSqlTableModel(this);
    model->setTable("FileTagger");   
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
 
    view = new QTableView();
    view->setWindowTitle("Mp3s in the Database");
    view->setModel(model);      
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QTableView::SingleSelection);
    model->select();
    view->setVisible(true);
    qDebug() << "DbViewApp()";
}
//end

DbViewApp::~DbViewApp() {
    delete view;
}

int main(int argc, char* argv[]) {
    DbViewApp app(argc, argv);
    return app.exec();
}

