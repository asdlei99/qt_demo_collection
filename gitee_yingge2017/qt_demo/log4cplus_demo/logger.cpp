#include "logger.h"
#include "log4cplus.h"
#include "configurator.h"

#include <string.h>
#include <iostream>

using namespace std;

logger::logger()
{
}

logger *logger::instance()
{
    static logger ins;
    return &ins;
}

bool logger::setInit(const string &s)
{
    if(s.empty()){
        cout<<"setInit failed,string is empty."<<endl;;
        return false;
    }

    log4cplus::PropertyConfigurator::doConfigure(String2WString(s));

    m_rootLogger = log4cplus::Logger::getRoot();

    return true;
}

void logger::operator<<(const string &str)
{
    LOG4CPLUS_DEBUG(m_rootLogger,str.data());
}

void logger::operator <<(const int num)
{
    LOG4CPLUS_DEBUG(m_rootLogger,std::to_string(num).data());
}

string logger::WString2String(const wstring &ws)
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

wstring logger::String2WString(const string &s)
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


