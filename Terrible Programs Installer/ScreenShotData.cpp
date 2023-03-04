// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ScreenShotData.h"
#if __has_include("ScreenShotData.g.cpp")
#include "ScreenShotData.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Terrible_Programs_Installer::implementation
{
    ScreenShotData::ScreenShotData()
    {
        DefaultStyleKey(winrt::box_value(L"Terrible_Programs_Installer.ScreenShotData"));
    }

    winrt::hstring ScreenShotData::ImageSource()
    {
        return m_ImageSource;
    }

    void ScreenShotData::ImageSource(winrt::hstring const& value)
    {
        if (m_ImageSource != value) {
            m_ImageSource = value;
        }
    }
}
