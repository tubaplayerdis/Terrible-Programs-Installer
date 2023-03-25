// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "HelpfulDebuggerv1.g.h"

namespace winrt::Terrible_Programs_Installer::implementation
{
    struct HelpfulDebuggerv1 : HelpfulDebuggerv1T<HelpfulDebuggerv1>
    {
        HelpfulDebuggerv1();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        winrt::Microsoft::UI::Dispatching::DispatcherQueue DispatcherL = winrt::Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
        Windows::Foundation::IAsyncAction PopulateAssets();
        
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Terrible_Programs_Installer::factory_implementation
{
    struct HelpfulDebuggerv1 : HelpfulDebuggerv1T<HelpfulDebuggerv1, implementation::HelpfulDebuggerv1>
    {
    };
}
