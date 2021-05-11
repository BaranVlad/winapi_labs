#pragma once

#include "hwnd_proc.h"
#include "resource.h"
#include <vector>

struct CircleT {
	int x;
	int y;
	int r;
};

class HwndProcLab2 : public HwndProc
{
private:
	int task = 1;

	// task1
	WCHAR text[100];
	int font_size;
	// task2
	int time = 0;
	//task3
	std::vector<CircleT> circles;
protected:
	void ButtonCheck(WORD bId);
	void TimerEnd(WPARAM timer_id);
	void MouseLeftButtonPressed(int x, int y);
	void PaintEvent();
public:
	HwndProcLab2(HWND hWnd);

	BUTTON_FUNC(ClickTask1)
	BUTTON_FUNC(ClickTask2)
	BUTTON_FUNC(ClickTask3)

	BUTTON_FUNC(PressPlus)
	BUTTON_FUNC(PressMinus)
	BUTTON_FUNC(PressCtrlS)
};

