#include <QCoreApplication>
//remove UNICODE define
#include <QDir>

#ifdef Q_OS_WIN
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>


/*!

\brief Check if a process is running
\param [in] processName Name of process to check if is running
\returns \c True if the process is running, or \c False if the process is not running
*/
bool IsProcessRunning(const wchar_t *processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry))
        while (Process32Next(snapshot, &entry))
            if (!_wcsicmp(entry.szExeFile, processName))
                exists = true;

    CloseHandle(snapshot);
    return exists;
}


void waitForTerminate(){
    bool isrunning=true;
    bool firstcheck=true;
    while (isrunning) {
        isrunning=IsProcessRunning(L"AutomationStudio.exe");
        if(firstcheck){
            firstcheck=false;
            qDebug("Is running");
        }

    }

}


#endif


void waitForTerminate(){

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    waitForTerminate();

    qDebug("App install finished");
    a.exit(0);
}
