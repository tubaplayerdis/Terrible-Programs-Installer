// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "SettingsPage.xaml.h"
#include <windows.h>
#include "DConsole.hpp"
#include "Downloader.hpp"
#include <SettingsClass.hpp>
#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <AtlBase.h>
#include <atlconv.h>
#include <string>
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Terrible_Programs_Installer::implementation
{
    SettingsPage::SettingsPage()
    {
        InitializeComponent();
        UIDispatcher = winrt::Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
    }

    int32_t SettingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SettingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    Windows::Foundation::IAsyncAction SettingsPage::CheckInternetAsync()
    {
        co_await winrt::resume_background(); //Needed to start backround activities

        int res = system("ping 140.82.112.3");

        //Need to do the whole statement due to how c++ works when going into assembly
        UIDispatcher.TryEnqueue([this, res] {
            if (res == 0) {
                DebugTools::Console::_log("Tested connection is active");
                Server_connect_stat_box().Text(L"Active");
            }
            else
            {
                DebugTools::Console::_log("Tested connection is active");
                Server_connect_stat_box().Text(L"Inactive");
            }
            });

        
    }

    Windows::Foundation::IAsyncAction SettingsPage::CheckDotNetAsync()
    {
        co_await winrt::resume_background(); //Needed to start backround activities

        std::string res = exec("dotnet sdk check");

        //Need to do the whole statement due to how c++ works when going into assembly
        UIDispatcher.TryEnqueue([this, res] {
            DebugTools::Console::_log(res);
            
            if (res == "") {
                DebugTools::Console::_log("No .net");
                dotnetstatusbox().Text(L"No .Net detected!, please download and install before using applications");
            }

            if (res.find("Up to date.")) {
                DebugTools::Console::_log("Up to date .net detected");
                dotnetstatusbox().Text(L"Up to date .Net");
            }
            else
            {
                DebugTools::Console::_log(".net was not up to date but is installed");
                dotnetstatusbox().Text(L"non up to date .Net, applications might not work as expected");
            }
            CheckDotNet().IsEnabled(true);
            });            
    }

    std::string SettingsPage::exec(std::string command)
    {
        char buffer[128];
        std::string result = "";

        // Open pipe to file
        FILE* pipe = _popen(command.c_str(), "r");
        if (!pipe) {
            return "popen failed!";
        }

        // read till end of process:
        while (!feof(pipe)) {

            // use buffer to read and add to result
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }

        _pclose(pipe);
        return result;
    }

    void SettingsPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        //myButton().Content(box_value(L"Clicked"));
    }
}


void winrt::Terrible_Programs_Installer::implementation::SettingsPage::Check_Connection_Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Server_connect_stat_box().Text(L"Testing...");
    auto asycstarter{ CheckInternetAsync() };
}

//the saving system along with value change voids

//value change and then instant save
void winrt::Terrible_Programs_Installer::implementation::SettingsPage::Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    DebugTools::SettingsClass::UIdebugenabled = (int)e.NewValue();
    save();
}

void winrt::Terrible_Programs_Installer::implementation::SettingsPage::DownloadSpeedSlider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    DebugTools::SettingsClass::downloadspeedlimit = (int)e.NewValue();
    save();
}

void winrt::Terrible_Programs_Installer::implementation::SettingsPage::save()
{
    DebugTools::Console::_log("Saving settings from settings page", __FUNCTION__);
    DebugTools::SettingsClass::SaveSettings();
}


void winrt::Terrible_Programs_Installer::implementation::SettingsPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //load settings into program
    DebugTools::SettingsClass::LoadSettings();
    //Change Modifyers values

    //Conversion crap
    /*
    wstring w = L"some wstring";
    CW2A cw2a(w.c_str());
    string s = cw2a;
    */

    //Install location (conversions, ewwwwwww)
    CA2W ca2w(DebugTools::SettingsClass::installslocation.c_str());
    std::wstring w = ca2w;
    InstallsLocsBox().Text(w);

    //DownloadSpeedShit
    DownloadSpeedSlider().Value((int)DebugTools::SettingsClass::downloadspeedlimit);

#if _DEBUG
    std::cout << "TypeCast: " << (int)DebugTools::SettingsClass::downloadspeedlimit << "Real: " << DebugTools::SettingsClass::downloadspeedlimit << "\n";
#endif // _DEBUG

    //UiDebug
    UiDebugSlider().Value((int)DebugTools::SettingsClass::UIdebugenabled);
}


void winrt::Terrible_Programs_Installer::implementation::SettingsPage::Page_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    DebugTools::SettingsClass::SaveSettings();
}



void winrt::Terrible_Programs_Installer::implementation::SettingsPage::AppLBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    AppLBox().Text(GetAppConfig());
}

std::wstring winrt::Terrible_Programs_Installer::implementation::SettingsPage::GetAppConfig()
{
#if defined(_DEBUG)
#if defined(WIN32)
    return L"Debug - Win32";
#else
#error "Unknown configuration"
#endif
#elif defined(NDEBUG)
#if defined(WIN32)
    return L"Release - Win32";
#else
#error "Unknown configuration"
#endif
#else
#error "Unknown configuration"
#endif
}




void winrt::Terrible_Programs_Installer::implementation::SettingsPage::DeleteChache_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    DebugTools::Downloader::DeleteAssets(true);
}


void winrt::Terrible_Programs_Installer::implementation::SettingsPage::DumpErrors_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    DebugTools::Console::_log("Dumping Errors...");
    DebugTools::Console::_dumperrorstoconsole();
}


void winrt::Terrible_Programs_Installer::implementation::SettingsPage::CheckDotNet_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    CheckDotNet().IsEnabled(false);
    auto bruh{ CheckDotNetAsync() };
}
