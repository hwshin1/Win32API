//handler.cpp
#include "std.h"

LRESULT Oncreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	con_init();
	con_control(hwnd, wParam, lParam);
	return 0;
}

LRESULT Ondestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnTime(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	con_Time(hwnd);
	return 0;
}

LRESULT OnLbuttondown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { LOWORD(lParam), HIWORD(lParam) };
	if (wParam & MK_CONTROL)
	{
		con_select(pt);
		return 0;
	}
	else if (wParam & MK_SHIFT)
	{
		con_delete(pt);
		InvalidateRect(hwnd, 0, TRUE);
		return 0;
	}

	con_curpoint(pt);

	con_Insert();

	RECT rc = { pt.x, pt.y, pt.x + 100, pt.y + 100 };
	InvalidateRect(hwnd, &rc, FALSE);
	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	con_paint(hdc);
	con_brush(hdc);

	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT Onkeydown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int key = (int)wParam;
	con_curType(key);
	return 0;
}

LRESULT Oncontextmenu(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { LOWORD(lParam), HIWORD(lParam) };
	con_Menu(hwnd, pt);

	return 0;
}

LRESULT Oncommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	con_command(hwnd, wParam);
	return 0;
}

LRESULT OnIntMenuPop(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu = GetMenu(hwnd);
	con_EnableMenu(hMenu);
	return 0;
}