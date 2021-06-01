#pragma warning(disable:4996)
#include "Calculator.h"
#include "resource.h"
#include "Commctrl.h"

#include <string>
#include <map>

#define MAX_STRING_SIZE 1000

const std::map<std::wstring, double (*)(double, double)> operation = {
    {std::wstring(L"+"), [](double a, double b) { return a + b; }},
    {std::wstring(L"-"), [](double a, double b) { return a - b; }},
    {std::wstring(L"*"), [](double a, double b) { return a * b; }},
    {std::wstring(L"/"), [](double a, double b) { return a / b; }},

    {std::wstring(L"&"), [](double a, double b) { return (double)((int)a & (int)b); }},
    {std::wstring(L"|"), [](double a, double b) { return (double)((int)a | (int)b); }},
    {std::wstring(L"<<"), [](double a, double b) { return (double)((int)a << (int)b); }},
    {std::wstring(L">>"), [](double a, double b) { return (double)((int)a >> (int)b); }},
    {std::wstring(L"^"), [](double a, double b) { return (double)((int)a ^ (int)b); }}
};

void Calculator::SetLogical() {\
    if (is_logical) {
        return;
    }
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_RESETCONTENT, NULL, NULL);
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_ADDSTRING, NULL, (LPARAM)L"&");
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_ADDSTRING, NULL, (LPARAM)L"|");
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_ADDSTRING, NULL, (LPARAM)L"<<");
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_ADDSTRING, NULL, (LPARAM)L">>");
    is_logical = true;
}

void Calculator::SetArithmetical() {
    if (!is_logical) {
        return;
    }
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_RESETCONTENT, NULL, NULL);
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_ADDSTRING, NULL, (LPARAM)L"+");
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_ADDSTRING, NULL, (LPARAM)L"-");
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_ADDSTRING, NULL, (LPARAM)L"/");
    SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_ADDSTRING, NULL, (LPARAM)L"*");
    is_logical = false;
}

int Calculator::GetPrecision() {
    return SendDlgItemMessage(hDlg, IDC_PRECISION, TBM_GETPOS, NULL, NULL);
}

void Calculator::Calculate() {
    WCHAR first_str[MAX_STRING_SIZE];
    WCHAR second_str[MAX_STRING_SIZE];
    WCHAR operation_str[MAX_STRING_SIZE];
    WCHAR result_str[MAX_STRING_SIZE];

    GetDlgItemText(hDlg, IDC_FIRST_EDIT, first_str, MAX_STRING_SIZE);
    GetDlgItemText(hDlg, IDC_SECOND_EDIT, second_str, MAX_STRING_SIZE);
    GetDlgItemText(hDlg, IDC_COMBOBOX, operation_str, MAX_STRING_SIZE);
    try {
        double a = _wtof(first_str);
        double b = _wtof(second_str);
        if (is_logical && (a > INT_MAX || b > INT_MAX || a < INT_MIN || b < INT_MIN)) {
            SetDlgItemText(hDlg, IDC_ANSWER, L"Overflow");
        }
        else {
            double result = operation.at(std::wstring(operation_str))(a, b);
            WCHAR format[MAX_STRING_SIZE];
            int precision = GetPrecision();
            swprintf(format, L"%%\.%df", precision);
            swprintf(result_str, format, result);
            SetDlgItemText(hDlg, IDC_ANSWER, result_str);
        }
    }
    catch (std::exception& e) {
        SetDlgItemText(hDlg, IDC_ANSWER, L"Error");
    }
}


INT_PTR CALLBACK Calculator::Update(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam) {
    hDlg = hdlg;

    switch (message)
    {
    case WM_INITDIALOG: {
        SetArithmetical();
        CheckDlgButton(hDlg, IDC_ARITHMETICAL, BST_CHECKED);
        SendDlgItemMessage(hDlg, IDC_PRECISION, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10));
        return (INT_PTR)TRUE;
    }
    case WM_HSCROLL:
        Calculate();
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_ARITHMETICAL:
            SetArithmetical();
            if (IsDlgButtonChecked(hDlg, IDC_AUTOMATIC)) {
                Calculate();
            }
            break;
        case IDC_LOGICAL:
            SetLogical();
            if (IsDlgButtonChecked(hDlg, IDC_AUTOMATIC)) {
                Calculate();
            }
            break;
        case IDC_PRECISION:
            Calculate();
            break;
        case IDC_COMBOBOX:
        case IDC_FIRST_EDIT:
        case IDC_AUTOMATIC:
        case IDC_SECOND_EDIT:
            if (!IsDlgButtonChecked(hDlg, IDC_AUTOMATIC)) {
                break;
            }
        case IDC_CALC: {
            Calculate();
        }
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
}