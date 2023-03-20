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
std::list<std::wstring> DebugTools::Downloader::HD2Items;
std::wstring DebugTools::Downloader::AssetLocation;
std::wstring DebugTools::Downloader::RunningDirectory;

std::list<DebugTools::TPIAsset> DebugTools::Downloader::HD2Downloads = std::list<DebugTools::TPIAsset>{
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/descriptions/HD2DESC.txt", L"HD2DESC.txt"),//First one has to be description
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image0.png", L"HD2A.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image1.png", L"HD2B.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image2.png", L"HD2C.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image3.png", L"HD2D.png")		
};


/*
Image server edit links
HD2A:  https://imgbox.com/upload/edit/784485321/pUsyeQesPEViGX6G

//Dont use its low quality were using github just rate limits so gotta find others

*/

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
	RunningDirectory = RunningDir;
	DebugTools::Console::_log(L"set assetloc var");
	DebugTools::Console::_log(L"Running Dir: " + RunningDir);
	DebugTools::Console::_log(L"Asset Loc: " + AssetLocation);
}

//Do not use this please it does not work ok?
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
	std::wstring dwnld_URL = L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image0.png";
	std::wstring savepath = AssetLocation + L"\\HD2A.png";
	if (URLDownloadToFileW(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL) == S_OK) {
		HD2Items.assign(1, L"HD2A.png");
	}
	else
	{
		DebugTools::Console::_log("Failed to download item", __FUNCTION__);
	}
	
	DebugTools::Downloader::PrintList(HD2Items);
}

bool DebugTools::Downloader::_VerifyHD2Cache()
{
	/*
	List of Images to veryify

	HD2DESC.txt
	HD2A.png
	HD2B.png
	
	*/
	
	std::wstring AssetCheck = AssetLocation + L"\\";

	//self explanatory
	if(!std::filesystem::exists(AssetLocation)) return false;

	for (TPIAsset _TPIAsset : HD2Downloads)
	{
		if (!std::filesystem::exists(AssetCheck + _TPIAsset._ItemName)) return false;
		HD2Items.push_back(_TPIAsset._ItemName);
		DebugTools::Console::_log(L"Verified: " + _TPIAsset._ItemName);
	}	
	//only happens if all checks are passed
	return true;

}

void DebugTools::Downloader::GetHD1Assets()
{
}

void DebugTools::Downloader::GetSCTGAssets()
{
}

void DebugTools::Downloader::DeleteAssets(bool LogEvent)
{
	if (!std::filesystem::exists(AssetLocation)) {
		if (LogEvent) { DebugTools::Console::_log(L"Directory does not exist, no need to delete assets", __FUNCTION__); }
		return;
	}
	for (const auto& entry : std::filesystem::directory_iterator(AssetLocation))
		std::filesystem::remove_all(entry.path());

	if (LogEvent) { DebugTools::Console::_log(L"Deleted Assets", __FUNCTION__); }
}

void DebugTools::Downloader::PrintList(std::list<std::wstring> const& list)
{
	DebugTools::Console::_log(L"Printing Asset List:", __FUNCTION__);
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


	//NOTE - I fixed it
	
	
	
	for (TPIAsset _TPIAsset : HD2Downloads) {
		DebugTools::Console::_log(L"Attempt download of asset:" + _TPIAsset._ItemName, __FUNCTION__);
		_TPIAsset.DownloadAsset(_list, AssetLocation);		
	}

	DebugTools::Downloader::PrintList(_list);
	return _list;
}

void DebugTools::Downloader::A_GetSCTGAssets()
{

}

void DebugTools::Downloader::A_GetPasswordCreatorAssets()
{

}

DebugTools::TPIAsset::TPIAsset(std::wstring DownloadSource, std::wstring ItemName)
{
	_DownloadSource = DownloadSource;
	_ItemName = ItemName;
}

void DebugTools::TPIAsset::DownloadAsset(std::list<std::wstring>& ListToAddTo, std::wstring AssetDirecotry)
{
	
	std::wstring savepath = AssetDirecotry + L"\\" + _ItemName;
	if (URLDownloadToFileW(NULL, _DownloadSource.c_str(), savepath.c_str(), 0, NULL) == S_OK) {
		ListToAddTo.push_back(_ItemName);
	}
	else
	{
		ListToAddTo.push_back(L"FAIL");
		DebugTools::Console::_log(L"Failed to download item:" + _ItemName, __FUNCTION__);
	}

}

bool DebugTools::TPIAsset::Verify()
{
	if (_SavedDir.empty()) return false;
	if (!std::filesystem::exists(_SavedDir + L"\\" + _ItemName)) return false;
	return true;
}
