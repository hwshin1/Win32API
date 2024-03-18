//모달.cpp
#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>
#include "resource.h"

typedef struct tagDATA
{
	COLORREF color;
}DATA;

//지식대화상자 Proc
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static DATA* pdata = NULL;
	static HWND hRed, hGreen, hBlue;

	switch (msg)
	{
	case WM_INITDIALOG:
	{
		pdata = (DATA*)lParam;

		SetDlgItemInt(hdlg, IDC_EDIT1, GetRValue(pdata->color), TRUE);
		SetDlgItemInt(hdlg, IDC_EDIT2, GetGValue(pdata->color), TRUE);
		SetDlgItemInt(hdlg, IDC_EDIT3, GetBValue(pdata->color), TRUE);

		//hRed = GetDlgItem(hdlg, )
	}
	}
}

COLORREF brush_color = RGB(0, 255, 0);
//부모 윈도우
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_NCLBUTTONDOWN:
	{
		DATA data;
		data.color = brush_color;
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
	wc.lpszMenuName = 0;
	wc.style = 0;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, TEXT("First"), TEXT("Hello"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 500, 0, 0, hInst, 0);

	ShowWindow(hwnd, SW_SHOW);
	//UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		//TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}