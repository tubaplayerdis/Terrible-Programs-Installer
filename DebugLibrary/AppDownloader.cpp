#include "pch.h"
#include "AppDownloader.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <windows.h>
#include <math.h>

FILE* fpp = nullptr;

using namespace std;

int nb_bar;
double last_progress, progress_bar_adv;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int progress_bar(void* bar, double t, double d)
{
    if (last_progress != round(d / t * 100))
    {
        nb_bar = 25;
        progress_bar_adv = round(d / t * nb_bar);

        cout << "\r ";
        SetConsoleTextAttribute(hConsole, 160);
        cout << " Progress : [ ";

        if (round(d / t * 100) < 10)
        {
            cout << "0" << round(d / t * 100) << " %]";
        }
        else
        {
            cout << round(d / t * 100) << " %] ";
        }

        SetConsoleTextAttribute(hConsole, 15);
        cout << " [";
        SetConsoleTextAttribute(hConsole, 10);
        for (int i = 0; i <= progress_bar_adv; i++)
        {
            cout << "#";
        }
        SetConsoleTextAttribute(hConsole, 15);
        for (int i = 0; i < nb_bar - progress_bar_adv; i++)
        {
            cout << ".";
        }

        cout << "]";
        last_progress = round(d / t * 100);
    }
    return 0;
}

void TPIApplication::AppDownloader::Download(int Application)
{
    AllocConsole();
    fpp = nullptr;
    freopen_s(&fpp, "CONIN$", "r", stdin); //more for stdin and out
    freopen_s(&fpp, "CONOUT$", "w", stdout);
    freopen_s(&fpp, "CONOUT$", "w", stderr);
    freopen_s(&fpp, "CONIN$", "a", stdin);
    std::cout << "\n\nDownloading something?" <<std::endl;

    HWND conwin = GetConsoleWindow();
    SetForegroundWindow(conwin);

    CURL* curl_download;
    FILE* fp;
    CURLcode res;
    string url = "http://www.gecif.net/articles/mathematiques/pi/pi_1_million.txt", output_file = "C:\\Users\\aaron\\Documents\\pi.txt";

    curl_download = curl_easy_init();

    if (curl_download)
    {
        //SetConsoleTextAttribute(hConsole, 11);
        fp = fopen(output_file.c_str(), "wb");

        curl_easy_setopt(curl_download, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_download, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl_download, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl_download, CURLOPT_NOPROGRESS, FALSE);
        //progress_bar : the fonction for the progress bar
        curl_easy_setopt(curl_download, CURLOPT_PROGRESSFUNCTION, progress_bar);

        //Text color :   SetConsoleTextAttribute(hConsole, nb_color);
        SetConsoleTextAttribute(hConsole, 11);
        //cout << " Start download" << endl << endl; //no lol
        

        res = curl_easy_perform(curl_download);

        fclose(fp);
        if (res == CURLE_OK)
        {
            SetConsoleTextAttribute(hConsole, 10);
            cout << endl << endl << "The Application Downloaded Successfuly" << endl;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << endl << endl << "Chat something bad happened" << endl;
        }
        curl_easy_cleanup(curl_download);
    }
    SetConsoleTextAttribute(hConsole, 11);
    return;


}





