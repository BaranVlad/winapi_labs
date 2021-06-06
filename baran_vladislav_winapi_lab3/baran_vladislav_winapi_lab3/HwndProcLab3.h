#pragma once

#include "hwnd_proc.h"
#include "resource.h"

struct TrafficCircle {
	int x;
	int y;
	int r;
	int time;

	COLORREF color_light;
	COLORREF color_dark;
	bool is_blink = false;
	bool is_light = false;
	bool is_change_size = false;
	int change_size_by = 0;

	TrafficCircle* next;

	void SetCoords(int x, int y, int r);
};

class HwndProcLab3 : public HwndProc
{
private:
	int task_ = 0;

	RECT car_rect;
	RECT traffic_lights;
	bool is_right_direction = true;
	int blink_time;

	int current_time = 0;
	TrafficCircle* current_light;

	TrafficCircle circles[3];

public:
	HwndProcLab3();
	void SetCmd(LPCSTR cmd);
	void SetHwnd(HWND hwnd);
	void PaintEvent();
	void TimerEnd(WPARAM timer_id);
	void MouseLeftButtonPressed(int x, int y);
	void MouseRightButtonPressed(int x, int y);

	void DrawCar(RECT draw_rect);
	void DrawTrafficLights(RECT draw_rect);
	void DrawTrafficLight(const TrafficCircle& light);
};

