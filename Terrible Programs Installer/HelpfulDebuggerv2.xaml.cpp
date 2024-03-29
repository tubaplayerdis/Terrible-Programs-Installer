// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <windows.h>
#include "HelpfulDebuggerv2.xaml.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h> //Needed for bitmap image please dont remove, ill put it in pch
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Windows.Foundation.h>//not needed since it is in the pch
#if __has_include("HelpfulDebuggerv2.g.cpp")
#include "HelpfulDebuggerv2.g.cpp"
#endif
#include <DConsole.hpp>
#include "SettingsClass.hpp"
#include "Downloader.hpp"
#include <ppltasks.h>
#include <winuser.h>
#include <fstream>
#include "ProgramInfo.h"
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
        DispatcherL = winrt::Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();

    }

    
    //FUNCTION IS NOT BEING USED
    concurrency::task<void> HelpfulDebuggerv2::TestFunc(std::wstring const& assetloc)
    {       
        /*
        return concurrency::create_task([assetloc]
            {
                concurrency::task_completion_event<void> stuff;
        DebugTools::Downloader downloader;
        std::list<std::wstring> list = downloader.A_GetHD2Assets();
        std::list<std::wstring> returnlist;


        for (std::wstring item : list) {
            returnlist.push_back(item); //this caused it lol
        }
        
        Windows::System::DispatcherQueue disp = Windows::System::DispatcherQueue::GetForCurrentThread();
        bool blah = disp.TryEnqueue([shit, returnlist] {

            SetAssetData(returnlist);

            });
        
        
        return;

        });
        */
        return concurrency::create_task([assetloc]
            {


            });
    }
    

    Windows::Foundation::IAsyncAction HelpfulDebuggerv2::EarlyInTheMornin(std::wstring const& assetloc)
    {
        //Read this on the co_await etc: https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/concurrency-2
        //winrt::apartment_context ui_thread;

        

        co_await winrt::resume_background(); //Needed to start backround activities

        DispatcherL.TryEnqueue([this] {

            InfoBarBeaner().IsOpen(true);

        });
        
        //DebugTools::Helpers::InfoBarUpdater yupers = DebugTools::Helpers::InfoBarUpdater(DispatcherL, InfoBarBeaner(), L"Loading store assets - ");
        

#pragma region Downloader
        DebugTools::Downloader downloader;
        std::list<std::wstring> list = downloader.A_GetHD2Assets();
        std::list<std::wstring> returnlist;


        for (std::wstring item : list) {
            returnlist.push_back(item); //this caused it lol
        }
#pragma endregion

#pragma region AssetStuff
        DebugTools::Console::_log("Assetr stuff", __FUNCTION__);

        /* HAVE TO FACT CHECK THIS SHIT
        No, this is a difference between Desktop and UWP. In Desktop apps, CoreDispatcher doesn't work,
        because there is no CoreWindow that owns the message pump. Instead, you need to use the DependencyObject.DispatcherQueue property. In fact,
        DependencyObject.DispatcherQueue will work in both UWP and Desktop, so it's recommended to always use that if you can                
        */




        std::list<std::wstring> stg = returnlist;
        DebugTools::Downloader::PrintList(stg, L"HD2 Downloaded");
        int x = 0;
        for (std::wstring item : stg)
        {
            if (x == 0) {
                if (item == L"FAIL") {/*Implementation of defualt item text*/ x++; continue; }
                std::wstring text;
                std::string line;
                DebugTools::Console::_log("Kinda hot ngl", __FUNCTION__);
                std::ifstream descfile(DebugTools::Downloader::AssetLocation + L"\\HD2DESC.txt");
                if (descfile.is_open()) {
                    while (std::getline(descfile, line))
                    {
                        text.append(std::wstring(line.begin(), line.end()));
                    }
                    DebugTools::Console::_log("Even hotter", __FUNCTION__);  
                    
                    DispatcherL.TryEnqueue([this, text] {

                        App_Desc().Text(text);

                    });
                    
                    DebugTools::Console::_log("No way", __FUNCTION__);
                }
                //Implementation of desc setting here

                x++;
                continue;
            }
            DebugTools::Console::_log("Moment of truth...", __FUNCTION__);

            //Need to do the whole statement due to how c++ works when going into assembly
            DispatcherL.TryEnqueue([this, x, item] {

                Microsoft::UI::Xaml::Controls::Border theex = Microsoft::UI::Xaml::Controls::Border();
                theex.HorizontalAlignment(HorizontalAlignment::Center);
                theex.VerticalAlignment(VerticalAlignment::Bottom);
                theex.Width(650);
                theex.Height(350);
                theex.BorderThickness(ThicknessHelper::FromUniformLength(1));
                theex.CornerRadius(CornerRadiusHelper::FromRadii(10, 10, 10, 10));
                theex.Name(L"AppImageBorder" + std::to_wstring(x));


                

                Microsoft::UI::Xaml::Media::ImageBrush lol = Microsoft::UI::Xaml::Media::ImageBrush();
                lol.ImageSource(Microsoft::UI::Xaml::Media::Imaging::BitmapImage(Windows::Foundation::Uri{ DebugTools::Downloader::RunningDirectory + L"\\No_Image.jpg" }));//Default



                Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage;
                std::wstring picstring = L"\\" + item;
                Windows::Foundation::Uri uri{ DebugTools::Downloader::AssetLocation + picstring };
                Windows::Foundation::Uri urf{ DebugTools::Downloader::RunningDirectory + L"\\No_Image.jpg" };
                DebugTools::Console::_log("ARe wE ThERe YEt","UI Thread Lambda");
                if (item == L"FAIL")
                {
                    bitmapImage.UriSource(urf);
                }
                else
                {
                    bitmapImage.UriSource(uri);
                }
                lol.ImageSource(bitmapImage);

                theex.Background(lol);
                DebugTools::Console::_log(L"Current Item: " + item);

            
                

                Suckit().Children().Append(theex);

            });

            //Windows needs to fix thier shit

            

            //Microsoft::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ L"WAssets/HD2100Scale.png" } }
            DebugTools::Console::_log("Loop: " + std::to_string(x) + "Done", "UI Thread Lambda");
            x++;
        }

        //Close if not already
        DispatcherL.TryEnqueue([this] {

            InfoBarBeaner().IsOpen(false);

            });

        DebugTools::Console::_log("I said, SUCK MY BALLS MR GARRISON", __FUNCTION__);


        // We now close this thanggggggggggggggg
        //TheInfoBar().IsOpen(false);

        DebugTools::Console::_log("Animam studios is a go", __FUNCTION__);
#pragma endregion


        //co_await ui_thread;

        //SetAssetData(returnlist);

    }


    //Not being used
    void HelpfulDebuggerv2::SetAssetData(std::list<std::wstring> listarg)
    {
        
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

//THIS FUNCTION IS CALLED WHEN THE INFO BAR LOADS NOT THE PAGE
void winrt::Terrible_Programs_Installer::implementation::HelpfulDebuggerv2::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    
    //Cache checks
    if (DebugTools::Downloader::_VerifyHD2Cache()) {
        //Desc
        std::wstring text;
        std::string line;
        std::ifstream descfile(DebugTools::Downloader::AssetLocation + L"\\HD2DESC.txt");
        if (descfile.is_open()) {
            while (std::getline(descfile, line))
            {
                text.append(std::wstring(line.begin(), line.end()));
            }
            App_Desc().Text(text);
        }
        int x = 0;
        for (std::wstring item : DebugTools::Downloader::HD2Items)
        {
            if (x == 0) {
                x++;
                continue;
            }//So the first item is always the desc         
            Microsoft::UI::Xaml::Controls::Border theex = Microsoft::UI::Xaml::Controls::Border();
            theex.HorizontalAlignment(HorizontalAlignment::Center);
            theex.VerticalAlignment(VerticalAlignment::Bottom);
            theex.Width(650);
            theex.Height(350);
            theex.BorderThickness(ThicknessHelper::FromUniformLength(1));
            theex.CornerRadius(CornerRadiusHelper::FromRadii(10, 10, 10, 10));
            theex.Name(L"AppImageBorder" + std::to_wstring(x));




            Microsoft::UI::Xaml::Media::ImageBrush lol = Microsoft::UI::Xaml::Media::ImageBrush();
            std::wstring picstring = L"\\" + item;
            DebugTools::Console::_log(L"Current Item: " + DebugTools::Downloader::AssetLocation + picstring);
            Microsoft::UI::Xaml::Media::Imaging::BitmapImage lolyes = Microsoft::UI::Xaml::Media::Imaging::BitmapImage();
            Windows::Foundation::Uri temp{ DebugTools::Downloader::AssetLocation + picstring };
            
            lolyes.UriSource(temp);
            lol.ImageSource(lolyes);

            theex.Background(lol);
            //DebugTools::Console::_log(L"Current Item: " + item);




            Suckit().Children().Append(theex);
            x++;
        }
        return;
    }

        
        
    

    //The downloading thing yup
    //TheInfoBar().IsOpen(true);


    auto firstTitleOp{ EarlyInTheMornin(DebugTools::Downloader::AssetLocation) };

    DebugTools::Console::_log("Holy shit guys 9000 ops on async operations, fuck microsoft frfr", __FUNCTION__);





    
    
    
}


void winrt::Terrible_Programs_Installer::implementation::HelpfulDebuggerv2::Page_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
{
    //Not Nececarry, all i needed was an asterisk
    /*
    RECT rect;
    if (GetWindowRect(TPIExtra::ProgramInfo::_windowhwnd, &rect))
    {
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;
    }
    ColumnTwo().Width(8);
    */
}
