#pragma once
#include <iterator>
#include <list>
#include <string>
namespace DebugTools {

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
		static std::wstring AssetLocation;
		static std::wstring RunningDirectory;
		static bool _VerifyHD2Cache();

		//DO NOT USE(does not work) - USE ASYNC
		static void GetHD2Assets();
		//DO NOT USE(does not work) - USE ASYNC
		static void GetHD1Assets();
		//DO NOT USE(does not work) - USE ASYNC
		static void GetSCTGAssets();
		//DO NOT USE(does not work) - USE ASYNC
		static void GetPasswordCreatorAssets();

		//Asset Getting Async

		std::list<std::wstring> A_GetHD2Assets(std::wstring _assetloc);
		void A_GetHD1Assets();
		void A_GetSCTGAssets();
		void A_GetPasswordCreatorAssets();

		static void DeleteAssets(bool LogEvent);

		static void PrintList(std::list<std::wstring> const& list);
	private:
		static std::list<TPIAsset> HD2Downloads;
		//static void PrintList(std::list<std::wstring> const& list);
		static std::wstring CurrentWorkingDir();
		static std::wstring GetExeFileName();
	};
	
}


