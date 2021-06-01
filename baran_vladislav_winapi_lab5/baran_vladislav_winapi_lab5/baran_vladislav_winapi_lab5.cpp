#include "framework.h"
#include "baran_vladislav_winapi_lab5.h"
#include "Calculator.h"
#include <map>

INT_PTR CALLBACK    CalculatorProc(HWND, UINT, WPARAM, LPARAM);

Calculator calculator;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_CALCULATOR), NULL, CalculatorProc);
}

INT_PTR CALLBACK CalculatorProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    return calculator.Update(hDlg, message, wParam, lParam);
}
