//handler.h
#pragma once
#include "std.h"

LRESULT Oncreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT Ondestroy(HWND hwnd, WPARAM wParam, LPARAM lParam);

LRESULT OnTime(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnLbuttondown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT Onkeydown(HWND hwnd, WPARAM wParam, LPARAM lParam);

LRESULT Oncontextmenu(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT Oncommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnIntMenuPop(HWND hwnd, WPARAM wParam, LPARAM lParam);