#include "MainWindowLab2.h"
#include "resource.h"

MainWindowLab2::MainWindowLab2(MAIN_WINDOW_PARAMETERS_CPP) :
	MainWindow()
{
	Init(MAIN_WINDOW_PARAMETERS_CPP_IN);
}

int MainWindowLab2::GetMenuID() {
	return IDR_MENU1;
}
