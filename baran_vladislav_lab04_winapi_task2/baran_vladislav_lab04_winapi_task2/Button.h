#pragma once

#include <Windows.h>

class Button
{
private:
	HWND button;
public:
	Button();
	~Button();

	void SetParams(HWND hwnd, HINSTANCE hInst, int x, int y, int w, int h, int id);
	void SetText(LPCWSTR text);
};

