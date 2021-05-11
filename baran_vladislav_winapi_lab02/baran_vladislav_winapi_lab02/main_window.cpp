#include "main_window.h"

MainWindow::MainWindow() {}

void MainWindow::Init(MAIN_WINDOW_PARAMETERS_CPP) {

    WNDCLASSEXW wc;

    WCHAR szClassName[] = L"MainWindowClass";

    wc.cbSize = sizeof(wc);
    wc.style = classStyle;
    wc.lpfnWndProc = pWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = MAKEINTRESOURCE(GetMenuID());
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // Регистрируем класс окна
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Cannot register class: ", L"Error", MB_OK);
        return;
    }

    // Создаем окно
    hWnd = CreateWindow(szClassName, windowName, windowStyle,
        x, y, width, height, hParent, (HMENU)NULL, hInst, NULL);

    if (!hWnd) {
        MessageBox(NULL, L"Cannot create window: ", L"Error", MB_OK);
        return;
    }

    // Показываем  окно
    ShowWindow(hWnd, cmdShow);
}

int MainWindow::GetMenuID() {
    return 0;
}

HWND MainWindow::GetHwnd() {
    return hWnd;
}

void MainWindow::SetInstance(HINSTANCE value) {
    hInstance = value;
}

