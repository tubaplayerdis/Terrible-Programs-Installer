#include "pch.h"
#include "SettingsClass.hpp"
#include "DConsole.hpp"
#include <string>
#include <pugixml.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>


int DebugTools::SettingsClass::UIdebugenabled = 0;
std::string DebugTools::SettingsClass::installslocation = "C:/TPI/apps/";
int DebugTools::SettingsClass::downloadspeedlimit = -1;

namespace fs = std::filesystem;

void DebugTools::SettingsClass::ToggleConsole()
{
	
	if (DebugTools::Console::isConsoleActive) {
		DebugTools::Console::_initializeConsole();
	}
	else
	{
		DebugTools::Console::_destroy();
	}
	
}

void DebugTools::SettingsClass::SetDefualts()
{
	
	DebugTools::SettingsClass::installslocation = "C:/TPI/apps/";
	DebugTools::SettingsClass::downloadspeedlimit = -1;
	DebugTools::SettingsClass::ToggleConsole(false);
	DebugTools::SettingsClass::UIdebugenabled = 0;
	
}

void DebugTools::SettingsClass::LoadSettings()
{
	DebugTools::Console::_log("Loading settings into memory");
	if (!fs::exists("settings.xml")) {
		DebugTools::Console::_log("Settings file not found, creating file", __FUNCTION__);
		DebugTools::SettingsClass::CreateNewFile();		
	}
	//Document memory	
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("settings.xml");
	DebugTools::Console::_log("Settings file load results:");
	DebugTools::Console::_log(result.description());
	//Checking if the settings exist
	if (!doc.child("Settings")) {
		DebugTools::Console::_log("Settings file corrupted, creating new file", __FUNCTION__);
		DebugTools::SettingsClass::CreateNewFile();
		doc.load_file("settings.xml");		
	} 
	if (!doc.child("Settings").attribute("InstallationsPath")) {
		DebugTools::Console::_log("Settings file corrupted, creating new file", __FUNCTION__);
		DebugTools::SettingsClass::CreateNewFile();
		doc.load_file("settings.xml");		
	}
	if (!doc.child("Settings").attribute("DownloadSpeedLimit")) {
		DebugTools::Console::_log("Settings file corrupted, creating new file", __FUNCTION__);
		DebugTools::SettingsClass::CreateNewFile();
		doc.load_file("settings.xml");		
	}
	if (!doc.child("Settings").attribute("UiDebugEnabled")) {
		DebugTools::Console::_log("Settings file corrupted, creating new file", __FUNCTION__);
		DebugTools::SettingsClass::CreateNewFile();
		doc.load_file("settings.xml");		
	}

	DebugTools::SettingsClass::installslocation = doc.child("Settings").attribute("InstallationsPath").value();
	DebugTools::SettingsClass::downloadspeedlimit = atoi(doc.child("Settings").attribute("DownloadSpeedLimit").value());

	//Use atoi for conversion to int

#if _DEBUG
	std::cout << "DSL source: " << doc.child("Settings").attribute("DownloadSpeedLimit").value() << "\n";
	std::cout << "DSL atoi pointer conversion: " << atoi(doc.child("Settings").attribute("DownloadSpeedLimit").value()) << "\n";
#endif // _DEBUG

	DebugTools::SettingsClass::UIdebugenabled = atoi(doc.child("Settings").attribute("UiDebugEnabled").value());

	DebugTools::Console::_log("Loaded settings successfully");

}

void DebugTools::SettingsClass::CreateNewFile()
{	
	//Check if file exisits and if it does not create it
	if (!fs::exists("settings.xml")) {
		DebugTools::Console::_log("Settings file not found, creating file", __FUNCTION__);
		std::ofstream SettingsFile("settings.xml");
		SettingsFile.close();
	}

	

	// Generate new XML document within memory
	pugi::xml_document doc;

	// Generate XML declaration
	auto declarationNode = doc.append_child(pugi::node_declaration);
	declarationNode.append_attribute("version") = "1.0";
	declarationNode.append_attribute("encoding") = "ISO-8859-1";
	declarationNode.append_attribute("standalone") = "yes";

	//CreateDocument
	auto root = doc.append_child("Settings");
	doc.child("Settings").append_attribute("InstallationsPath").set_value("C:/TPI/apps/");
	doc.child("Settings").append_attribute("DownloadSpeedLimit").set_value(-1);
	doc.child("Settings").append_attribute("UiDebugEnabled").set_value(0);


	bool saveSucceeded = doc.save_file("settings.xml");
	if (saveSucceeded == false) {
		DebugTools::Console::_log("\n---------------------------------------\nFailed to create application settings!!!\n---------------------------------------\n");
	}
	else
	{
		DebugTools::Console::_log("successfully created and saved application settings");
	}
}

void DebugTools::SettingsClass::SaveSettings()
{	
	if (!fs::exists("settings.xml")) {
		DebugTools::Console::_log("Settings file not found, creating file", __FUNCTION__);
		std::ofstream SettingsFile("Settings.xml");
		SettingsFile.close();
	}
	// Generate new XML document within memory
	pugi::xml_document doc;

	// Generate XML declaration
	auto declarationNode = doc.append_child(pugi::node_declaration);
	declarationNode.append_attribute("version") = "1.0";
	declarationNode.append_attribute("encoding") = "ISO-8859-1";
	declarationNode.append_attribute("standalone") = "yes";

	//CreateDocument
	auto root = doc.append_child("Settings");
	doc.child("Settings").append_attribute("InstallationsPath").set_value(DebugTools::SettingsClass::installslocation.c_str());
	doc.child("Settings").append_attribute("DownloadSpeedLimit").set_value(DebugTools::SettingsClass::downloadspeedlimit);
	doc.child("Settings").append_attribute("UiDebugEnabled").set_value(DebugTools::SettingsClass::UIdebugenabled);


	bool saveSucceeded = doc.save_file("settings.xml");
	if (saveSucceeded == false) {
		DebugTools::Console::_log("\n---------------------------------------\nFailed to save application settings!!!\n---------------------------------------\n");
	}
	else
	{
		DebugTools::Console::_log("successfully saved application settings");
	}
}

void DebugTools::SettingsClass::ToggleConsole(bool input)
{
	if (input) {
		DebugTools::Console::_initializeConsole();
	}
	else
	{
		DebugTools::Console::_destroy();
	}
}
