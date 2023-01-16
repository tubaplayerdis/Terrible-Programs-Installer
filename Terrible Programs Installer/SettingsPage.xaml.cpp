// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "SettingsPage.xaml.h"
#include <windows.h>
#include "DConsole.hpp"
#include <SettingsClass.hpp>
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
    }

    int32_t SettingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SettingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void SettingsPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        //myButton().Content(box_value(L"Clicked"));
    }
}


void winrt::Terrible_Programs_Installer::implementation::SettingsPage::Check_Connection_Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    int res = system("ping 140.82.112.3");
    if (res == 0) {
        DebugTools::Console::_log("Tested connection is active");
        Server_connect_stat_box().Text(L"Active");
    }
    else
    {
        DebugTools::Console::_log("Tested connection is active");
        Server_connect_stat_box().Text(L"Inactive");
    }
    
    
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
    std::cout << "TypeCast: " << (int)DebugTools::SettingsClass::downloadspeedlimit << "Real: " << DebugTools::SettingsClass::downloadspeedlimit;
#endif // _DEBUG

    //UiDebug
    UiDebugSlider().Value((int)DebugTools::SettingsClass::UIdebugenabled);
}


void winrt::Terrible_Programs_Installer::implementation::SettingsPage::Page_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    DebugTools::SettingsClass::SaveSettings();
}



