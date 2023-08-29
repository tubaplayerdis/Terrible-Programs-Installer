// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "HelpfulDebuggerv1.xaml.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h> // for uri source
#include <fstream>
#if __has_include("HelpfulDebuggerv1.g.cpp")
#include "HelpfulDebuggerv1.g.cpp"
#endif
#include <Downloader.hpp>
#include <DConsole.hpp>
#include <Startup.hpp>
#include <AppDownloader.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Terrible_Programs_Installer::implementation
{
    HelpfulDebuggerv1::HelpfulDebuggerv1()
    {
        InitializeComponent();
    }

    int32_t HelpfulDebuggerv1::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void HelpfulDebuggerv1::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
    
}


Windows::Foundation::IAsyncAction winrt::Terrible_Programs_Installer::implementation::HelpfulDebuggerv1::PopulateAssets()
{
    co_await winrt::resume_background(); //Needed to start backround activities

    DispatcherL.TryEnqueue([this] {

        InfoBarBeaner().IsOpen(true);

        });


    //DebugTools::Helpers::InfoBarUpdater yupers = DebugTools::Helpers::InfoBarUpdater(DispatcherL, InfoBarBeaner(), L"Loading store assets - ");

#pragma region Downloader
    DebugTools::Downloader downloader;
    std::list<std::wstring> list = downloader.A_GetHD1Assets();
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
    DebugTools::Downloader::PrintList(stg, L"HD1 Downloaded");
    int x = 0;
    for (std::wstring item : stg)
    {
        if (x == 0) {
            if (item == L"FAIL") {/*Implementation of defualt item text*/ x++; continue; }
            std::wstring text;
            std::string line;
            //DebugTools::Console::_log("Kinda hot ngl", __FUNCTION__);
            std::ifstream descfile(DebugTools::Downloader::AssetLocation + L"\\HD1DESC.txt");
            if (descfile.is_open()) {
                while (std::getline(descfile, line))
                {
                    text.append(std::wstring(line.begin(), line.end()));
                }
                //DebugTools::Console::_log("Even hotter", __FUNCTION__);

                DispatcherL.TryEnqueue([this, text] {

                    App_Desc().Text(text);

                    });

                //DebugTools::Console::_log("No way", __FUNCTION__);
            }
            //Implementation of desc setting here

            x++;
            continue;
        }
        //DebugTools::Console::_log("Moment of truth...", __FUNCTION__);

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
            //DebugTools::Console::_log("ARe wE ThERe YEt", "UI Thread Lambda");
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
}

void winrt::Terrible_Programs_Installer::implementation::HelpfulDebuggerv1::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //Cache checks
    if (DebugTools::Downloader::_VerifyHD1Cache()) {
        //Desc
        std::wstring text;
        std::string line;
        std::ifstream descfile(DebugTools::Downloader::AssetLocation + L"\\HD1DESC.txt");
        if (descfile.is_open()) {
            while (std::getline(descfile, line))
            {
                text.append(std::wstring(line.begin(), line.end()));
            }
            App_Desc().Text(text);
        }
        int x = 0;
        for (std::wstring item : DebugTools::Downloader::HD1Items)
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


    auto firstTitleOp{ PopulateAssets() };

    //if(DebugTools::Startup::Applications)

    DebugTools::Console::_log("bro idk", __FUNCTION__);
}


void winrt::Terrible_Programs_Installer::implementation::HelpfulDebuggerv1::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    TPIApplication::AppDownloader::Download(1);
}
