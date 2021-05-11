#ifndef WINAPI_MAIN_WINDOW_H_
#define WINAPI_MAIN_WINDOW_H_

#include <Windows.h>

#define HWND_PROC_DEF(proc_name)    LRESULT CALLBACK proc_name##(HWND, UINT, WPARAM, LPARAM);
#define HDLG_PROC_DEF(proc_name)    INT_PTR CALLBACK proc_name##(HWND, UINT, WPARAM, LPARAM);

#define MAIN_WINDOW_PARAMETERS_H    LPCWSTR windowName, HINSTANCE hInst, int cmdShow,\
        LRESULT(WINAPI* pWndProc)(HWND, UINT, WPARAM, LPARAM),                  \
        LPCWSTR menuName = NULL,                                                \
        int x = CW_USEDEFAULT, int y = 0,                                       \
        int width = CW_USEDEFAULT, int height = 0,                              \
        UINT classStyle = CS_HREDRAW | CS_VREDRAW,                              \
        DWORD windowStyle = WS_OVERLAPPEDWINDOW,                                \
        HWND hParent = NULL                                                     

#define MAIN_WINDOW_PARAMETERS_CPP   LPCWSTR windowName, HINSTANCE hInst, int cmdShow, \
        LRESULT(WINAPI* pWndProc)(HWND, UINT, WPARAM, LPARAM),                  \
        LPCWSTR menuName,                                                       \
        int x, int y,                                                           \
        int width, int height,                                                  \
        UINT classStyle,                                                        \
        DWORD windowStyle,                                                      \
        HWND hParent        

#define MAIN_WINDOW_PARAMETERS_CPP_IN windowName, hInst, cmdShow, pWndProc, menuName, x, y,\
        width, height, classStyle, windowStyle, hParent

class MainWindow {
protected:
    HWND hWnd;
    HINSTANCE hInstance;

    virtual int GetMenuID();
public:
	MainWindow();
    void Init(MAIN_WINDOW_PARAMETERS_H);
    void SetInstance(HINSTANCE hInstance);
    HWND GetHwnd();
};

#endif