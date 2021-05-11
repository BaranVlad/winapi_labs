#include "hwnd_proc.h"

HwndProc::HwndProc(HWND hwnd) : hWnd(hwnd) {}

LRESULT HwndProc::Exec(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
        HwndCreate();
        break;
    case WM_COMMAND:
        ButtonCheck(wParam);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        PaintEvent();
        EndPaint(hWnd, &ps);
        break;
    case WM_TIMER:
        TimerEnd(wParam);
        break;
    case WM_DESTROY:
        CloseEvent();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

void HwndProc::ButtonCheck(WORD bId) {}

void HwndProc::PaintEvent() {}

void HwndProc::CloseEvent() {}

void HwndProc::HwndCreate() {}

void HwndProc::TimerEnd(WPARAM timer_id) {}

void Line(HDC hdc, int x1, int y1, int x2, int y2) {
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}
