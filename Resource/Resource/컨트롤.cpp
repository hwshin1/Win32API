//컨트롤.cpp
#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

// -----------------준비---------------------
#define IDC_EDIT1		1
#define IDC_BUTTON1		2
#define IDC_LISTBOX1	3
#define IDC_COMBOBOX1	4

HWND hEdit1, hButton1, hListBox1, hComBoBox1;
//--------------------------------------------

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	 hEdit1 = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, 10, 200, 25, hwnd, (HMENU)IDC_EDIT1, 0, 0);

	 hButton1 = CreateWindow(TEXT("button"), TEXT("클릭!"), WS_CHILD | WS_VISIBLE | WS_BORDER,
		 10, 50, 200, 25, hwnd, (HMENU)IDC_BUTTON1, 0, 0);

	 hListBox1 = CreateWindow(TEXT("ListBox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		 10, 100, 200, 200, hwnd, (HMENU)IDC_LISTBOX1, 0, 0);

	 hComBoBox1 = CreateWindow(TEXT("Combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
		 250, 100, 200, 200, hwnd, (HMENU)IDC_LISTBOX1, 0, 0);

	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == IDC_BUTTON1)
	{
		TCHAR buf[50];
		GetWindowText(hEdit1, buf, _countof(buf)); //sizeof 대신 _countof쓰자 'sizeof'대용
		//SetWindowText(hwnd, buf);
		SendMessage(hListBox1, LB_ADDSTRING, 0, (LPARAM)buf);
		SendMessage(hComBoBox1, CB_ADDSTRING, 0, (LPARAM)buf);
	}
	else if (LOWORD(wParam) == IDC_LISTBOX1)
	{
		if (HIWORD(wParam) == LBN_SELCHANGE)
		{
			TCHAR str[128];
			int i = SendMessage(hListBox1, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox1, LB_GETTEXT, i, (LPARAM)str);
			SetWindowText(hwnd, str);
		}
	}
	else if (LOWORD(wParam) == IDC_COMBOBOX1)
	{
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			TCHAR str[128];
			int i = (int)SendMessage(hComBoBox1, CB_GETCURSEL, 0, 0);
			SendMessage(hComBoBox1, CB_GETEDITSEL, i, (LPARAM)str);
			SetWindowText(hwnd, str);
		}
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		return OnCreate(hwnd, wParam, lParam);
	case WM_COMMAND:
		return OnCommand(hwnd, wParam, lParam);
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
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}