#include "main_window_lab1.h"
#include "hwnd_proc_lab1.h"

HWND_PROC_DEF(WndProc)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    MainWindowLab1 mainWnd(L"Winapi first lab", hInstance, nCmdShow, WndProc);
    //KWnd mainWnd("������ ����", hInstance, nCmdShow, WndProc, NULL, 300, 400, 500, 450);
    while (GetMessage(&msg, NULL, 0, 0))//��������� ���� ��������� ��������� �� �������� ����������
                                        //��������� ��������� ���������
    {
        TranslateMessage(&msg);//����� ���� ������� ����� �����, ����� ���� ��������� ������, ��������
                               //� ����������. ����������� ���� ��������� WM_KEYDOWN � WM_KEYUP �
                               //��������� WM_CHAR, ������� �������� ��� ������� (wParam) � ���� ��������
                               //���� TCHAR

        DispatchMessage(&msg);//�������� ��������� msg ������� � Windows.
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HwndProcLab1 hwnd_proc(hWnd);
    return hwnd_proc.Exec(uMsg, wParam, lParam);
}
