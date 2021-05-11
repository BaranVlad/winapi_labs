#ifndef HWND_PROC_LAB1_H_
#define HWND_PROC_LAB2_H_

#include "hwnd_proc.h"
#include "resource.h"

#include "schedule.h"

class HwndProcLab1 : public HwndProc
{
private:
	int task_num = 1;
	Schedule schedule;
protected:
	void ButtonCheck(WORD bId);
	void PaintEvent();
public:
	HwndProcLab1(HWND hwnd);

	void DrawTask1();
	void DrawTask2();
	void DrawTask3();
	void DrawTask4();
	void DrawTask5();
	void DrawTask6();

	BUTTON_FUNC(ClickTask1)
	BUTTON_FUNC(ClickTask2)
	BUTTON_FUNC(ClickTask3)
	BUTTON_FUNC(ClickTask4)
	BUTTON_FUNC(ClickTask5)
	BUTTON_FUNC(ClickTask6)
};

#endif


