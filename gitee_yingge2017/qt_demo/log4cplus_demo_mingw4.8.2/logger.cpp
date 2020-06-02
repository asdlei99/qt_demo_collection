#include "logger.h"
#include "log4cplus/configurator.h"

#include <string.h>
#include <iostream>

using namespace std;

Logger::Logger()
{
}

//Logger::~Logger()
//{
//    m_rootLogger.shutdown();
//}


bool Logger::setInit(const string &s)
{
    if(s.empty()){
        cout<<"setInit failed,string is empty."<<endl;;
        return false;
    }

    log4cplus::initialize();
    log4cplus::PropertyConfigurator::doConfigure(String2WString(s));

    m_rootLogger = log4cplus::Logger::getRoot();

//    LOG4CPLUS_DEBUG(m_rootLogger,"Logger init succ.");

    return true;
}

void Logger::operator <<(const string &s)
{
    LOG4CPLUS_DEBUG(m_rootLogger,s.data());
}

void Logger::operator <<(const QString &s)
{
    LOG4CPLUS_DEBUG(m_rootLogger,s.toStdString().data());
}

void Logger::operator <<(const char *msg)
{
    LOG4CPLUS_DEBUG(m_rootLogger,msg);
}

void Logger::debug(const char *msg,...)
{
    LOG4CPLUS_DEBUG(m_rootLogger,msg);
}

string Logger::WString2String(const wstring &ws)
{
    std::string strLocale = setlocale(LC_ALL, "");
    const wchar_t* wchSrc = ws.c_str();
    size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
    char *chDest = new char[nDestSize];
    memset(chDest,0,nDestSize);
    wcstombs(chDest,wchSrc,nDestSize);
    std::string strResult = chDest;
    delete []chDest;
    setlocale(LC_ALL, strLocale.c_str());
    return strResult;
}

wstring Logger::String2WString(const string &s)
{
    std::string strLocale = setlocale(LC_ALL, "");
    const char* chSrc = s.c_str();
    size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
    wchar_t* wchDest = new wchar_t[nDestSize];
    wmemset(wchDest, 0, nDestSize);
    mbstowcs(wchDest,chSrc,nDestSize);
    std::wstring wstrResult = wchDest;
    delete []wchDest;
    setlocale(LC_ALL, strLocale.c_str());
    return wstrResult;
}


