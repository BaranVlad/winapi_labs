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
    case WM_LBUTTONDOWN:
        MouseLeftButtonPressed(LOWORD(lParam), HIWORD(lParam));
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

void HwndProc::ButtonCheck(WORD bId) {}

void HwndProc::PaintEvent() {}

void HwndProc::CloseEvent() {}

void HwndProc::MouseLeftButtonPressed(int x, int y) {}

void HwndProc::HwndCreate() {}

void HwndProc::TimerEnd(WPARAM timer_id) {}

void Line(HDC hdc, int x1, int y1, int x2, int y2) {
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

void Circle(HDC hdc, int x1, int y1, int r) {
    Ellipse(hdc, x1 - r, y1 - r, x1 + r, y1 + r);
}

bool IsInCircle(int x1, int y1, int r, int x2, int y2) {
    if (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= r) {
        return true;
    }
    return false;
}

