#pragma once

#include "framework.h"

#define BUTTONS_DEF 400

class TicTacToe
{
private:
	HWND parent;
	HINSTANCE hinstance;

	HWND buttons[3][3];
	
	HFONT font;

	int free_cells;
	int turn_num = 0;
	int computer_turn = 0;

	void DeleteField();
public:
	TicTacToe();
	~TicTacToe();

	void CreateField(HWND hwnd, HINSTANCE hinstance);
	void ResizeField(RECT client_rect);
	void ReplaceField(int x, int y);
	void ClearField();

	void SetCellText(int i, int j, LPCWSTR what);
	int MakeTurn(int i, int j, LPCWSTR what);

	void Turn(HWND button);
	bool IsBusy(int i, int j);

	void Restart();
	void StartComputerGame();
	void StartPlayerGame();
	void PlayerFirstTurn();

	void CalculateTurn(int& i, int& j);
	int IsWin();
	int GetCell(int i, int j);
	void WinMessage(int player);
	void TieMessage();

	void ComputerTurn();
};

