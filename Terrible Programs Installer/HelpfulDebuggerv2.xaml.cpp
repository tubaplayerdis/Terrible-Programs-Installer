// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "HelpfulDebuggerv2.xaml.h"
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.ViewManagement.h>
#if __has_include("HelpfulDebuggerv2.g.cpp")
#include "HelpfulDebuggerv2.g.cpp"
#endif
#include <DConsole.hpp>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Terrible_Programs_Installer::implementation
{
    HelpfulDebuggerv2::HelpfulDebuggerv2()
    {
        InitializeComponent();
    }

    void HelpfulDebuggerv2::EnableUIDebug(int toggle)
    {
        Windows::UI::ViewManagement::UISettings uisettings;
        Media::SolidColorBrush transbrush = Microsoft::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Transparent());
        Media::SolidColorBrush redbrush = Microsoft::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red());
        Media::SolidColorBrush systemcolorbrush = Microsoft::UI::Xaml::Media::SolidColorBrush(uisettings.GetColorValue(Windows::UI::ViewManagement::UIColorType::Accent));
        switch (toggle)
        {
        case 0:
            ChangeDebugElementColors(transbrush);
            DebugTools::Console::_log(L"Disabled UI Debug");
            break;
        case 1:
            ChangeDebugElementColors(redbrush);
            DebugTools::Console::_log(L"Enabled UI Debug: Red");
            break;
        case 2:
            ChangeDebugElementColors(systemcolorbrush);
            DebugTools::Console::_log(L"Disabled UI Debug: System Accent Color");
            break;
       default:
            ChangeDebugElementColors(transbrush);
            DebugTools::Console::_log(L"Defaulted on disable UI Debug");
            break;
        }

       
        
    }   

    void HelpfulDebuggerv2::ChangeDebugElementColors(Microsoft::UI::Xaml::Media::SolidColorBrush color)
    {
        VerticalPaneBorder().BorderBrush(color);
        AppImageBorder().BorderBrush(color);
    }

    int32_t HelpfulDebuggerv2::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void HelpfulDebuggerv2::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void HelpfulDebuggerv2::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        //myButton().Content(box_value(L"Clicked"));
    }
   
    
}
