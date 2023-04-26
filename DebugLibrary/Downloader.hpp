#pragma once
#include <iterator>
#include <list>
#include <string>
#include <urlmon.h>    
#include <iostream>
#include "DConsole.hpp"
#include <hstring.h>



#pragma comment (lib, "urlmon.lib")

namespace DebugTools {

	namespace Helpers {				

		class DownloaderCallback : public IBindStatusCallback
		{
		public:
			DownloaderCallback() {}

			~DownloaderCallback() { }

			// This one is called by URLDownloadToFile
			STDMETHOD(OnProgress)(/* [in] */ ULONG ulProgress, /* [in] */ ULONG ulProgressMax, /* [in] */ ULONG ulStatusCode, /* [in] */ LPCWSTR wszStatusText)
			{
				DebugTools::Console::_log("\rDownloaded " + std::to_string(ulProgress) + " of " + std::to_string(ulProgressMax) + " byte(s), " + " Status Code = " + std::to_string(ulStatusCode));
				return S_OK;
			}

			// The rest  don't do anything...
			STDMETHOD(OnStartBinding)(/* [in] */ DWORD dwReserved, /* [in] */ IBinding __RPC_FAR* pib)
			{
				return E_NOTIMPL;
			}

			STDMETHOD(GetPriority)(/* [out] */ LONG __RPC_FAR* pnPriority)
			{
				return E_NOTIMPL;
			}

			STDMETHOD(OnLowResource)(/* [in] */ DWORD reserved)
			{
				return E_NOTIMPL;
			}

			STDMETHOD(OnStopBinding)(/* [in] */ HRESULT hresult, /* [unique][in] */ LPCWSTR szError)
			{
				return E_NOTIMPL;
			}

			STDMETHOD(GetBindInfo)(/* [out] */ DWORD __RPC_FAR* grfBINDF, /* [unique][out][in] */ BINDINFO __RPC_FAR* pbindinfo)
			{
				return E_NOTIMPL;
			}

			STDMETHOD(OnDataAvailable)(/* [in] */ DWORD grfBSCF, /* [in] */ DWORD dwSize, /* [in] */ FORMATETC __RPC_FAR* pformatetc, /* [in] */ STGMEDIUM __RPC_FAR* pstgmed)
			{
				return E_NOTIMPL;
			}

			STDMETHOD(OnObjectAvailable)(/* [in] */ REFIID riid, /* [iid_is][in] */ IUnknown __RPC_FAR* punk)
			{
				return E_NOTIMPL;
			}

			// IUnknown stuff
			STDMETHOD_(ULONG, AddRef)()
			{
				return 0;
			}

			STDMETHOD_(ULONG, Release)()
			{
				return 0;
			}

			STDMETHOD(QueryInterface)(/* [in] */ REFIID riid, /* [iid_is][out] */ void __RPC_FAR* __RPC_FAR* ppvObject)
			{
				return E_NOTIMPL;
			}
		};
	}

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

		std::list<std::wstring> A_GetHD2Assets(/*DebugTools::Helpers::InfoBarUpdater better*/);
		std::list<std::wstring> A_GetHD1Assets(/*DebugTools::Helpers::InfoBarUpdater better*/);
		void A_GetSCTGAssets();
		void A_GetPasswordCreatorAssets();

		static void DeleteAssets(bool LogEvent);

		static void PrintList(std::list<std::wstring> const& list, std::wstring listname);

		static std::wstring CurrentWorkingDir();
	private:
		static std::list<TPIAsset> HD2Downloads;
		static std::list<TPIAsset> HD1Downloads;
		//static void PrintList(std::list<std::wstring> const& list);		
		static std::wstring GetExeFileName();
	};
	
}


