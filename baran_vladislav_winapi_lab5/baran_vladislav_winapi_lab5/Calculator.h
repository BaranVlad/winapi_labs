#pragma once

#include <Windows.h>

class Calculator
{
private:
	HWND hDlg;

	bool is_logical = true;

public:
	INT_PTR CALLBACK Update(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLogical();
	void SetArithmetical();
	void Calculate();
	int GetPrecision();
};

