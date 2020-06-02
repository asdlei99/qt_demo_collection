#ifndef SECRETPROCESS_H
#define SECRETPROCESS_H

#include <QObject>
#include <iostream>
#include <vector>
#include <windows.h>
#include <stdint.h>
#include <tlhelp32.h>
#include <stdio.h>

typedef struct EnumHWndsArg
{
    std::vector<HWND> *vecHWnds;
    DWORD dwProcessId;
}EnumHWndsArg, *LPEnumHWndsArg;

class secretprocess : public QObject
{
    Q_OBJECT
public:
    explicit secretprocess(QObject *parent = 0);
    DWORD GetProcessIDByName(const WCHAR* pName);
    void GetHWndsByProcessID(DWORD processID, std::vector<HWND> &vecHWnds);
    static  void doSecretPrpcess(HWND ghwnd);
private:
    HANDLE GetProcessHandleByID(int nID);//通过进程ID获取进程句柄
    DWORD m_hThisID;
signals:
    
public slots:

};

#endif // SECRETPROCESS_H
