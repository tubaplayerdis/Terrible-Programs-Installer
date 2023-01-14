#pragma once
#include <string>

namespace DebugTools {
	class Console
	{
	public: 
		static void _initializeConsole();
		static void _log(std::wstring input);
		static void _log(std::string input);
		static void _clear();
		static void _destroy();
	};
}


