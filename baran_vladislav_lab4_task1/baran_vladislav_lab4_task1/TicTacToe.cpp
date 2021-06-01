#include "TicTacToe.h"

#define BUTTON_SIZE 100
#define FONT_SIZE 100
#define COMPUTER_PING 400

TicTacToe::TicTacToe() {
	font = CreateFont(FONT_SIZE, 0, 0, 0, 0, ANSI_CHARSET, 0U, 0U, 0U, 0U, 0U, 0U, 0U, TEXT("Arial"));
}

void TicTacToe::CreateField(HWND hwnd, HINSTANCE hinstance) {
	computer_turn = 1;
	turn_num = 0;
	free_cells = 9;
	parent = hwnd;
	this->hinstance = hinstance;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			buttons[i][j] = CreateWindow(L"Button", NULL, WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 0, 0, 100, 100, hwnd, (HMENU)BUTTONS_DEF, hinstance, NULL);
			SendMessage(buttons[i][j], WM_SETFONT, (WPARAM)font, (LPARAM)TRUE);
		}
	}
	if (computer_turn == 0) {
		ComputerTurn();
	}
}

void TicTacToe::ClearField() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			SetCellText(i, j, L"");
		}
	}
}

void TicTacToe::ReplaceField(int x, int y) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			SetWindowPos(buttons[i][j], NULL, x + i * BUTTON_SIZE, y + j * BUTTON_SIZE, BUTTON_SIZE, BUTTON_SIZE, NULL);
		}
	}
}

void TicTacToe::ResizeField(RECT client_rect) {
	ReplaceField(client_rect.right / 2 - 3 * BUTTON_SIZE / 2, client_rect.bottom / 2 - 3 * BUTTON_SIZE / 2);
}

TicTacToe::~TicTacToe() {
	DeleteField();
}

void TicTacToe::SetCellText(int i, int j, LPCWSTR what) {
	SetWindowText(buttons[i][j], what);
}

int TicTacToe::MakeTurn(int i, int j, LPCWSTR what) {
	if (IsBusy(i, j)) {
		return 0;
	}
	SetCellText(i, j, what);
	turn_num = 1 - turn_num;
	free_cells--;
	WinMessage(IsWin());
	if (free_cells <= 0) {
		TieMessage();
	}
	return IsWin();
}

bool TicTacToe::IsBusy(int i, int j) {
	WCHAR text[2];
	GetWindowText(buttons[i][j], text, 2);
	if (text[0] == L'\0') {
		return false;
	}
	return true;
}

void TicTacToe::Turn(HWND button) {
	bool is_turned = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (buttons[i][j] == button) {
				MakeTurn(i, j, (turn_num == 0 ? L"X" : L"O"));
			}
		}
	}
	ComputerTurn();
}

void TicTacToe::DeleteField() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			DestroyWindow(buttons[i][j]);
			CloseWindow(buttons[i][j]);
		}
	}
}

void TicTacToe::Restart() {
	ClearField();
	computer_turn = 1 - computer_turn;
	turn_num = 0;
	free_cells = 9;
}


void TicTacToe::StartComputerGame() {
	ClearField();
	computer_turn = 1;
	turn_num = 0;
	free_cells = 9;
}


void TicTacToe::StartPlayerGame() {
	ClearField();
	computer_turn = 2;
	turn_num = 0;
	free_cells = 9;
}


void TicTacToe::CalculateTurn(int& i, int& j) {
	int num_cell = rand() % free_cells;
	int cell = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (!IsBusy(i, j)) {
				cell++;
			}
			if (cell - 1 == num_cell) {
				return;
			}
		}
	}
}

int TicTacToe::IsWin() {
	for (int i = 0; i < 3; i++) {
		if (GetCell(i, 0) == GetCell(i, 1) &&
			GetCell(i, 1) == GetCell(i, 2) &&
			GetCell(i, 0) != 0)
		{
			return GetCell(i, 0);
		}
		if (GetCell(0, i) == GetCell(1, i) &&
			GetCell(1, i) == GetCell(2, i) &&
			GetCell(0, i) != 0)
		{
			return GetCell(0, i);
		}
	}
	if (GetCell(0, 0) == GetCell(1, 1) &&
		GetCell(1, 1) == GetCell(2, 2) &&
		GetCell(0, 0) != 0)
	{
		return GetCell(0, 0);
	}
	if (GetCell(0, 2) == GetCell(1, 1) &&
		GetCell(1, 1) == GetCell(2, 0) &&
		GetCell(0, 2) != 0)
	{
		return GetCell(0, 2);
	}
	return 0;

}

int TicTacToe::GetCell(int i, int j) {
	WCHAR text[2];
	GetWindowText(buttons[i][j], text, 2);
	if (text[0] == L'\0') {
		return 0;
	}
	else if (text[0] == L'X') {
		return 1;
	}
	else if (text[0] == L'O') {
		return 2;
	}
	return true;
}

void TicTacToe::WinMessage(int player) {
	if (player == 0) {
		return;
	}
	if (player == 1) {
		MessageBox(parent, L"Крестики победили", L"Win", MB_OK);
	}
	else if (player == 2) {
		MessageBox(parent, L"Нолики победили", L"Win", MB_OK);
	}
	Restart();
}


void TicTacToe::ComputerTurn() {
	if (computer_turn == turn_num) {
		if (free_cells <= 0) {
			TieMessage();
			return;
		}
		Sleep(300);
		int i, j;
		CalculateTurn(i, j);
		MakeTurn(i, j, (turn_num == 0 ? L"X" : L"O"));
	}
}

void TicTacToe::TieMessage() {
	MessageBox(parent, L"Ничья", L"Tie", MB_OK);
	Restart();
}

void TicTacToe::PlayerFirstTurn() {
	computer_turn = 0;
}



