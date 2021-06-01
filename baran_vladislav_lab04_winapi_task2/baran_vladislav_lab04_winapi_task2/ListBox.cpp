#include "ListBox.h"

ListBox::ListBox() {

}

void ListBox::SetParams(HWND hwnd, HINSTANCE hInst, int x, int y, int w, int h, int id) {
	list_box = CreateWindow(L"listbox", NULL,
		WS_CHILD | WS_VISIBLE | LBS_STANDARD,
		x, y, w, h,
		hwnd, (HMENU)id, hInst, NULL);
}

void ListBox::GetString(int num, LPWSTR string) {
	SendMessage(list_box, LB_GETTEXT, (WPARAM)num, (LPARAM)string);
}

void ListBox::Append(LPCWSTR string) {
	SendMessage(list_box, LB_ADDSTRING, NULL, (LPARAM)string);
}

ListBox::~ListBox() {
	DestroyWindow(list_box);
	CloseWindow(list_box);
}

void ListBox::ClearHightliting() {
	SendMessage(list_box, LB_SETCURSEL, -1, NULL);
}

int ListBox::GetCurrent() {
	return SendMessage(list_box, LB_GETCURSEL, NULL, NULL);
}

void ListBox::DeleteCurrent() {
	SendMessage(list_box, LB_DELETESTRING, GetCurrent(), NULL);
}

int ListBox::Size() {
	return SendMessage(list_box, LB_GETCOUNT, NULL, NULL);
}

void ListBox::ChangeCurrent(LPCWSTR string) {
	int curr = GetCurrent();
	DeleteCurrent();
	InsertString(curr, string);
}

void ListBox::InsertString(int num, LPCWSTR string) {
	SendMessage(list_box, LB_INSERTSTRING, num, (LPARAM)string);
}


