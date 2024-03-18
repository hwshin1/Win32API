//그리기모드 선긋기
#pragma comment (linker, "/subsystem:windows")
#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		start = end = MAKEPOINTS(lParam);
		SetCapture(hwnd);

		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (GetCapture() == hwnd)
		{
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOT);

			MoveToEx(hdc, start.x, start.y, NULL);
			LineTo(hdc, end.x, end.y);

			end = MAKEPOINTS(lParam);
			MoveToEx(hdc, start.x, start.y, NULL);
			LineTo(hdc, end.x, end.y);

			ReleaseDC(hwnd, hdc);
		}
		return 0;
	}
	case WM_LBUTTONUP:
	{
		HDC hdc = GetDC(hwnd);

		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);

		ReleaseDC(hwnd, hdc);
		ReleaseCapture();
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