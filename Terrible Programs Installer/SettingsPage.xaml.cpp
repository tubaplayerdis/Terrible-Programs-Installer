// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "SettingsPage.xaml.h"
#include <windows.h>
#include "DConsole.hpp"
#include <SettingsClass.h>
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


void winrt::Terrible_Programs_Installer::implementation::SettingsPage::Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    DebugTools::SettingsClass::UIdebugenabled = (int)e.NewValue();
}
