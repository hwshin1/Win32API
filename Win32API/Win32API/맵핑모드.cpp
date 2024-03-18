//¸ÊÇÎ¸ðµå.cpp
#pragma comment(linker, "/subsystem:windows")
#include <Windows.h>
#include <tchar.h>

LRESULT	CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);
		Rectangle(hdc, 10, 10, 10 + 100, 10 + 100);	//100*100
		ReleaseDC(hwnd, hdc);

		return 0;
	}
	case WM_LBUTTONUP:
	{
		HDC hdc = GetDC(hwnd);
		SetMapMode(hdc, MM_LOMETRIC);				//0.1mm

		Rectangle(hdc, 200, -10, 200 + 100, -(10 + 100));	//100*100

		ReleaseDC(hwnd, hdc);
		return 0;
	}

	case WM_RBUTTONDOWN:
	{
		POINT pt = { LOWORD(lParam), HIWORD(lParam) };	//¹°¸®ÁÂÇ¥(ÀåÄ¡ÁÂÇ¥)-ÇÈ¼¿
		HDC hdc = GetDC(hwnd);
		SetMapMode(hdc, MM_LOMETRIC);

		//¹°¸®ÁÂÇ¥ --> ³í¸®ÁÂÇ¥ º¯È¯
		DPtoLP(hdc, &pt, 1);

		Rectangle(hdc, pt.x, pt.y, pt.x + 100, pt.y + 100);	//³í¸®ÁÂÇ¥(0.1mm)

		ReleaseDC(hwnd, hdc);
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
	wc.lpszMenuName = 0;
	wc.style = 0;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, TEXT("First"), TEXT("Hello"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 500,
		0, 0,
		hInst, 0);

	ShowWindow(hwnd, SW_SHOW);
	//UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		//TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}