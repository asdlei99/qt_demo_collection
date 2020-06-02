#ifndef LOGGER_H
#define LOGGER_H

#include "log4cplus/log4cplus.h"
#include <string>
#include <QString>

using namespace  std;

class Logger
{
private:
    explicit Logger();
public:
    static Logger &instance(){
        static Logger sins;
        return sins;
    }
    static Logger *instancePtr(){
        return &instance();
    }
    ~Logger(){
          m_rootLogger.shutdown();
    }

    ///设置配置文件路径
    bool setInit(const string&s);

    void operator <<(const char* msg);
    void operator <<(const string &s);
    void operator <<(const QString&s);

     void debug(const char* msg,...);
private:
    std::string WString2String(const std::wstring& ws);
    std::wstring String2WString(const std::string& s);
private:
    log4cplus::Logger m_rootLogger;
};

#endif // LOGGER_H
