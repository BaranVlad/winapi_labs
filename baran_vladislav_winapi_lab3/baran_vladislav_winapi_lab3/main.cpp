#include "MainWindowLab3.h"
#include "HwndProcLab3.h"
#include <string>

HWND_PROC_DEF(WndProc)

HwndProcLab3 hwnd_proc;
std::string cmd_str;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    cmd_str.assign(lpCmdLine);
    MSG msg;
    MainWindowLab3 mainWnd(L"Winapi first lab", hInstance, nCmdShow, WndProc);
    HACCEL haccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(mainWnd.GetHwnd(), haccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    hwnd_proc.SetHwnd(hWnd);
    hwnd_proc.SetCmd(cmd_str.c_str());
    return hwnd_proc.Exec(uMsg, wParam, lParam);
}
