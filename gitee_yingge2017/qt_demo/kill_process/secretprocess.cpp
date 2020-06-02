#include "secretprocess.h"
#include <QDebug>

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
    EnumHWndsArg *pArg = (LPEnumHWndsArg)lParam;
    DWORD  processId;
    GetWindowThreadProcessId(hwnd, &processId);
    if (processId == pArg->dwProcessId)
    {
        pArg->vecHWnds->push_back(hwnd);
    }
    return TRUE;
}

secretprocess::secretprocess(QObject *parent) :
    QObject(parent)
{
    m_hThisID= GetCurrentProcessId();//当前进程id
}

HANDLE secretprocess::GetProcessHandleByID(int nID)//通过进程ID获取进程句柄
{
    return OpenProcess(PROCESS_ALL_ACCESS, FALSE, nID);
}

DWORD secretprocess::GetProcessIDByName(const WCHAR* pName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return NULL;
    }
    PROCESSENTRY32 pe = { sizeof(pe) };
    for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe))
    {
        if ((wcscmp(pe.szExeFile, pName) == 0)&&(pe.th32ProcessID!=m_hThisID))
        {
            CloseHandle(hSnapshot);
            return pe.th32ProcessID;
        }
      //  printf("%-6d %s\n", pe.th32ProcessID, pe.szExeFile);
    }
    CloseHandle(hSnapshot);
    return 0;
}

void secretprocess::GetHWndsByProcessID(DWORD processID, std::vector<HWND> &vecHWnds)
{
    EnumHWndsArg wi;
    wi.dwProcessId = processID;
    wi.vecHWnds = &vecHWnds;
    EnumWindows(lpEnumFunc, (LPARAM)&wi);
}

void secretprocess::doSecretPrpcess(HWND ghwnd)
{
    secretprocess  spObj;

    DWORD pid = spObj.GetProcessIDByName(L"RockerControl.exe");

    if (pid != 0)
    {
//        qDebug()<<"kill pid=%d"<<pid<<endl;
        QString  qscmd;
        qscmd.sprintf("taskkill -f -pid %d",pid);
//        system(qPrintable(qscmd));
        system(qscmd.toStdString().data());
    }
}
