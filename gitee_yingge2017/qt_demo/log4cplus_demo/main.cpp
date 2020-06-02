#include <QCoreApplication>
#include <qfile.h>
#include <qdebug.h>

#include "log4cplus/log4cplus.h"
#include "logger.h"
#include "common.h"

#include <memory>

//#define UNICODE


void test(){
    //用Initializer类进行初始化
    log4cplus::Initializer initializer;

    //第1步：创建ConsoleAppender
    log4cplus::SharedAppenderPtr appender(new log4cplus::ConsoleAppender());

    //第2步：设置Appender的名称和输出格式（SimpleLayout）
    appender->setName(LOG4CPLUS_TEXT("console"));
    appender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout));

    //第3步：获得一个Logger实例，并设置其日志输出等级阈值
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT ("test"));
    logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);

    //第4步：为Logger实例添加ConsoleAppender
    logger.addAppender(appender);

    //第5步：使用宏将日志输出
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Hello world"));
    LOG4CPLUS_DEBUG(logger,LOG4CPLUS_TEXT("Hello world111111111111"));
}

void test2(){
    //用Initializer类进行初始化
    log4cplus::Initializer initializer;

    //第1步：创建ConsoleAppender和FileAppender(参数app表示内容追加到文件)
    log4cplus::SharedAppenderPtr consoleAppender(new log4cplus::ConsoleAppender);
    log4cplus::SharedAppenderPtr fileAppender(new log4cplus::FileAppender(
                                                  LOG4CPLUS_TEXT("log.txt"),
                                                  std::ios_base::app
                                                  )
                                              );

    //第2步：设置Appender的名称和输出格式
    //ConsoleAppender使用SimpleLayout
    //FileAppender使用PatternLayout
    consoleAppender->setName(LOG4CPLUS_TEXT("console"));
    consoleAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout()));
    fileAppender->setName(LOG4CPLUS_TEXT("file"));
    log4cplus::tstring pattern = LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S,%Q} [%t] %-5p %c - %m [%l]%n");
    fileAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern)));

    //第3步：获得一个Logger实例，并设置其日志输出等级阈值
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT ("test"));
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    //第4步：为Logger实例添加ConsoleAppender和FileAppender
    logger.addAppender(consoleAppender);
    logger.addAppender(fileAppender);

    //第5步：使用宏将日志输出
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Hello world"));
}
void test3(){
    //    log4cplus.appender.ALL_MSGS.layout.ConversionPattern=[%-5p %d{%y-%m-%d %H:%M:%S}] [%l]%n%m%n%n
    //    log4cplus.properties
    QString iniPath = QCoreApplication::applicationDirPath() + "/log.ini";
    if(false == QFile::exists(iniPath)){
        qDebug()<<"log ini no exist:"
               <<iniPath;
    }else{
        qDebug()<<"log exist.";
    }

    log4cplus::PropertyConfigurator::doConfigure(iniPath.toStdWString());

#if 1
    log4cplus::Logger loggerMktBase = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("loggerMkt"));
    //    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));


    log4cplus::Logger lgPltf = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("loggerPlatform"));

    //    LOG4CPLUS_TRACE_METHOD(lgPltf, LOG4CPLUS_TEXT(__FUNCTION__));
    LOG4CPLUS_DEBUG(lgPltf, "This is a DEBUG message");
    LOG4CPLUS_INFO(lgPltf, "This is a INFO message");
    LOG4CPLUS_WARN(lgPltf, "This is a WARN message");
    LOG4CPLUS_ERROR(lgPltf, "This is a ERROR message");
    LOG4CPLUS_FATAL(lgPltf, "This is a FATAL message");


    LOG4CPLUS_FATAL(loggerMktBase, "This is a FATAL message");
#endif
}

void test4(){
    QString iniPath = QCoreApplication::applicationDirPath() + "/log.ini";
    if(false == QFile::exists(iniPath)){
        qDebug()<<"log ini no exist:"
               <<iniPath;
    }else{
        qDebug()<<"log exist.";
    }

    log4cplus::PropertyConfigurator::doConfigure(iniPath.toStdWString());

    log4cplus::Logger rootLogger = log4cplus::Logger::getRoot();

    LOG4CPLUS_DEBUG(rootLogger,"this is message.");

    //    log4cplus::Logger apdPlatformLogger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("apdPlatform"));
    //    LOG4CPLUS_DEBUG(apdPlatformLogger,"this is message.");

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"log4cplus demo";

    //    test();
    //    test2();
    //    test3();
    //    test4();

    QString iniPath = QCoreApplication::applicationDirPath() + "/log.ini";
    if(false == QFile::exists(iniPath)){
        qDebug()<<"log ini no exist:"
               <<iniPath;
    }else{
        qDebug()<<"log exist.";
    }

#if 0
    string s = "main";
    //    logger * log =  logger::instance();
    logger *log = new logger;


    log->setInit(iniPath.toStdString());
    *log<<s;
#endif

#if 1
    logger log;
    log.setInit(iniPath.toStdString());
    log<<"fdsf";
    log<<1000;
#endif

    logs.setInit(iniPath.toStdString());
    logs<<"logs main.";



    qDebug()<<"log4cplus demo end.";
//    qInfo()<<"fdsaf";
    return a.exec();
}


#if 0
#include "log4cplus/log4cplus.h"
#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>

using namespace log4cplus;
using namespace log4cplus::helpers;




#endif




