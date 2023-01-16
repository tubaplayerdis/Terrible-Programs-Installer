#pragma once
#include <string>
#include <iostream>
#include <filesystem>
namespace DebugTools {
	class SettingsClass
	{
	public:
		//General
		static std::string installslocation;
		static int downloadspeedlimit;
		//Advanced	
		static void ToggleConsole();
		static int UIdebugenabled;
		//voids
		static void SetDefualts();
		static void LoadSettings();
		static void SaveSettings();

	private:
		static bool toggleconsole;
		static void ToggleConsole(bool input);
	};
}


