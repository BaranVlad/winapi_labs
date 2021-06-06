#include "MainWindowLab3.h"
#include "resource.h"

MainWindowLab3::MainWindowLab3(MAIN_WINDOW_PARAMETERS_CPP) :
	MainWindow()
{
	Init(MAIN_WINDOW_PARAMETERS_CPP_IN);
}

int MainWindowLab3::GetMenu() {
	return IDR_MENU;
}

