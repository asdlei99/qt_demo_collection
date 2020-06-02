#include "dbtest.h"
#include "dbtest.h"
#include "connector.h"
#include "mysql_driver.h"

#include <iostream>


using namespace std;

void dbtest(){
    cout<<"1 dbtest"<<endl;
#if 0
    //    sql::mysql::NativeAPI::NativeDriverWrapper MySQL_Driver *driver;
    sql::mysql::MySQL_Driver *driver =  mysql::get_driver_instance();
    if(driver == NULL)
    {
        cout << "get driver err\n";
        return  ;
    }
#endif

    try{
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();

        cout<<"db major version:"<<driver->getMajorVersion()<<endl;
        cout<<driver->getName()<<endl;
        cout<<driver->getMajorVersion()<<endl;
        cout<<driver->getMinorVersion()<<endl;
        cout<<driver->getPatchVersion()<<endl;

        //delete driver;
        con = driver->connect("127.0.0.1", "ding", "ding");
        if(con == NULL){
            cout<<"con is NULL"<<endl;
        }
        if(con->isValid()){
            cout<<"con is valid"<<endl;
        }else{
            cout<<"con is unvalid"<<endl;
            return;
        }
        try{
            cout<<"setSchema start"<<endl;
            con->setSchema("db");
            cout<<"setSchema end"<<endl;
        }catch ( SQLException &e )
        {
            cout<<"setSchema,数据库 连接异常： "<<e.what()<<endl;
            cout << "ERROR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << ")" << endl;
        }
        catch ( std::runtime_error &e )
        {
            cout<<"setSchema,数据库 运行时异常： "<<e.what()<<endl;
        }
        catch(std::exception &e){
            cout<<"setSchema,catch else,"<<e.what()<<endl;
        }

        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("select id,ip from lf_adip;");
        while (res->next()) {
            //            cout << "\t... MySQL replies: ";
            /* Access column data by alias or column name */
            cout << res->getString("ip") << endl;
            //            cout << "\t... MySQL says it again: ";
            /* Access column data by numeric offset, 1 is the first column */
           // cout << res->getString(1) << endl;
        }



        delete res;
        delete stmt;
        delete con;

#if 0
        sql::Driver *driver  = get_driver_instance();
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        /* Create a connection */
#endif
        //  con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    }
    catch ( SQLException &e )
    {
        cout<<"数据库 连接异常： "<<e.what()<<endl;
        cout << "ERROR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << ")" << endl;
    }
    catch ( std::runtime_error &e )
    {
        cout<<"数据库 运行时异常： "<<e.what()<<endl;
    }
    catch(std::exception &e){
        cout<<"db,catch else,"<<e.what()<<endl;
    }
    //        conn = driver->connect(DBHOST, USER, PASSWORD);
    //        state = conn->createStatement();
    //        if(!conn || !state)
    //            return false;



#if 0


    DBPool  db = DBPool::GetInstance();

    db.initPool("tcp://127.0.0.1:3306", "ding", "ding", 100);
    cout<<"2 db init Pool"<<endl;

    Connection *con;
    Statement *state;
    ResultSet *result;
    // con = db.GetConnection();//get a db con

    cout<<"3 end of dbtest"<<endl;
#endif
    cout<<"end of dbtest"<<endl;
}
