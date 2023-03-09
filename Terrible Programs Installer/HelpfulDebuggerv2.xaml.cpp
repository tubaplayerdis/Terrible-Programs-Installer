// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "HelpfulDebuggerv2.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h> //Needed for bitmap image please dont remove, ill put it in pch
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.Foundation.h>//not needed since it is in the pch
#if __has_include("HelpfulDebuggerv2.g.cpp")
#include "HelpfulDebuggerv2.g.cpp"
#endif
#include <DConsole.hpp>
#include "SettingsClass.hpp"
#include "Downloader.hpp"
#include <ppltasks.h>
#include <windows.h>
#include <winuser.h>
#include <SensAPI.h>
#pragma comment(lib, "Sensapi.lib")

using namespace winrt;
using namespace Microsoft::UI::Xaml;



// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Terrible_Programs_Installer::implementation
{

    HelpfulDebuggerv2::HelpfulDebuggerv2()
    {
        //Download Assets
        // go to test func below







        InitializeComponent();


    }

    concurrency::task<std::list<std::wstring>> HelpfulDebuggerv2::TestFunc(std::wstring const& assetloc)
    {
        return concurrency::create_task([assetloc]
            {
                concurrency::task_completion_event<std::list<std::wstring>> stuff;
        DebugTools::Downloader downloader;
        std::list<std::wstring> list = downloader.A_GetHD2Assets(assetloc);
        std::list<std::wstring> returnlist;


        for (std::wstring item : list) {
            returnlist.push_back(item); //this caused it lol
        }
        
        /*
        Windows::System::DispatcherQueue disp = Windows::System::DispatcherQueue::GetForCurrentThread();
        bool blah = disp.TryEnqueue([] {
            
            

        });
        */
        return returnlist;

        });
    }


    winrt::hstring HelpfulDebuggerv2::ScreenShot1()
    {
        if (HelpfulDebuggerv2::CheckInternet() == -1) {
            return L"No_Image.jpg";
        }
        else
        {
            return L"https://github.com/tubaplayerdis/TPI-Assets/raw/main/SplashScreen.scale-100.png";
        }
    }

    void HelpfulDebuggerv2::ScreenShot1(winrt::hstring)
    {
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
            DebugTools::Console::_log(L"Enabled UI Debug: System Accent Color");
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

    int HelpfulDebuggerv2::CheckInternet()
    {
        DWORD dwSens;
        if (IsNetworkAlive(&dwSens) == FALSE)
        {
            DebugTools::Console::_log("No network connection", __FUNCTION__);
            return -1;
        }
        else
        {
            switch (dwSens)
            {
            case NETWORK_ALIVE_LAN:
                DebugTools::Console::_log("LAN connection available", __FUNCTION__);
                return 0;
                break;
            case NETWORK_ALIVE_WAN:
                DebugTools::Console::_log("WAN connection available", __FUNCTION__);
                return 1;
                break;
            default:
                DebugTools::Console::_log("Unknown connection available", __FUNCTION__);
                return 2;
                break;
            }
        }
    }
   
    
    

    
    

}


void winrt::Terrible_Programs_Installer::implementation::HelpfulDebuggerv2::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //Cache checks
    if (DebugTools::Downloader::_VerifyHD2Cache()) {
        //Image source 1
        Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
        std::wstring picstring = L"\\HD2A.png";
        Windows::Foundation::Uri uri{ DebugTools::Downloader::AssetLocation + picstring };
        bitmapImage.UriSource(uri);
        scren1().ImageSource(bitmapImage);
        //image source 2
        Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage1;
        std::wstring picstring1 = L"\\HD2B.png";
        Windows::Foundation::Uri uri1{ DebugTools::Downloader::AssetLocation + picstring1 };
        bitmapImage1.UriSource(uri1);
        scren2().ImageSource(bitmapImage1);
        //Image source 3

        //Image source 4

        //Image source 5

        //Image source 6
        return;
    }



    auto firstTitleOp{ TestFunc(DebugTools::Downloader::AssetLocation) };

    DebugTools::Console::_log("Holy shit guys 9000 ops on async operations, fuck microsoft frfr", __FUNCTION__);





    
    
    DebugTools::Console::_log("It inited", __FUNCTION__);

    try {
        std::list<std::wstring> stg = firstTitleOp.get();
        DebugTools::Downloader::PrintList(stg);
        int x = 0;
        for (std::wstring item : stg)
        {
            
            //DebugTools::Console::_log("Moment of truth...", __FUNCTION__);
            Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
            std::wstring picstring = L"\\" + item;
            Windows::Foundation::Uri uri{ DebugTools::Downloader::AssetLocation + picstring };
            Windows::Foundation::Uri urf{ DebugTools::Downloader::RunningDirectory + L"\\No_Image.jpg" };
            if (item == L"FAIL")
            {
                bitmapImage.UriSource(urf);
            }
            else
            {
                bitmapImage.UriSource(uri);
            }            
            DebugTools::Console::_log(L"Current Item: " + item);
            switch (x)
            {
            case 0:
                scren1().ImageSource(bitmapImage);
                break;

            case 1:
                scren2().ImageSource(bitmapImage);
                break;                
                //This was the old code:
                /*
                case 1:
                    break;
                    scren2().ImageSource(bitmapImage);
                                
                I can assure you I am NOT a retard
                */
                
                //Implement other numbers to other images
            default:
                break;
            }



            
            //Microsoft::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ L"WAssets/HD2100Scale.png" } }
            DebugTools::Console::_log("Loop: " + std::to_string(x) + "Done", __FUNCTION__);
            x++;
        }        
            DebugTools::Console::_log("I said, SUCK MY BALLS MR GARRISON", __FUNCTION__);        
    }
    catch (std::exception e) {
        MessageBoxA(NULL, e.what(), "Ive died be happy", MB_OK);
    }



    DebugTools::Console::_log("No more ft jerks jack", __FUNCTION__);
    
}
