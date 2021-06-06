#pragma warning(disable:4996)
#include "HwndProcLab2.h"

#define TIMER_ID 10
#define CIRCLE_RADIUS 100

#define START_CIRCLE_RADIUS 30
#define CIRCLE_BIGGER_BY 20

HwndProcLab2::HwndProcLab2(HWND hWnd) :
	HwndProc(hWnd)
{
	font_size = 16;
	wcscpy(text, L"Some text");
}

void HwndProcLab2::ButtonCheck(WORD bId) {
	switch (bId) {
		BUTTON_CASE(IDC_TASK1, ClickTask1)
		BUTTON_CASE(IDC_TASK2, ClickTask2)
		BUTTON_CASE(IDC_TASK3, ClickTask3)

		BUTTON_CASE(IDA_PLUS, PressPlus)
		BUTTON_CASE(IDA_MINUS, PressMinus)
		BUTTON_CASE(IDA_CTRL_S, PressCtrlS)
	}
	
	InvalidateRect(hWnd, NULL, TRUE);
}

void HwndProcLab2::ClickTask1() {
	task = 1;
}

void HwndProcLab2::ClickTask2() {
	task = 2;
}

void HwndProcLab2::ClickTask3() {
	task = 3;
}

void HwndProcLab2::PressPlus() {
	if (task == 1 && font_size < 100) {
		int size = wcslen(text);
		font_size += 2;
		text[size] = L'+';
		text[size + 1] = 0;
	}
	else if (task == 2) {
		SetTimer(hWnd, TIMER_ID, 1000, NULL);
	}
}

void HwndProcLab2::TimerEnd(WPARAM timer_id) {
	if (timer_id == TIMER_ID && task == 2) {
		time++;
	}
	InvalidateRect(hWnd, NULL, TRUE);
}

void HwndProcLab2::PressMinus() {
	if (task == 1 && font_size > 6) {
		int size = wcslen(text);
		font_size -= 2;
		text[size] = L'-';
		text[size + 1] = 0;
	}
	else if (task == 2) {
		KillTimer(hWnd, TIMER_ID);
	}
}

void HwndProcLab2::PressCtrlS() {
	SetTimer(hWnd, TIMER_ID, 1000, NULL);
	time = 0;
}

void HwndProcLab2::MouseLeftButtonPressed(int x, int y) {
	if (task != 3) {
		return;
	}
	bool is_in_circle = false;
	for (CircleT& circle : circles) {
		if (IsInCircle(circle.x, circle.y, circle.r, x, y)) {
			circle.r += CIRCLE_BIGGER_BY;
			is_in_circle = true;
		}
	}

	if (!is_in_circle) {
		CircleT circle;
		circle.x = x;
		circle.y = y;
		circle.r = START_CIRCLE_RADIUS;
		circles.push_back(circle);
	}

	InvalidateRect(hWnd, NULL, true);
}

void HwndProcLab2::PaintEvent() {
	GetClientRect(hWnd, &client_rect);
	switch (task) {
	case 1: {
		HFONT font = CreateFont(font_size, 0, 0, 0, 0, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, NULL);
		SelectObject(hdc, font);
		SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
		TextOut(hdc, client_rect.right / 2, client_rect.bottom / 2, text, wcslen(text));
		DeleteObject(font);
		return;
	}
	case 2: {
		WCHAR str_time[100];
		swprintf(str_time, L"%d", time);
		SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
		Circle(hdc, client_rect.right / 2, client_rect.bottom / 2, CIRCLE_RADIUS);
		TextOut(hdc, client_rect.right / 2, client_rect.bottom / 2, str_time, wcslen(str_time));
		return;
	}
	case 3: {
		SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
		for (CircleT& circle : circles) {
			Circle(hdc, circle.x, circle.y, circle.r);
		}
		return;
	}
	}
}
