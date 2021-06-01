#include "Button.h"

Button::Button() {}

void Button::SetParams(HWND hwnd, HINSTANCE hInst, int x, int y, int w, int h, int id) {
	button = CreateWindow(L"button", NULL,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, w, h,
		hwnd, (HMENU)id, hInst, NULL);
}

Button::~Button() {
	DestroyWindow(button);
	CloseWindow(button);
}

void Button::SetText(LPCWSTR text) {
	SetWindowText(button, text);
}

