#include "pch.h"
#include "DConsole.hpp"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <shellapi.h>

FILE* fp = nullptr;//No initalizer will cause memory leak
bool _isConsoleActive = false;
bool _isConsoleCreation = false;
std::ofstream DebugTools::Console::TPILOG;

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
        TPILOG.open("tpi.log");
        TPILOG << "No console activation set, creating log...\n";
        return;
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
    std::cout << "Terrible Programs Installer version 0.01  -  Successfully created debug console\n\n\n";
    SetConsoleActivation(true);
}

void DebugTools::Console::_log(std::wstring input)
{
    if (!isConsoleCreation()) {
        TPILOG << input.c_str() << L"\n";
        return;
    }
    std::wcout << input + L"\n";
}

void DebugTools::Console::_log(std::wstring input, std::string func)
{
    if (!isConsoleCreation()) {
        TPILOG << func.c_str() <<L"():" << input.c_str() << L"\n";
        return;
    }
    std::wcout << func.c_str() << L"(): " << input + L"\n";
}

void DebugTools::Console::_log(std::string input)
{
    if (!isConsoleCreation()) {
        TPILOG << input << L"\n";
        return;
    }
    std::cout << input + "\n";
}

void DebugTools::Console::_log(std::string input, std::string func)
{
    if (!isConsoleCreation()) {
        TPILOG << func << "():" << input.c_str() << L"\n";
        return;
    }
    std::cout << func << "(): " << input + "\n";
}

void DebugTools::Console::_openlogfileinfs()
{
    ShellExecuteA(NULL, "open", "C:\\", NULL, NULL, SW_SHOWDEFAULT);
}

void DebugTools::Console::_clear()
{
    std::cout.flush();
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
