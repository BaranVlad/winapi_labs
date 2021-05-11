#include "schedule.h"

#pragma warning(disable:4996)

const WCHAR days[6][100] = {
	L"Понедельник",
	L"Вторник",
	L"Среда",
	L"Четверг",
	L"Пятница",
	L"Суббота",
};


Schedule::Schedule()
{}

void Schedule::AddSubject(int day, const WCHAR type[100], const WCHAR subject_name[100], const WCHAR class_num[100]) {
	table[day].push_back(Cell(type, subject_name, class_num));
}

void Schedule::AddSubject(int day) {
	table[day].push_back(Cell(L"", L"", L""));
	table[day][table[day].size() - 1].is_empty_ = true;
}

Schedule::Cell::Cell(const WCHAR cell_type[100], const WCHAR subject_name[100], const WCHAR class_num[100]) {
	wcscpy(type_, cell_type);
	wcscpy(subject_name_, subject_name);
	wcscpy(class_num_, class_num);
}

void Schedule::Draw(HDC hdc) {

	for (int i = 0; i < TABLE_DAYS; i++) {
		for (int j = 0; j < table[i].size(); j++) {
			if (table[i][j].is_empty_) {
				continue;
			}
			DrawCell(hdc, table[i][j], table_rect.left + TABLE_DAY_OFFSET + j * cell_width, table_rect.top + i * cell_height);
		}
	}
	DrawDays(hdc);
}

void Schedule::DrawDays(HDC hdc) {
	HFONT vFont = CreateFont(12, 0, 900, 0, FW_BOLD, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Arial");
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);
	SelectObject(hdc, vFont);
	SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
	
	for (int i = 0; i < TABLE_DAYS; i++) {
		Rectangle(hdc, table_rect.left, table_rect.top + i * cell_height, table_rect.left + TABLE_DAY_OFFSET, table_rect.top + (i + 1) * cell_height);
		TextOut(hdc, table_rect.left + TABLE_DAY_OFFSET / 2 + 2, table_rect.top + i * cell_height + cell_height / 2, days[i], wcslen(days[i]));
	}

	DeleteObject(vFont);
	DeleteObject(brush);
}

void Schedule::DrawCell(HDC hdc, const Cell& cell, int x, int y) {
	HBRUSH brush;
	if (wcscmp(cell.type_, L"Лекция") == 0) {
		brush = CreateSolidBrush(RGB(250, 128, 114));
	}
	else if (wcscmp(cell.type_, L"Практика") == 0) {
		brush = CreateSolidBrush(RGB(255, 165, 0));
	}
	else if (wcscmp(cell.type_, L"Физ-ра") == 0) {
		brush = CreateSolidBrush(RGB(200, 255, 100));
	}
	else {
		brush = CreateSolidBrush(RGB(100, 100, 100));
	}
	SelectObject(hdc, brush);
	SetBkMode(hdc, TRANSPARENT);
	Rectangle(hdc, x, y, x + cell_width, y + cell_height);

	SetTextAlign(hdc, TA_CENTER | TA_TOP);
	TextOut(hdc, x + cell_width / 2, y + 1, cell.type_, wcslen(cell.type_));
	SetTextAlign(hdc, TA_CENTER | TA_BOTTOM);
	TextOut(hdc, x + cell_width / 2, y + cell_height - 1, cell.class_num_, wcslen(cell.class_num_));
	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
	TextOut(hdc, x + cell_width / 2, y + cell_height / 2, cell.subject_name_, wcslen(cell.subject_name_));
	DeleteObject(brush);
}

void Schedule::SetRect(RECT rect) {
	table_rect = rect;
	cell_height = (rect.bottom - rect.top) / TABLE_DAYS;
	cell_width = (rect.right - rect.left) / TABLE_PAIRS;
}
