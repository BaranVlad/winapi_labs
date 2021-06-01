// baran_vladislav_lab04_winapi_task2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "baran_vladislav_lab04_winapi_task2.h"
#include "ListBox.h"
#include "Button.h"

#define MAX_LOADSTRING 100
#define IDC_LISTBOX1 1001
#define IDC_LISTBOX2 1002
#define IDC_SWAP_BUTTON 1003
#define IDM_EDIT 1005
#define IDM_DELETE 1006
#define IDM_ADD 1007

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
ListBox list_box1;
ListBox list_box2;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    EditDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AddDialog(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BARANVLADISLAVLAB04WINAPITASK2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BARANVLADISLAVLAB04WINAPITASK2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BARANVLADISLAVLAB04WINAPITASK2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BARANVLADISLAVLAB04WINAPITASK2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static Button button;
    switch (message)
    {
    case WM_CREATE: {
        button.SetParams(hWnd, hInst, 320, 200, 60, 40, IDC_SWAP_BUTTON);
        button.SetText(L"Bring");

        list_box1.SetParams(hWnd, hInst, 100, 100, 200, 300, IDC_LISTBOX1);
        list_box2.SetParams(hWnd, hInst, 400, 100, 200, 300, IDC_LISTBOX2);
        list_box1.Append(L"sdsdsdssds");
        list_box2.Append(L"sdjkfks");

        break;
    }

    case WM_COMMAND:
        {
            
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_EDIT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_EDIT), hWnd, EditDialog);
                break;
            case IDM_DELETE:
                if (list_box1.GetCurrent() != -1) {
                    list_box1.DeleteCurrent();
                } else if (list_box2.GetCurrent() != -1) {
                    list_box2.DeleteCurrent();
                }
                break;
            case IDM_ADD:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD), hWnd, AddDialog);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDC_LISTBOX1:
                if (HIWORD(wParam) == LBN_SETFOCUS) {
                    list_box2.ClearHightliting();
                }
                break;
            case IDC_LISTBOX2:
                if (HIWORD(wParam) == LBN_SETFOCUS) {
                    list_box1.ClearHightliting();
                }
                break;
            case IDC_SWAP_BUTTON: {
                WCHAR swap_string[MAX_LOADSTRING];
                int cur1 = list_box1.GetCurrent();
                int cur2 = list_box2.GetCurrent();
                if (cur1 != -1) {
                    list_box1.GetString(cur1, swap_string);
                    list_box1.DeleteCurrent();
                    list_box2.Append(swap_string);
                }
                else if (cur2 != -1) {
                    list_box2.GetString(cur2, swap_string);
                    list_box2.DeleteCurrent();
                    list_box1.Append(swap_string);
                }
            }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CONTEXTMENU:
    {
        HMENU hMenu = CreatePopupMenu();
        
        AppendMenu(hMenu, MFT_STRING, IDM_ADD, L"Добавить");
        AppendMenu(hMenu, MFT_STRING, IDM_EDIT, L"Редактировать");
        AppendMenu(hMenu, MFT_STRING, IDM_DELETE, L"Удалить");

        TrackPopupMenu(hMenu, TPM_RIGHTBUTTON |
            TPM_TOPALIGN |
            TPM_LEFTALIGN,
            LOWORD(lParam),
            HIWORD(lParam), 0, hWnd, NULL);
        DestroyMenu(hMenu);
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK EditDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        } else if (LOWORD(wParam) == IDC_CHANGE) {
            WCHAR string[MAX_LOADSTRING];
            GetDlgItemText(hDlg, IDC_STRING_EDIT, string, MAX_LOADSTRING);
            if (list_box1.GetCurrent() != -1) {
                list_box1.ChangeCurrent(string);
            } else if (list_box2.GetCurrent() != -1) {
                list_box2.ChangeCurrent(string);
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AddDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_CHANGE) {
            WCHAR string[MAX_LOADSTRING];
            GetDlgItemText(hDlg, IDC_STRING_EDIT, string, MAX_LOADSTRING);
            if (IsDlgButtonChecked(hDlg, IDC_RADIO1)) {
                list_box1.Append(string);
            }
            else if (IsDlgButtonChecked(hDlg, IDC_RADIO2)) {
                list_box2.Append(string);
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

