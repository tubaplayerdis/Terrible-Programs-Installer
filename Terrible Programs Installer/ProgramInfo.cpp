#include "pch.h"
#include "ProgramInfo.h"
#include <windows.h>
#include <iostream>

HWND TPIExtra::ProgramInfo::_windowhwnd;
int TPIExtra::ProgramInfo::_windowheight;
int TPIExtra::ProgramInfo::_windowwidth;

void TPIExtra::ProgramInfo::_printhandw()
{
#if _DEBUG
	std::cout << "Height:" << _windowheight << "\nWidth:" << _windowheight << "\n";
#endif // _DEBUG

}
