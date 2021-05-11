#include "main_window_lab1.h"

MainWindowLab1::MainWindowLab1(MAIN_WINDOW_PARAMETERS_CPP) :
	MainWindow()
{
	Init(MAIN_WINDOW_PARAMETERS_CPP_IN);
}

int MainWindowLab1::GetMenuID() {
	return IDR_MENU;
}
