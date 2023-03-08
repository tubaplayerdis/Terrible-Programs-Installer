#pragma once
#include <iterator>
#include <list>
#include <string>
namespace DebugTools {
	class Downloader
	{
	public:
		static void _Initilize();
		static std::list<std::wstring> Items;
		static std::wstring AssetLocation;
		static void GetHD2Assets();
		static void GetHD1Assets();
		static void GetSCTGAssets();
		static void GetPasswordCreatorAssets();

		//Asset Getting Async

		std::list<std::wstring> A_GetHD2Assets(std::wstring _assetloc);
		void A_GetHD1Assets();
		void A_GetSCTGAssets();
		void A_GetPasswordCreatorAssets();

		static void DeleteAssets(bool LogEvent);

	private:
		static void PrintList(std::list<std::wstring> const& list);
		static std::wstring CurrentWorkingDir();
		static std::wstring GetExeFileName();
	};
	
}


