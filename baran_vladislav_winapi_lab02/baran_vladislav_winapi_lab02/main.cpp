#include "MainWindowLab2.h"
#include "HwndProcLab2.h"

HWND_PROC_DEF(WndProc)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    MainWindowLab2 mainWnd(L"Winapi first lab", hInstance, nCmdShow, WndProc);

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
    static HwndProcLab2 hwnd_proc(hWnd);
    return hwnd_proc.Exec(uMsg, wParam, lParam);
}
