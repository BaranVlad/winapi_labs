#include "hdlg_proc.h"

HdlgProc::HdlgProc(HWND hwnd) : hDlg(hwnd) {}

LRESULT HdlgProc::Exec(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_INITDIALOG:
        HdlgCreate();
        break;
    case WM_COMMAND:
        ButtonCheck(wParam);
        break;
    case WM_TIMER:
        TimerEnd(wParam);
        break;
    default:
        return DefWindowProc(hDlg, uMsg, wParam, lParam);
    }
    return 0;
}

void HdlgProc::ButtonCheck(WORD bId) {}

void HdlgProc::HdlgCreate() {}

void HdlgProc::TimerEnd(WPARAM timer_id) {}

