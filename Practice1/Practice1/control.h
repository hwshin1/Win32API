//control.h
#pragma once
#include "std.h"

void con_init();
void con_curpoint(POINT pt);
void con_Insert();
void con_select(POINT pt);
void con_delete(POINT pt);
void con_paint(HDC hdc);
void con_curType(int key);
void con_brush(HDC hdc);
void con_Menu(HWND hwnd, POINT pt);
void con_command(HWND hwnd, WPARAM wParam);
void con_EnableMenu(HMENU hMenu);
void con_control(HWND hwnd, WPARAM wParam, LPARAM lParam);
void con_Time(HWND hwnd);