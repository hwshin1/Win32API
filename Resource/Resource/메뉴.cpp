//¸Þ´º.cpp
#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>
#include "resource.h"

COLORREF color = RGB(255, 0, 0);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CONTEXTMENU:
	{
		HMENU hMenu = GetMenu(hwnd);
		//HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU2));
		HMENU hSubMenu = GetSubMenu(hMenu, 1);

		POINT pt = { LOWORD(lParam), HIWORD(lParam) }; //½ºÅ©¸° ÁÂÇ¥
		TrackPopupMenu(hSubMenu, TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, 0);
		return 0;
	}
	case WM_INITMENUPOPUP:
	{
		HMENU hMenu = GetMenu(hwnd);									//ºÎÂøµÈ ¸Þ´ºÀÇ ÇÚµé È¹µæ
		EnableMenuItem(hMenu, ID_40002, color == RGB(255, 0, 0) ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_40003, color == RGB(0, 0, 255) ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_40004, color == RGB(0, 255, 0) ? MF_GRAYED : MF_ENABLED);
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_40002) {
			color = RGB(255, 0, 0); InvalidateRect(hwnd, 0, FALSE);		//»¡
		}
		else if (LOWORD(wParam) == ID_40003) {
			color = RGB(0, 0, 255); InvalidateRect(hwnd, 0, FALSE);		//ÆÄ
		}
		else if (LOWORD(wParam) == ID_40004) {
			color = RGB(0, 255, 0); InvalidateRect(hwnd, 0, FALSE);		//³ì
		}
		else if (LOWORD(wParam) == ID_FILE_EXIT) {
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		HBRUSH brush = CreateSolidBrush(color);
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

		Rectangle(hdc, 5, 5, 5 + 100, 5 + 100);
		DeleteObject(SelectObject(hdc, oldbrush));

		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = 0;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, TEXT("First"), TEXT("Hello"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 500, 0, 0, hInst, 0);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}