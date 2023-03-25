#pragma once
#include <iterator>
#include <list>
#include <string>
namespace DebugTools {

	enum DirReturns
	{
		DirectoryExists = 0,
		DirectoryCreated = 1,
		DirectoryFailedCreation = 2
	};

	class TPIAsset
	{
	public:
		TPIAsset(std::wstring DownloadSource, std::wstring ItemName);
		void DownloadAsset(std::list<std::wstring>& ListToAddTo, std::wstring AssetDirecotry);
		bool Verify();
		std::wstring _DownloadSource;
		std::wstring _ItemName;
	private:
		std::wstring _SavedDir;
	};	

	class Downloader
	{
	public:
		static void _Initilize();		
		static std::list<std::wstring> HD2Items;
		static std::list<std::wstring> HD1Items;
		static std::wstring AssetLocation;
		static std::wstring RunningDirectory;
		static bool _VerifyHD2Cache();
		static bool _VerifyHD1Cache();

		static DirReturns CheckAndCreateDir();

		//Asset Getting Async

		std::list<std::wstring> A_GetHD2Assets();
		std::list<std::wstring> A_GetHD1Assets();
		void A_GetSCTGAssets();
		void A_GetPasswordCreatorAssets();

		static void DeleteAssets(bool LogEvent);

		static void PrintList(std::list<std::wstring> const& list, std::wstring listname);
	private:
		static std::list<TPIAsset> HD2Downloads;
		static std::list<TPIAsset> HD1Downloads;
		//static void PrintList(std::list<std::wstring> const& list);
		static std::wstring CurrentWorkingDir();
		static std::wstring GetExeFileName();
	};
	
}


