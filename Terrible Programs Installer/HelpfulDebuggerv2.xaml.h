// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "HelpfulDebuggerv2.g.h"
#include <string>
#include <winnt.h>
#include <ppltasks.h>
#include <winrt/Windows.Foundation.h>
using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Terrible_Programs_Installer::implementation
{
    struct HelpfulDebuggerv2 : HelpfulDebuggerv2T<HelpfulDebuggerv2>
    {
        
        HelpfulDebuggerv2();
        
        winrt::hstring ScreenShot1();
        void ScreenShot1(winrt::hstring);

        concurrency::task<std::list<std::wstring>> TestFunc(std::wstring const& assetloc);
        
        
        void EnableUIDebug(int toggle);
        int32_t MyProperty();
        void MyProperty(int32_t value);
        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    private:
        void ChangeDebugElementColors(Microsoft::UI::Xaml::Media::SolidColorBrush color);
        int CheckInternet();
        winrt::hstring m_sc1 = L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/SplashScreen.scale-100.png";
        
    public:
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Page_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
    };

    

    
    
}

namespace winrt::Terrible_Programs_Installer::factory_implementation
{
    struct HelpfulDebuggerv2 : HelpfulDebuggerv2T<HelpfulDebuggerv2, implementation::HelpfulDebuggerv2>
    {
    };
}
