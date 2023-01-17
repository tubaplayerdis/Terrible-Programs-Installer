#pragma once
#include <string>

namespace DebugTools {
	class Console
	{
	public: 
		static bool isConsoleActive();
		static void _initializeConsole();
		static void _log(std::wstring input);
		static void _log(std::wstring input, std::string func);
		static void _log(std::string input);		
		static void _log(std::string input, std::string func);
		static void _clear();
		static void _destroy();
	private:
		static void SetConsoleActivation(bool toggle);
		
	};
}


