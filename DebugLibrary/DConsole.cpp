#include "pch.h"
#include "DConsole.hpp"
#include <windows.h>
#include <iostream>

FILE* fp = nullptr;//No initalizer will cause memory leak

void DebugTools::Console::_initializeConsole()
{
    AllocConsole();
    fp = nullptr;
    freopen_s(&fp, "CONIN$", "r", stdin); //more for stdin and out
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    std::cout << "Terrible Programs Installer version 0.01  -  Successfully created debug console\n\n\n";
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
    FreeConsole();
    fclose(fp);
}
