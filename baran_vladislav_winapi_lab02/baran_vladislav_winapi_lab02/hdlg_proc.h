#ifndef WINAPI_HDLG_PROC_H_
#define WINAPI_HDLG_PROC_H_

#include <vector>
#include <Windows.h>

#define BUTTON_CASE(bDef, bFunc) \
case bDef:			\
	bFunc##();		\
	break;			\

#define BUTTON_FUNC(bFuncName) \
	void bFuncName##();

#define EMPTY_BUTTON_FUNC(bFuncName) \
	void ##bFuncName##() {}

class HdlgProc
{
protected:
	HWND hDlg;

	virtual void ButtonCheck(WORD bId);
	virtual void HdlgCreate();
	virtual void TimerEnd(WPARAM timer_id);
public:
	HdlgProc() = delete;
	HdlgProc(HWND hWnd);
	LRESULT Exec(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
