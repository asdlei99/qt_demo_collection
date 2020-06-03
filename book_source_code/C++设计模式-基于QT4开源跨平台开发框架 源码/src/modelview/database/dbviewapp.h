#ifndef DBVIEWAPP_H
#define DBVIEWAPP_H

class QTableView;
class QSqlTableModel;
class Mp3TableModel;

#include <QApplication>

class DbViewApp : public QApplication {
    Q_OBJECT

   public:
   static bool createConnection();
   DbViewApp(int argc, char* argv[]);
   virtual ~DbViewApp();

   private:
   QSqlTableModel *model;
   QTableView *view;
   
};

#endif        //  #ifndef DBVIEWAPP_H

