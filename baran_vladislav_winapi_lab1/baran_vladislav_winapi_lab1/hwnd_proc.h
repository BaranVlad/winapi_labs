#ifndef WINAPI_HWND_PROC_H_
#define WINAPI_HWND_PROC_H_

#include <vector>
#include <Windows.h>

#define BUTTON_CASE(bDef, bFunc) \
case bDef:			\
	bFunc##();		\
	break;			\

#define BUTTON_FUNC(bFuncName) \
	void bFuncName##();

#define EMPTY_BUTTON_FUNC(bFuncName) \
	void bFuncName##() {}

#define SET_PEN(hdc, penName, width, color) penName = CreatePen(PS_SOLID, width, color); SelectObject(hdc, penName);
#define STYLE_SET_PEN(hdc, penName, style, width, color) penName = CreatePen(style, width, color); SelectObject(hdc, penName);
#define SET_BRUSH(hdc, brushName, color) brushName = CreateSolidBrush(color); SelectObject(hdc, brushName);
#define DELETE_OBJECT(penName) DeleteObject(penName);

void Line(HDC hdc, int x1, int y1, int x2, int y2);

class HwndProc
{
protected:
	HWND hWnd;
	RECT client_rect;
	HDC hdc;
	PAINTSTRUCT ps;

	virtual void PaintEvent();
	virtual void CloseEvent();
	virtual void ButtonCheck(WORD bId);
	virtual void HwndCreate();
	virtual void TimerEnd(WPARAM timer_id);
public:
	HwndProc() = delete;
	HwndProc(HWND hWnd);
	LRESULT Exec(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
