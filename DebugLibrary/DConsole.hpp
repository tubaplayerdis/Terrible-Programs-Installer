#pragma once
#include <string>
#include <list>

namespace DebugTools {
	namespace Helpers {
		class TPIFILE {
		public:
			TPIFILE(); //Class constructor
			void WRITELINE(std::string LINE);
			void WRITELINE(std::wstring LINE);	
			void WRITELINE(std::string LINE, std::string FUNC);
			void WRITELINE(std::wstring LINE, std::string FUNC);
			void OPENINFS();
			void CLOSEFILE();
			std::list<std::string> errorlist;
			std::string _FILENAME;

		private:			
			std::string GetLastErrorStdStr();
			std::wstring s2ws(const std::string& s);
			std::string ws2s(const std::wstring& s);
			
		};

		class StringConverions {
		public:
			static std::string toString(const std::wstring& s);
			static std::wstring toWString(const std::string& s);
		};

	}

	class Console
	{
	public: 
		static bool isLoggingCreation();
		static bool isConsoleActive();
		static void _initializeConsole();
		static void _log(std::wstring input);
		static void _log(std::wstring input, std::string func);
		static void _log(std::string input);		
		static void _log(std::string input, std::string func);
		static void _dumperrorstoconsole();
		static void _openlogfileinfs();
		static void _clear();
		static void _destroy();			
		static bool _isLoggingCreation;
		static bool _isalsoconsole;
	private:
		static bool _isConsoleActive;
		static void setLoggingCreationStatus(bool toggle);
		static void SetConsoleActivation(bool toggle);
		
	};
}


