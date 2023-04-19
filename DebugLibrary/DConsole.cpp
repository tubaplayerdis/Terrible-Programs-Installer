#include "pch.h"
#include "DConsole.hpp"
#include <windows.h>
#include <shellapi.h>
#include <fileapi.h>
#include <sstream>
#include <list>
#include "Downloader.hpp"
#include <Shlwapi.h>
#include <filesystem>
#include <direct.h>


FILE* fp = nullptr;//No initalizer will cause memory leak

//------------------------------------MAKE TOGGALABLE IN SETTINGS--------------------
bool _isConsoleActive = false;
bool _isConsoleCreation = false;
bool _isalsoconsole = true; //console + logging


DebugTools::Helpers::TPIFILE TPILOG = DebugTools::Helpers::TPIFILE();
HANDLE _TPIFILEHANDLE = nullptr;

bool DebugTools::Console::isConsoleCreation()
{
    return _isConsoleCreation;
}

bool DebugTools::Console::isConsoleActive()
{
    return _isConsoleActive;
}

void DebugTools::Console::_initializeConsole()
{
    if (!isConsoleCreation()) {
        //Create log file and stream writer        
        TPILOG.WRITELINE("No console activation set, creating log...\n");
        if (!_isalsoconsole) return;
    }
    if (isConsoleActive()) {
        return;
    }
    AllocConsole();
    fp = nullptr;
    freopen_s(&fp, "CONIN$", "r", stdin); //more for stdin and out
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "a", stdin);
    SetConsoleActivation(true);
    std::cout << "Terrible Programs Installer version 0.10  -  Successfully created debug console\n\n\n";         
}

void DebugTools::Console::_log(std::wstring input)
{
    if (!isConsoleCreation()) {        
        TPILOG.WRITELINE(input.c_str());
        if(!_isalsoconsole) return;
    }
    if(isConsoleActive()) std::wcout << input + L"\n";
}

void DebugTools::Console::_log(std::wstring input, std::string func)
{
    if (!isConsoleCreation()) {        
        TPILOG.WRITELINE(input.c_str(), func.c_str());
        if (!_isalsoconsole) return;
    }
    if (isConsoleActive()) std::wcout << func.c_str() << L"(): " << input + L"\n";
}

void DebugTools::Console::_log(std::string input)
{
    if (!isConsoleCreation()) {
        TPILOG.WRITELINE(input);
        if (!_isalsoconsole) return;
    }
    if (isConsoleActive()) std::cout << input + "\n";
}

void DebugTools::Console::_log(std::string input, std::string func)
{
    if (!isConsoleCreation()) {
        TPILOG.WRITELINE(input.c_str(), func.c_str());
        if (!_isalsoconsole) return;
    }
    if (isConsoleActive()) std::cout << func << "(): " << input + "\n";
}

void DebugTools::Console::_openlogfileinfs()
{
    TPILOG.OPENINFS();
}

void DebugTools::Console::_clear()
{
    std::cout.flush();
}

void DebugTools::Console::_dumperrorstoconsole()
{
    DebugTools::Console::_log("Current TPILOG: " + TPILOG._FILENAME);
    DebugTools::Console::_log(std::to_string(TPILOG.errorlist.size()), "ERROR COUNT");
    std::list<std::string> copyof = TPILOG.errorlist;
    TPILOG.errorlist.clear();
    int64_t x = 0;
    for (std::string var : copyof)
    {
        DebugTools::Console::_log(var, "ERROR " + std::to_string(x));
        x++;
    }
    
}

void DebugTools::Console::_destroy()
{
    if (!isConsoleActive()) {
        return;
    }
    FreeConsole();
    fclose(fp);
    SetConsoleActivation(false);
}

void DebugTools::Console::setConsoleCreationStatus(bool toggle)
{
    _isConsoleCreation = toggle;
}

void DebugTools::Console::SetConsoleActivation(bool toggle)
{
    _isConsoleActive = toggle;
}

DebugTools::Helpers::TPIFILE::TPIFILE()
{
    auto t = std::time(nullptr);
#pragma warning(suppress : 4996) 
    auto tm = *std::localtime(&t);   

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    std::string timestr = oss.str();


    CHAR buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string f = std::string(buffer);
    std::string runningdir = f.substr(0, f.find_last_of("\\/"));
    runningdir += "\\Logs";


    if (!std::filesystem::exists(runningdir)) {        
        std::string RD(runningdir.begin(), runningdir.end());
        if (_mkdir(RD.c_str()) == 0) {
            errorlist.push_back(GetLastErrorStdStr() + "IF \"The system cannot find file specified\", unless logging manfunction, normal activity");
        }
    }

    _FILENAME = runningdir + "\\TerribleProgramsInstaller" + timestr + ".log";
    _TPIFILEHANDLE = CreateFileA(_FILENAME.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);   

    if (_TPIFILEHANDLE == INVALID_HANDLE_VALUE)
    {
        errorlist.push_back("There was a Terminal Failure in which the log file could not be created");
        errorlist.push_back(GetLastErrorStdStr());
    }

}

void DebugTools::Helpers::TPIFILE::WRITELINE(std::string LINE)
{    
    DWORD dwBytesWritten = 0;
    std::string _LINE = LINE + "\n";
    if (!WriteFile(_TPIFILEHANDLE, _LINE.c_str(), strlen(_LINE.c_str()), &dwBytesWritten, NULL)) {
        errorlist.push_back(GetLastErrorStdStr());
    };
}

void DebugTools::Helpers::TPIFILE::WRITELINE(std::wstring LINE)
{    
    DWORD dwBytesWritten = 0;
    std::wstring _LINE = LINE + L"\n";
    if (!WriteFile(_TPIFILEHANDLE, ws2s(_LINE).c_str(), strlen(ws2s(_LINE).c_str()), &dwBytesWritten, NULL)) {
        errorlist.push_back(GetLastErrorStdStr());
    };
}

void DebugTools::Helpers::TPIFILE::WRITELINE(std::string LINE, std::string FUNC)
{    
    DWORD dwBytesWritten = 0;
    std::string _LINE = FUNC + "(): " + LINE + "\n";
    if (!WriteFile(_TPIFILEHANDLE, _LINE.c_str(), strlen(_LINE.c_str()), &dwBytesWritten, NULL)) {
        errorlist.push_back(GetLastErrorStdStr());
    };
}

void DebugTools::Helpers::TPIFILE::WRITELINE(std::wstring LINE, std::string FUNC)
{   
    DWORD dwBytesWritten = 0;
    std::wstring _LINE = s2ws(FUNC) + L"(): " + LINE + L"\n";
    if (!WriteFile(_TPIFILEHANDLE, ws2s(_LINE).c_str(), strlen(ws2s(_LINE).c_str()), &dwBytesWritten, NULL)) {
        errorlist.push_back(GetLastErrorStdStr());
    };
}

void DebugTools::Helpers::TPIFILE::OPENINFS()
{
    ShellExecuteA(NULL, "open", _FILENAME.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}

void DebugTools::Helpers::TPIFILE::CLOSEFILE()
{
    CloseHandle(_TPIFILEHANDLE);
}

std::string DebugTools::Helpers::TPIFILE::GetLastErrorStdStr()
{

#pragma region GetlastError1
    /*
    DWORD error = GetLastError();
    if (error)
    {
        LPVOID lpMsgBuf;
        DWORD bufLen = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0, NULL);
        if (bufLen)
        {
            LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
            std::string result(lpMsgStr, lpMsgStr + bufLen);

            LocalFree(lpMsgBuf);

            return result;
        }
    }
    return std::string();
    */
#pragma endregion

#pragma region OtherRegion
    DWORD errorMessageID = GetLastError();

    if (errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
#pragma endregion

}

std::wstring DebugTools::Helpers::TPIFILE::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

std::string DebugTools::Helpers::TPIFILE::ws2s(const std::wstring& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
    char* buf = new char[len];
    WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
    std::string r(buf);
    delete[] buf;
    return r;
}


