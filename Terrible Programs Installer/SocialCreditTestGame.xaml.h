// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "SocialCreditTestGame.g.h"

namespace winrt::Terrible_Programs_Installer::implementation
{
    struct SocialCreditTestGame : SocialCreditTestGameT<SocialCreditTestGame>
    {
        SocialCreditTestGame();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        winrt::Microsoft::UI::Dispatching::DispatcherQueue DispatcherL = winrt::Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
        Windows::Foundation::IAsyncAction PopulateAssets();

        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Terrible_Programs_Installer::factory_implementation
{
    struct SocialCreditTestGame : SocialCreditTestGameT<SocialCreditTestGame, implementation::SocialCreditTestGame>
    {
    };
}
