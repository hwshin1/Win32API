//handler.cpp
#include "std.h"

LRESULT	OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	con_init();
	return 0;
}

LRESULT	OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT pt = { LOWORD(lParam), HIWORD(lParam) };
	if (wParam & MK_CONTROL)
	{
		con_Select(pt);
		return 0;
	}
	else if (wParam & MK_SHIFT)
	{
		con_Delete(pt);
		InvalidateRect(hwnd, 0, TRUE);
		return 0;
	}

	//현재 좌표 갱신
	con_set_curPoint(pt);
	//저장
	con_Insert();
	//무효화
	RECT rc = { pt.x, pt.y, pt.x + 100, pt.y + 100 };
	InvalidateRect(hwnd, &rc, FALSE);
	return 0;
}

LRESULT	OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	con_PrintAll(hdc);
	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int key = (int)wParam;

	con_set_curType(key);
	return 0;
}