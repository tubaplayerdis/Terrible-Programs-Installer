#include "pch.h"
#include "Startup.hpp"
#include "Downloader.hpp"
#include "DConsole.hpp"
#include <urlmon.h>
#include <filesystem>
#include <pugixml.hpp>
#include "boost/lexical_cast.hpp"

std::list<DebugTools::Helpers::StoreApplication> DebugTools::Startup::Applications = std::list<DebugTools::Helpers::StoreApplication>{};
bool DebugTools::Startup::UpdateAssets = true;

bool GetBoolFromValue(const pugi::char_t* value, bool todefault)
{
	if (value == "fasle") {
		return false;
	}
	else if (value == "true")
	{
		return true;
	}
	else
	{
		return todefault;
	}
}

void DebugTools::Startup::Init()
{
	bool abletoupdatestartup;
	//Download Startup.xml
	std::wstring savepath = DebugTools::Downloader::CurrentWorkingDir() + L"\\startup.xml";

	if (std::filesystem::exists(savepath)) {
		std::filesystem::remove(savepath);
		DebugTools::Console::_log("Startup.xml existed, so deleted");
	}//Delete if existing, no need to keep as internet is needed for application

	if (URLDownloadToFileW(NULL, L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/startup.xml", savepath.c_str(), 0, NULL) == S_OK) {
		DebugTools::Console::_log("Downloaded startup.xml");		
	} else
	{
		Applications.push_back(DebugTools::Helpers::StoreApplication::StoreApplication("null", false, "null", 0.0));
		return;
	}

	std::string startuppath = DebugTools::Helpers::StringConverions::toString(savepath);//well see if this needed

	//Document memory	
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(startuppath.c_str());
	DebugTools::Console::_log("Statup file load results:");
	DebugTools::Console::_log(result.description());

	if (!doc.child("TerribleProgramsInstaller")) {
		Applications.push_back(DebugTools::Helpers::StoreApplication::StoreApplication("null", false, "null", 0.0));
		return;
	}

	auto root = doc.child("TerribleProgramsInstaller");
	const pugi::char_t* tr = root.child("setting").child("UpdateAssets").value();
	if (tr == "fasle") {
		UpdateAssets = false;
	}
	else if(tr == "true")
	{
		UpdateAssets = true;
	}
	else
	{
		UpdateAssets = true;
	}
	DebugTools::Console::_log("Current Applications in startup: ");
	auto apps = root.child("Applications").children();
	for (pugi::xml_node var : apps)
	{
		DebugTools::Console::_log(var.name());		
		DebugTools::Helpers::StoreApplication temp = DebugTools::Helpers::StoreApplication(var.name(), GetBoolFromValue(var.child("available").value(), false), var.child("download").value(), boost::lexical_cast<double>(std::string(var.child("CurrentVerion").value()))); //long one liner //shutup compiler
		Applications.push_back(temp);		
	}
	DebugTools::Console::_log("Created Apps classes and added them to the list");
}

DebugTools::Helpers::StoreApplication::StoreApplication(std::string name, bool available, std::string download, double version)
{
	Name = name;
	Aviability = available;
	Download = download;
	Version = version;
}