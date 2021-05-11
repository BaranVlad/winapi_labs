#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include <Windows.h>
#include "resource.h"
#include <string>
#include <vector>

#define CELL_RECT 60
#define TABLE_DAYS 6
#define TABLE_PAIRS 5
#define TABLE_DAY_OFFSET 20

class Schedule
{
public:
	struct Cell {
		bool is_empty_ = false;

		WCHAR type_[100];
		WCHAR subject_name_[100];
		WCHAR class_num_[100];

		Cell(const WCHAR type[100], const WCHAR subject_name[100], const WCHAR class_num[100]);
	};
private:
	RECT table_rect;
	std::vector<Cell> table[TABLE_DAYS];

	int cell_height;
	int cell_width;

	void DrawCell(HDC hdc, const Cell& cell, int x, int y);
public:
	Schedule();

	void SetRect(RECT rect);
	void AddSubject(int day, const WCHAR type[100], const WCHAR subject_name[100], const WCHAR class_num[100]);
	void AddSubject(int day);
	void Draw(HDC hdc);
	void DrawDays(HDC hdc);
};

#endif

