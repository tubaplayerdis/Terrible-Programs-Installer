#include "pch.h"
#include "DConsole.hpp"
#include <windows.h>
#include <iostream>

FILE* fp = nullptr;//No initalizer will cause memory leak
bool _isConsoleActive = false;

bool DebugTools::Console::isConsoleActive()
{
    return _isConsoleActive;
}

void DebugTools::Console::_initializeConsole()
{
    if (isConsoleActive()) {
        return;
    }
    AllocConsole();
    fp = nullptr;
    freopen_s(&fp, "CONIN$", "r", stdin); //more for stdin and out
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    std::cout << "Terrible Programs Installer version 0.01  -  Successfully created debug console\n\n\n";
    SetConsoleActivation(true);
}

void DebugTools::Console::_log(std::wstring input)
{
    std::wcout << input + L"\n";
}

void DebugTools::Console::_log(std::string input)
{
    std::cout << input + "\n";
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

void DebugTools::Console::SetConsoleActivation(bool toggle)
{
    _isConsoleActive = toggle;
}
