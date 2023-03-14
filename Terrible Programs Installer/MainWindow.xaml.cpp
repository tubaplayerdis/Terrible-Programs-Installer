// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#include <windows.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include "DConsole.hpp"
#include "SettingsClass.hpp"
#include "Downloader.hpp"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "ProgramInfo.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Terrible_Programs_Installer::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        initwindow();
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        
        MessageBoxA(nullptr, "Button Was clicked", "if this shows up lol!", MB_OK);
        
    }

    void MainWindow::initwindow()
    {
#pragma region ConsoleWork

#if _DEBUG
        DebugTools::Console::_initializeConsole();
#endif // DEBUG

        

#pragma endregion



        WindowHandle = FindWindowA(NULL, "WinUI Desktop");
        SetWindowTextA(WindowHandle, "Terrible Programs Installer");

#pragma region IconLoading
        HWND hwnd = WindowHandle;
        HANDLE hIcon = LoadImageA(0, "TPI.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
        if (hIcon) {
            //Change both icons to the same icon handle.
            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

            //This will ensure that the application icon gets changed too.
            SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        }
#pragma endregion

        //Set stuff lol
        TPIExtra::ProgramInfo::_windowhwnd = hwnd;
        RECT rect;
        int height;
        int width;
        if (GetWindowRect(hwnd, &rect))
        {
            width = rect.right - rect.left;
            height = rect.bottom - rect.top;
        }
        TPIExtra::ProgramInfo::_windowheight = height;
        TPIExtra::ProgramInfo::_windowwidth = width;
        TPIExtra::ProgramInfo::_printhandw();

        // Windows Debugger didnt like this part
        /*
        delete &height;
        delete &width;
        */

        //load in settings
        DebugTools::SettingsClass::LoadSettings();

        //Init In asset Downloader
        DebugTools::Downloader::_Initilize();


        TheInfoBar().Message(L"Welcome to TPI.");
        TheInfoBar().IsOpen(true);
    }

    

    
}


void winrt::Terrible_Programs_Installer::implementation::MainWindow::The_NavigationView_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args)
{
    TheInfoBar().Message(L"Loading page...");
    TheInfoBar().IsOpen(true); 
    TheInfoBar().UpdateLayout();
    //Saying visible when its not
    Microsoft::UI::Xaml::Visibility lol = TheInfoBar().Visibility();
    DebugTools::Console::_log(std::to_string((int)lol), "Visibility 1=no 0=yes");
    while(true) {
        if (lol == Microsoft::UI::Xaml::Visibility::Collapsed) {
            TheInfoBar().IsOpen(true);
        }
        else
        {
            break;
        }
        DebugTools::Console::_log("Looping");
    }
    std::wstring the_tag = winrt::unbox_value_or<winrt::hstring>(args.InvokedItemContainer().Tag(), L"").c_str();
    DebugTools::Console::_log(L"Tag of invoked Navigation View Item:" + the_tag);
   if (the_tag == L"ABT") {     
       TheInfoBar().IsOpen(false);
   }
   else if (the_tag == L"HB2") {
       //Dont cloase the loading thing
        The_Frame().Navigate(xaml_typename<Terrible_Programs_Installer::HelpfulDebuggerv2>());       
        DebugTools::Console::_log(L"Navigated to:" + the_tag);
   }
   else if(the_tag == L"Settings")
   {
       The_Frame().Navigate(xaml_typename<Terrible_Programs_Installer::SettingsPage>());
       DebugTools::Console::_log(L"Navigated to:" + the_tag);
       TheInfoBar().IsOpen(false);
   }
}


void winrt::Terrible_Programs_Installer::implementation::MainWindow::Window_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args)
{
    //DebugTools::Downloader::DeleteAssets(false);
}
