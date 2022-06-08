#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#include <winrt/Microsoft.UI.Interop.h>
#include <atlstr.h>
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Storage;
using namespace Windows::System;
using namespace Windows::Foundation;

namespace winrt::WooSuRecord::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        m_mainAppWindow = GetAppWindowForCurrentWindow();

        winrt::Windows::Graphics::SizeInt32 windowSize;
        windowSize.Height = 230;
        windowSize.Width = 270;
        m_mainAppWindow.Resize(windowSize);

        winrt::Windows::Graphics::PointInt32 windowPoint;
        windowPoint.X = (1920 - windowSize.Width) / 2;
        windowPoint.Y = (1080 - windowSize.Height) / 2;
        m_mainAppWindow.Move(windowPoint);

        this->Title(L"WooSu 녹음기");
    }
    winrt::AppWindow MainWindow::GetAppWindowForCurrentWindow()
    {
        winrt::WooSuRecord::MainWindow thisWindow = *this;
        winrt::com_ptr<IWindowNative> windowNative = thisWindow.as<IWindowNative>();
        HWND hWnd;
        windowNative->get_WindowHandle(&hWnd);
        winrt::WindowId windowId;
        windowId = winrt::GetWindowIdFromWindow(hWnd);
        Microsoft::UI::Windowing::AppWindow appWindow = Microsoft::UI::Windowing::AppWindow::GetFromWindowId(windowId);
        return appWindow;
    }
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }
    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::settingButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        settingPanel().Visibility(Visibility::Visible);
        recordPanel().Visibility(Visibility::Collapsed);
    }
    void MainWindow::settingCloseButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        settingPanel().Visibility(Visibility::Collapsed);
        recordPanel().Visibility(Visibility::Visible);
    }

    void MainWindow::openfolderButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        CString STR = _T("C:\\");
        ShellExecute(NULL, L"open", STR, NULL, NULL, SW_SHOW);
    }
    void MainWindow::githubButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        CString STR = _T("https://github.com/wjh2335/WooSuRecord");
        ShellExecute(NULL, L"open", STR, NULL, NULL, SW_SHOW);
    }
    void MainWindow::playButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        std::string text_str;
        hstring text_hstr = _time().Text();
        text_str.assign(text_hstr.begin(), text_hstr.end());
        int cnt = atoi(text_str.c_str());
        ++cnt;
        if (cnt > _timeSlider().Maximum()) cnt = 0;
        _time().Text(to_hstring(cnt));
        _timeSlider().Value(cnt);
    }
    void MainWindow::stopButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        std::string text_str;
        hstring text_hstr = _time().Text();
        text_str.assign(text_hstr.begin(), text_hstr.end());
        int cnt = atoi(text_str.c_str());
        cnt = 0;
        _time().Text(to_hstring(cnt));
        _timeSlider().Value(cnt);
    }
    void MainWindow::pauseButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        SYSTEMTIME cur_time;
        GetLocalTime(&cur_time);
        wsprintf(g_time_str, L"%02d시%02d분%02d초", cur_time.wHour, cur_time.wMinute, cur_time.wSecond);
        _time().Text(g_time_str);
    }
    void MainWindow::slider_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        _time().Text(to_hstring(_timeSlider().Value()));
    }
    void MainWindow::startButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (state == 0)
        {
            state = 1;
            StartBtn().Content(box_value(L"녹음중..."));
            start = time(NULL);
            _time().Text(to_hstring(time(NULL) - start));
        }
        else
        {
            state = 0;
            StartBtn().Content(box_value(L"●"));
            end = time(NULL);
            _time().Text(to_hstring(end - start));
            _timeSlider().Maximum(end - start);
            _timeSlider().Value(end - start);
        }
    }
    void MainWindow::deleteButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        std::string text_str;
        hstring text_hstr = _time().Text();
        text_str.assign(text_hstr.begin(), text_hstr.end());
        int cnt = atoi(text_str.c_str());
        cnt = 0;
        _time().Text(to_hstring(cnt));
        _timeSlider().Value(cnt);
        _timeSlider().Maximum(100);
    }
}