#include "HwndProcLab3.h"
#include <sstream>

#define TIMER_ID 10
#define BLINK_TIMER 500
#define CHANGE_SIZE_BY 10

void TrafficCircle::SetCoords(int x, int y, int r) {
	this->x = x;
	this->y = y;
	this->r = r;
}

HwndProcLab3::HwndProcLab3() :
	HwndProc()
{
	GetClientRect(hWnd, &client_rect);

	current_light = &circles[0];
	circles[0].is_light = true;

	circles[0].next = &circles[1];
	circles[1].next = &circles[2];
	circles[2].next = &circles[0];

	circles[0].color_light = RGB(255, 0, 0);
	circles[0].color_dark = RGB(80, 0, 0);

	circles[1].color_light = RGB(255, 255, 0);
	circles[1].color_dark = RGB(80, 80, 0);

	circles[2].color_light = RGB(0, 255, 0);
	circles[2].color_dark = RGB(0, 80, 0);
}

void HwndProcLab3::SetCmd(LPCSTR cmd) {
	if (task_ != 0) {
		return;
	}
	std::stringstream ss(cmd);

	GetClientRect(hWnd, &client_rect);
	ss >> task_;
	if (task_ == 1) {
		SetTimer(hWnd, TIMER_ID, 23, NULL);
		car_rect.top = 100;
		car_rect.left = 100;
		car_rect.bottom = 200;
		car_rect.right = 300;
		int dir;
		ss >> dir;
		if (dir == 0) {
			is_right_direction = true;
		}
		else {
			is_right_direction = false;
			std::swap(car_rect.left, car_rect.right);
			car_rect.left += 600;
			car_rect.right += 600;
		}
	} else if (task_ == 2) {
		SetTimer(hWnd, TIMER_ID, 1000, NULL);
		SetTimer(hWnd, BLINK_TIMER, 500, NULL);
		traffic_lights.left = 100;
		traffic_lights.top = 100;
		traffic_lights.right = 200;
		traffic_lights.bottom = 350;
		ss >> circles[0].time;
		ss >> circles[1].time;
		ss >> circles[2].time;
		ss >> blink_time;
	}
}

void HwndProcLab3::SetHwnd(HWND hwnd) {
	hWnd = hwnd;
}

void HwndProcLab3::DrawCar(RECT draw_rect) {
	HBRUSH brush;
	HPEN pen;

	POINT poly[7] = {
		{draw_rect.left + (draw_rect.right - draw_rect.left) / 4, draw_rect.top},
		{draw_rect.left + 3 * (draw_rect.right - draw_rect.left) / 4, draw_rect.top},
		{draw_rect.left + 3 * (draw_rect.right - draw_rect.left) / 4, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 4},
		{draw_rect.right, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 4},
		{draw_rect.right, draw_rect.top + 7 * (draw_rect.bottom - draw_rect.top) / 8},
		{draw_rect.left, draw_rect.top + 7 * (draw_rect.bottom - draw_rect.top) / 8},
		{draw_rect.left, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 4},
	};
	SET_PEN(cdc, pen, 2, 0);
	SET_BRUSH(cdc, brush, RGB(200, 44, 20));
	Polygon(cdc, poly, 7);
	DELETE_OBJECT(brush);
	Line(cdc, draw_rect.left, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 4, draw_rect.right, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 4);
	Line(cdc, draw_rect.left + (draw_rect.right - draw_rect.left) / 2, draw_rect.top, draw_rect.left + (draw_rect.right - draw_rect.left) / 2, draw_rect.top + 7 * (draw_rect.bottom - draw_rect.top) / 8);
	Line(cdc, draw_rect.left + 3 * (draw_rect.right - draw_rect.left) / 4, draw_rect.top, draw_rect.left + 3 * (draw_rect.right - draw_rect.left) / 4, draw_rect.top + 7 * (draw_rect.bottom - draw_rect.top) / 8);
	Line(cdc, draw_rect.left + (draw_rect.right - draw_rect.left) / 2 + 5, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 2, draw_rect.left + (draw_rect.right - draw_rect.left) / 2 + 40, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 2);
	SET_BRUSH(cdc, brush, RGB(100, 100, 100));
	Circle(cdc, draw_rect.left + (draw_rect.right - draw_rect.left) / 4, draw_rect.top + 7 * (draw_rect.bottom - draw_rect.top) / 8, (draw_rect.bottom - draw_rect.top) / 8);
	Circle(cdc, draw_rect.left + 3 * (draw_rect.right - draw_rect.left) / 4, draw_rect.top + 7 * (draw_rect.bottom - draw_rect.top) / 8, (draw_rect.bottom - draw_rect.top) / 8);
	DELETE_OBJECT(brush)
	SET_BRUSH(cdc, brush, RGB(50, 50, 200));
	Rectangle(cdc, draw_rect.left + (draw_rect.right - draw_rect.left) / 2, draw_rect.top, draw_rect.left + 3 * (draw_rect.right - draw_rect.left) / 4, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 4);
	DELETE_OBJECT(brush)
	DELETE_OBJECT(pen);
}

void HwndProcLab3::DrawTrafficLight(const TrafficCircle& light) {
	HBRUSH brush;
	if (light.is_light) {
		SET_BRUSH(cdc, brush, light.color_light);
	}
	else {
		SET_BRUSH(cdc, brush, light.color_dark);
	}

	int r = (light.is_change_size ? light.r - light.change_size_by : light.r);

	Circle(cdc, light.x, light.y, r);

	DELETE_OBJECT(brush);
}

void HwndProcLab3::DrawTrafficLights(RECT draw_rect) {
	HBRUSH brush;
	SET_BRUSH(cdc, brush, RGB(100, 100, 100));
	Rectangle(cdc, draw_rect.left, draw_rect.top, draw_rect.right, draw_rect.bottom);
	DELETE_OBJECT(brush);
	
	int r = (draw_rect.right - draw_rect.left) / 3 - 2;
	
	circles[0].SetCoords(draw_rect.left + (draw_rect.right - draw_rect.left) / 2, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 4 - 10, r);
	DrawTrafficLight(circles[0]);

	circles[1].SetCoords(draw_rect.left + (draw_rect.right - draw_rect.left) / 2, draw_rect.top + (draw_rect.bottom - draw_rect.top) / 2, r);
	DrawTrafficLight(circles[1]);

	circles[2].SetCoords(draw_rect.left + (draw_rect.right - draw_rect.left) / 2, draw_rect.top + 3 * (draw_rect.bottom - draw_rect.top) / 4 + 10, r);
	DrawTrafficLight(circles[2]);
}

void HwndProcLab3::PaintEvent() {
	GetClientRect(hWnd, &client_rect);
	if (task_ == 1) {
		DrawCar(car_rect);
	}
	else if (task_ == 2) {
		DrawTrafficLights(traffic_lights);
	}
}

void HwndProcLab3::TimerEnd(WPARAM timer_id) {
	if (timer_id == BLINK_TIMER) {
		if (current_light->is_blink) {
			current_light->is_light = !current_light->is_light;
		}
		for (int i = 0; i < 3; i++) {
			if (circles[i].is_change_size) {
				circles[i].change_size_by = (circles[i].change_size_by ? 0 : CHANGE_SIZE_BY);
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
	} else if (task_ == 1) {
		if ((car_rect.left <= client_rect.left && !is_right_direction) ||
			car_rect.left >= client_rect.right && is_right_direction)
		{
			std::swap(car_rect.left, car_rect.right);
			is_right_direction = !is_right_direction;
		}
		int offset = 10 * (is_right_direction ? 1 : -1);
		car_rect.left += offset;
		car_rect.right += offset;
		InvalidateRect(hWnd, NULL, FALSE);
	}
	else {
		if (current_time >= current_light->time - blink_time) {
			current_light->is_blink = true;
		}

		if (current_time >= current_light->time) {
			current_light->is_blink = false;
			current_light->is_light = false;
			current_light = current_light->next;
			current_light->is_light = true;
			current_time = 0;
		}
		
		InvalidateRect(hWnd, NULL, FALSE);
		current_time++;
	}
}

void HwndProcLab3::MouseLeftButtonPressed(int x, int y) {
	if (task_ != 2) {
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (IsInCircle(circles[i].x, circles[i].y, circles[i].r, x, y)) {
			circles[i].is_change_size = true;
		}
	}
}


void HwndProcLab3::MouseRightButtonPressed(int x, int y) {
	if (task_ != 2) {
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (IsInCircle(circles[i].x, circles[i].y, circles[i].r, x, y)) {
			circles[i].is_change_size = false;
		}
	}
}

