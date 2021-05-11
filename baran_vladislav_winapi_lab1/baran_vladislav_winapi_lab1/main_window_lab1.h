#ifndef MAIN_WINDOW_LAB1_H_
#define MAIN_WINDOW_LAB1_H_

#include "main_window.h"
#include "resource.h"

class MainWindowLab1 : public MainWindow
{
protected:
    int GetMenuID();
public:
    MainWindowLab1(MAIN_WINDOW_PARAMETERS_H);
};

#endif

