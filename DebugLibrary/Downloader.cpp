#include "pch.h"
#include "Downloader.hpp"
#include "DConsole.hpp"
#include <windows.h>
#include <filesystem>
#include <string>
#include <Urlmon.h>
#include <direct.h>
#include <iostream>
#include <hstring.h>
#pragma comment(lib, "urlmon.lib")

//Define objects as to not get a linker error
std::list<std::wstring> DebugTools::Downloader::HD2Items;
std::list<std::wstring> DebugTools::Downloader::HD1Items;
std::wstring DebugTools::Downloader::AssetLocation;
std::wstring DebugTools::Downloader::RunningDirectory;

std::list<DebugTools::TPIAsset> DebugTools::Downloader::HD2Downloads = std::list<DebugTools::TPIAsset>{
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/descriptions/HD2DESC.txt", L"HD2DESC.txt"),//First one has to be description
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image0.png", L"HD2A.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image1.png", L"HD2B.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image2.png", L"HD2C.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD2/image3.png", L"HD2D.png")		
};

std::list<DebugTools::TPIAsset> DebugTools::Downloader::HD1Downloads = std::list<DebugTools::TPIAsset>{
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/descriptions/HD1DESC.txt", L"HD1DESC.txt"),//First one has to be description
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD1/image1.png", L"HD1A.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD1/image2.png", L"HD1B.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD1/image3.png", L"HD1C.png"),
		DebugTools::TPIAsset(L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/HD1/image4.png", L"HD1D.png")
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
		DebugTools::Console::_log(L"Verified: " + _TPIAsset._ItemName, __FUNCTION__);
	}	
	//only happens if all checks are passed
	return true;

}

bool DebugTools::Downloader::_VerifyHD1Cache()
{
	std::wstring AssetCheck = AssetLocation + L"\\";

	//self explanatory
	if (!std::filesystem::exists(AssetLocation)) return false;

	for (TPIAsset _TPIAsset : HD1Downloads)
	{
		if (!std::filesystem::exists(AssetCheck + _TPIAsset._ItemName)) return false;
		HD1Items.push_back(_TPIAsset._ItemName);
		DebugTools::Console::_log(L"Verified: " + _TPIAsset._ItemName, __FUNCTION__);
	}
	//only happens if all checks are passed
	return true;
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

void DebugTools::Downloader::PrintList(std::list<std::wstring> const& list, std::wstring listname)
{
	DebugTools::Console::_log(L"Printing " + listname + L"list:", __FUNCTION__);
	for (auto const& i : list) {
		DebugTools::Console::_log(i);
	}
}

DebugTools::DirReturns DebugTools::Downloader::CheckAndCreateDir()
{	
	std::wstring _assetloc = AssetLocation;
	DebugTools::Console::_log(L"Checking assets directory location existance", __FUNCTION__);
	if (!std::filesystem::exists(_assetloc)) {
		DebugTools::Console::_log(L"Directory does not exist, creating", __FUNCTION__);
		std::string RD(_assetloc.begin(), _assetloc.end());
		if (_mkdir(RD.c_str()) == 0) { DebugTools::Console::_log("Direcotory Created", __FUNCTION__); return DirectoryCreated; }
		else
		{
			DebugTools::Console::_log("Directory failed creation", __FUNCTION__);
			return DirectoryFailedCreation;
		}
	}
	DebugTools::Console::_log(L"Directory already existed", __FUNCTION__);
	return DirectoryExists;
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

std::list<std::wstring> DebugTools::Downloader::A_GetHD1Assets(/*DebugTools::Helpers::InfoBarUpdater better*/)
{
	double progress = 0;
	//better.set(progress);
	switch (CheckAndCreateDir())
	{
	case 0:
		DebugTools::Console::_log(L"Directory Existed", __FUNCTION__);
		break;
	case 1:
		DebugTools::Console::_log(L"Directory Was Created", __FUNCTION__);
		break;
	case 2:
		DebugTools::Console::_log(L"Directory Fialed Creation", __FUNCTION__);
		break;
	default:
		DebugTools::Console::_log(L"Defaulted On Check and Create Dir", __FUNCTION__);
		break;
	}
	progress = 10;
	//better.set(progress);
	std::list<std::wstring> _list;
	for (TPIAsset _TPIAsset : HD1Downloads) {
		DebugTools::Console::_log(L"Attempt download of asset:" + _TPIAsset._ItemName, __FUNCTION__);
		_TPIAsset.DownloadAsset(_list, AssetLocation);
		progress += 22.5;
		//better.set(progress);
	}

	DebugTools::Downloader::PrintList(_list, L"HD1Downloads");
	return _list;
}

std::list<std::wstring> DebugTools::Downloader::A_GetHD2Assets(/*DebugTools::Helpers::InfoBarUpdater better*/)
{
	double progress = 0;
	//better.set(progress);
	switch (CheckAndCreateDir())
	{
	case 0:
		DebugTools::Console::_log(L"Directory Existed", __FUNCTION__);
		break;
	case 1:
		DebugTools::Console::_log(L"Directory Was Created", __FUNCTION__);
		break;		
	case 2:
		DebugTools::Console::_log(L"Directory Fialed Creation", __FUNCTION__);
		break;
	default:
		DebugTools::Console::_log(L"Defaulted On Check and Create Dir", __FUNCTION__);
		break;
	}
	progress = 10;
	//better.set(progress);

	std::list<std::wstring> _list;	
	for (TPIAsset _TPIAsset : HD2Downloads) {
		DebugTools::Console::_log(L"Attempt download of asset:" + _TPIAsset._ItemName, __FUNCTION__);
		_TPIAsset.DownloadAsset(_list, AssetLocation);
		progress += 22.5;
		//better.set(progress);
	}

	DebugTools::Downloader::PrintList(_list, L"HD2Downloads");
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
	Helpers::DownloaderCallback callback;
	std::wstring savepath = AssetDirecotry + L"\\" + _ItemName;
	DebugTools::Console::_log("Replacement Line");
	if (URLDownloadToFileW(NULL, _DownloadSource.c_str(), savepath.c_str(), 0, &callback) == S_OK) {
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


