// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "ScreenShotData.g.h"

namespace winrt::Terrible_Programs_Installer::implementation
{
    struct ScreenShotData : ScreenShotDataT<ScreenShotData>
    {
        ScreenShotData();

        winrt::hstring ImageSource();
        void ImageSource(winrt::hstring const& value);

    private:
        winrt::hstring m_ImageSource;
    };
}

namespace winrt::Terrible_Programs_Installer::factory_implementation
{
    struct ScreenShotData : ScreenShotDataT<ScreenShotData, implementation::ScreenShotData>
    {
    };
}
