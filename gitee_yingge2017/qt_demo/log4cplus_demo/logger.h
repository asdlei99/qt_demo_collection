#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <log4cplus/log4cplus.h>

using namespace  std;

class logger
{
private:
    //    explicit logger();
public:
    explicit logger();
    static logger *instance();
    ///设置配置文件路径
    bool setInit(const string&s);

    void operator<<(const string &s);
    void operator <<(const int num);
private:
    std::string WString2String(const std::wstring& ws);
    std::wstring String2WString(const std::string& s);
private:
    log4cplus::Logger m_rootLogger;
};


#endif // LOGGER_H
