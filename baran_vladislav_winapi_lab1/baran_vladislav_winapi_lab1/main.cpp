#include "main_window_lab1.h"
#include "hwnd_proc_lab1.h"

HWND_PROC_DEF(WndProc)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    MainWindowLab1 mainWnd(L"Winapi first lab", hInstance, nCmdShow, WndProc);
    //KWnd mainWnd("ѕример окна", hInstance, nCmdShow, WndProc, NULL, 300, 400, 500, 450);
    while (GetMessage(&msg, NULL, 0, 0))//выполн€ем цикл обработки сообщений до закрыти€ приложени€
                                        //извлекаем очередное сообщение
    {
        TranslateMessage(&msg);//вызов этой функции нужен тогда, когда идет обработка данных, вводимых
                               //с клавиатуры. ѕреобразует пару сообщений WM_KEYDOWN и WM_KEYUP в
                               //сообщение WM_CHAR, которое содержит код символа (wParam) в виде значени€
                               //типа TCHAR

        DispatchMessage(&msg);//передает структуру msg обратно в Windows.
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HwndProcLab1 hwnd_proc(hWnd);
    return hwnd_proc.Exec(uMsg, wParam, lParam);
}
