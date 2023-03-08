#include "pch.h"
#include "Downloader.hpp"
#include "DConsole.hpp"
#include <windows.h>
#include <filesystem>
#include <string>
#include <Urlmon.h>
#include <direct.h>
#include <iostream>
#pragma comment(lib, "urlmon.lib")

//Define objects as to not get a linker error
std::list<std::wstring> DebugTools::Downloader::Items;
std::wstring DebugTools::Downloader::AssetLocation;


void DebugTools::Downloader::_Initilize()
{
	//char result[MAX_PATH]; is old
	std::wstring RunningDir = DebugTools::Downloader::CurrentWorkingDir();
	DebugTools::Console::_log(L"Checking assets directory location existance", __FUNCTION__);
	if (!std::filesystem::exists(RunningDir + L"\\WAssets")) {
		DebugTools::Console::_log(L"Directory does not exist, creating", __FUNCTION__);	
		std::string RD(RunningDir.begin(), RunningDir.end());
		RD += "WAssets";
		if (_mkdir(RD.c_str()) == 0) { DebugTools::Console::_log("Direcotory Created", __FUNCTION__); }
		else
		{
			DebugTools::Console::_log("Direcotory failed creation", __FUNCTION__);
		}
	}
	std::wstring Fixed = RunningDir + L"\\WAssets";
	//std::wstring ws(Fixed.begin(), Fixed.end());
	AssetLocation = Fixed;
	DebugTools::Console::_log(L"set assetloc var");
	DebugTools::Console::_log(L"Running Dir: " + RunningDir);
	DebugTools::Console::_log(L"Asset Loc: " + AssetLocation);
}

void DebugTools::Downloader::GetHD2Assets()
{
	DebugTools::Console::_log(L"Checking assets directory location existance", __FUNCTION__);
	if (!std::filesystem::exists(AssetLocation)) {
		DebugTools::Console::_log(L"Directory does not exist, creating", __FUNCTION__);
		std::string RD(AssetLocation.begin(), AssetLocation.end());		
		if (_mkdir(RD.c_str()) == 0) { DebugTools::Console::_log("Direcotory Created", __FUNCTION__); }
		else
		{
			DebugTools::Console::_log("Direcotory failed creation", __FUNCTION__);
		}
	}
	std::wstring dwnld_URL = L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/SplashScreen.scale-100.png";
	std::wstring savepath = AssetLocation + L"\\HD2100Scale.png";
	if (URLDownloadToFileW(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL) == S_OK) {
		Items.assign(1, L"HD2100Scale.png");
	}
	else
	{
		DebugTools::Console::_log("Failed to download item", __FUNCTION__);
	}
	
	DebugTools::Downloader::PrintList(Items);
}

void DebugTools::Downloader::GetHD1Assets()
{
}

void DebugTools::Downloader::GetSCTGAssets()
{
}

void DebugTools::Downloader::GetPasswordCreatorAssets()
{
}

void DebugTools::Downloader::DeleteAssets(bool LogEvent)
{
	if (!std::filesystem::exists(AssetLocation)) {
		if (LogEvent) { DebugTools::Console::_log(L"Directory does not exist, no need to delete", __FUNCTION__); }
		return;
	}
	for (const auto& entry : std::filesystem::directory_iterator(AssetLocation))
		std::filesystem::remove_all(entry.path());
}

void DebugTools::Downloader::PrintList(std::list<std::wstring> const& list)
{
	DebugTools::Console::_log(L"Printing Asset List:");
	for (auto const& i : list) {
		DebugTools::Console::_log(i);
	}
}

std::wstring DebugTools::Downloader::CurrentWorkingDir()
{
	std::wstring f = GetExeFileName();
	return f.substr(0, f.find_last_of(L"\\/"));
}

std::wstring DebugTools::Downloader::GetExeFileName()
{
	WCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::wstring(buffer);
}

//async stuff

void DebugTools::Downloader::A_GetHD1Assets() 
{
	
}

std::list<std::wstring> DebugTools::Downloader::A_GetHD2Assets(std::wstring _assetloc)
{
	DebugTools::Console::_log(L"Starting mission impossible", "HD2 Async func");
	std::list<std::wstring> _list;
	DebugTools::Console::_log(L"Checking assets directory location existance", "HD2 Async func");
	if (!std::filesystem::exists(_assetloc)) {
		DebugTools::Console::_log(L"Directory does not exist, creating", "HD2 Async func");
		std::string RD(_assetloc.begin(), _assetloc.end());
		if (_mkdir(RD.c_str()) == 0) { DebugTools::Console::_log("Direcotory Created", "HD2 Async func"); }
		else
		{
			DebugTools::Console::_log("Direcotory failed creation", "HD2 Async func");
		}
	}
	std::wstring dwnld_URL = L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/Nickocaodo.png";
	std::wstring savepath = _assetloc + L"\\HD2100Scale.png";
	if (URLDownloadToFileW(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL) == S_OK) {
		_list.assign(1, L"HD2100Scale.png");
	}
	else
	{
		DebugTools::Console::_log("Failed to download item", "HD2 Async func");
	}

	return _list;
}

void DebugTools::Downloader::A_GetSCTGAssets()
{

}

void DebugTools::Downloader::A_GetPasswordCreatorAssets()
{

}
