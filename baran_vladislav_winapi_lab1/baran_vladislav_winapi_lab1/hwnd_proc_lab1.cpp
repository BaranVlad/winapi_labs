#include "hwnd_proc_lab1.h"

#include <cmath>
#define M_PI 3.14159265358979323846 

HwndProcLab1::HwndProcLab1(HWND hwnd) : 
	HwndProc(hwnd)
{
	schedule.AddSubject(0, L"Практика", L"Програм", L"506");
	schedule.AddSubject(0, L"Лекция", L"Програм", L"605");
	schedule.AddSubject(0, L"Лекция", L"МА", L"605");
	schedule.AddSubject(0, L"Практика", L"МА", L"518");

	schedule.AddSubject(1, L"Лекция", L"ГА", L"605");
	schedule.AddSubject(1, L"Практика", L"ГА", L"518");
	schedule.AddSubject(1, L"Практика", L"Англ.яз.", L"600-б");

	schedule.AddSubject(2, L"Лекция", L"МА", L"605");
	schedule.AddSubject(2, L"Практика", L"МА", L"518");
	schedule.AddSubject(2, L"Практика", L"Програм", L"508");
	schedule.AddSubject(2, L"Практика", L"Програм", L"508");

	schedule.AddSubject(3, L"Практика", L"ДМиМЛ", L"300-б");
	schedule.AddSubject(3, L"Практика", L"УП", L"508");
	schedule.AddSubject(3, L"Лекция", L"Програм", L"605");
	schedule.AddSubject(3, L"Физ-ра", L"Физкультура", L"Спортзал");

	schedule.AddSubject(4, L"Лекция", L"ГА", L"605");
	schedule.AddSubject(4, L"Практика", L"ГА", L"522");
	schedule.AddSubject(4, L"Практика", L"Англ.яз.", L"607(ЮФ)");
	schedule.AddSubject(4, L"Лекция", L"ДМиМЛ", L"605");

	schedule.AddSubject(5);
	schedule.AddSubject(5);
	schedule.AddSubject(5);
	schedule.AddSubject(5, L"Физ-ра", L"Физкультура", L"Спортзал");
}

void HwndProcLab1::ButtonCheck(WORD bId) {
	switch (bId) {
		BUTTON_CASE(IDC_TASK1, ClickTask1)
		BUTTON_CASE(IDC_TASK2, ClickTask2)
		BUTTON_CASE(IDC_TASK3, ClickTask3)
		BUTTON_CASE(IDC_TASK4, ClickTask4)
		BUTTON_CASE(IDC_TASK5, ClickTask5)
		BUTTON_CASE(IDC_TASK6, ClickTask6)
	}
	InvalidateRect(hWnd, NULL, TRUE);
}

void HwndProcLab1::ClickTask1() {
	task_num = 1;
}

void HwndProcLab1::ClickTask2() {
	task_num = 2;
}

void HwndProcLab1::ClickTask3() {
	task_num = 3;
}

void HwndProcLab1::ClickTask4() {
	task_num = 4;
}

void HwndProcLab1::ClickTask5() {
	task_num = 5;
}

void HwndProcLab1::ClickTask6() {
	task_num = 6;
}

void HwndProcLab1::PaintEvent() {
	GetClientRect(hWnd, &client_rect);
	switch (task_num) {
	case 1:
		DrawTask1();
		break;
	case 2:
		DrawTask2();
		break;
	case 3:
		DrawTask3();
		break;
	case 4:
		DrawTask4();
		break;
	case 5:
		DrawTask5();
		break;
	case 6:
		DrawTask6();
		break;
	}
}

void HwndProcLab1::DrawTask1() {
	Rectangle(hdc, 10, 10, client_rect.right - 10, client_rect.bottom - 10);
}

void HwndProcLab1::DrawTask2() {
	Ellipse(hdc, client_rect.left, client_rect.top, client_rect.right, client_rect.bottom);
}

void HwndProcLab1::DrawTask3() {
	SetTextAlign(hdc, TA_LEFT | TA_TOP);
	TextOut(hdc, 0, 0, L"Left-Top corner", 15);

	SetTextAlign(hdc, TA_RIGHT | TA_TOP);
	TextOut(hdc, client_rect.right, 0, L"Right-Top corner", 16);

	SetTextAlign(hdc, TA_LEFT | TA_BOTTOM);
	TextOut(hdc, 0, client_rect.bottom, L"Left-Bottom corner", 18);

	SetTextAlign(hdc, TA_RIGHT | TA_BOTTOM);
	TextOut(hdc, client_rect.right, client_rect.bottom, L"Right-Bottom corner", 19);

	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
	TextOut(hdc, client_rect.right / 2, client_rect.bottom / 2, L"Center", 6);
}

void HwndProcLab1::DrawTask4() {
	HPEN pen;
	HBRUSH brush;

	int bound_offset = 30;
	int text_x1 = client_rect.right / 4;
	int text_x2 = 3 * client_rect.right / 4;
	int text_y1 = client_rect.bottom / 2 - bound_offset / 4;
	int text_y2 = client_rect.bottom - bound_offset / 4;

	STYLE_SET_PEN(hdc, pen, PS_DOT, 1, RGB(0, 0, 0));
	Line(hdc, client_rect.right / 2, 0, client_rect.right / 2, client_rect.bottom);
	Line(hdc, 0, client_rect.bottom / 2, client_rect.right, client_rect.bottom / 2);
	DELETE_OBJECT(pen);

	SET_BRUSH(hdc, brush, RGB(200, 50, 100));
	SET_PEN(hdc, pen, 10, RGB(130, 50, 150));
	Ellipse(hdc, bound_offset, bound_offset, client_rect.right / 2 - bound_offset, client_rect.bottom / 2 - bound_offset);
	DELETE_OBJECT(pen);
	DELETE_OBJECT(brush);

	SET_BRUSH(hdc, brush, RGB(50, 200, 50));
	STYLE_SET_PEN(hdc, pen, PS_DASH, 1, RGB(255, 0, 0));
	Rectangle(hdc, client_rect.right / 2 + bound_offset, bound_offset, client_rect.right - bound_offset, client_rect.bottom / 2 - bound_offset);
	DELETE_OBJECT(pen);
	DELETE_OBJECT(brush);

	SET_BRUSH(hdc, brush, RGB(50, 50, 200));
	SET_PEN(hdc, pen, 8, RGB(250, 250, 50));
	Pie(hdc, bound_offset, client_rect.bottom / 2 + bound_offset, client_rect.right / 2 - bound_offset, client_rect.bottom - bound_offset, client_rect.right / 4 + 100, 3 * client_rect.bottom / 4, client_rect.right / 4 + (int)(cos(M_PI / 6.) * 100), 3 * client_rect.bottom / 4 - (int)(sin(M_PI / 6.) * 100));
	DELETE_OBJECT(pen);
	DELETE_OBJECT(brush);

	POINT poly[4] = {
		{client_rect.right / 2 + bound_offset, 3 * client_rect.bottom / 4},
		{3 * client_rect.right / 4, client_rect.bottom / 2 + bound_offset},
		{client_rect.right - bound_offset, 3 * client_rect.bottom / 4},
		{3 * client_rect.right / 4, client_rect.bottom - bound_offset}
	};

	SET_BRUSH(hdc, brush, RGB(150, 250, 150));
	SET_PEN(hdc, pen, 4, RGB(150, 50, 250));
	Polygon(hdc, poly, 4);
	DELETE_OBJECT(pen);
	DELETE_OBJECT(brush);

	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
	TextOut(hdc, text_x1, text_y1, L"Ellipse", 7);
	TextOut(hdc, text_x1, text_y2, L"Pie", 3);
	TextOut(hdc, text_x2, text_y1, L"Rectangle", 9);
	TextOut(hdc, text_x2, text_y2, L"Rhombus", 7);
}

void UpdateColor(double& c1, double& c2, double& c3, double velocity) {
	if (c3 > 0) {
		c3 = max(c3 - velocity, 0);
		return;
	}
	if (c2 < 255) {
		c2 = min(c2 + velocity, 255);
		if (c2 >= 255) {
			c1 -= velocity;
		}
		return;
	}
}

void HwndProcLab1::DrawTask5() {
	int max_offset = min(client_rect.right / 2, client_rect.bottom / 2);
	double velocity = 6. * 255 / max_offset;
	RECT rect;
	HBRUSH brush;
	double r = 255;
	double g = 0;
	double b = 0;
	for (int offset = 0; offset <= max_offset; offset++) {
		SET_BRUSH(hdc, brush, RGB((int)r, (int)g, (int)b));
		rect.left = offset;
		rect.top = offset;
		rect.right = client_rect.right - offset;
		rect.bottom = client_rect.bottom - offset;
		FillRect(hdc, &rect, brush);
		DELETE_OBJECT(brush);

		if (r >= 255) {
			UpdateColor(r, g, b, velocity);
		}
		else if (g >= 255) {
			UpdateColor(g, b, r, velocity);
		}
		else if (b >= 255) {
			UpdateColor(b, r, g, velocity);
		}
	}
}

void HwndProcLab1::DrawTask6() {
	schedule.SetRect(client_rect);
	schedule.Draw(hdc);
}

