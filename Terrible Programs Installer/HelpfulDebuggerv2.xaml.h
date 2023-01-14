// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "HelpfulDebuggerv2.g.h"
using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Terrible_Programs_Installer::implementation
{
    struct HelpfulDebuggerv2 : HelpfulDebuggerv2T<HelpfulDebuggerv2>
    {
        HelpfulDebuggerv2();

        void EnableUIDebug(int toggle);
        int32_t MyProperty();
        void MyProperty(int32_t value);
        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    private:
        void ChangeDebugElementColors(Microsoft::UI::Xaml::Media::SolidColorBrush color);
    };
}

namespace winrt::Terrible_Programs_Installer::factory_implementation
{
    struct HelpfulDebuggerv2 : HelpfulDebuggerv2T<HelpfulDebuggerv2, implementation::HelpfulDebuggerv2>
    {
    };
}
