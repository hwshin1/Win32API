//handler.h
#pragma once
#include "std.h"

LRESULT	OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT	OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT	OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT	OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam);