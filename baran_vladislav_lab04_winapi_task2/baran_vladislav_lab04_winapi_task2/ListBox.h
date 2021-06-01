#pragma once

#include <windows.h>

class ListBox
{
private:
	HWND list_box;
public:
	ListBox();
	~ListBox();
	void SetParams(HWND hwnd, HINSTANCE hInst, int x, int y, int w, int h, int id);
	void GetString(int num, LPWSTR string);
	void Append(LPCWSTR string);
	void DeleteCurrent();
	void ClearHightliting();
	void InsertString(int num, LPCWSTR string);
	int GetCurrent();
	int Size();
	void ChangeCurrent(LPCWSTR string);
};

