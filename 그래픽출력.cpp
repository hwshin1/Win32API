#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, 0, 0, 100, 100);
		Ellipse(hdc, 110, 0, 200, 100);

		SetPixel(hdc, 50, 50, RGB(255, 0, 0)); //빨강 점
		MoveToEx(hdc, 100, 200, 0);
		LineTo(hdc, 300, 200);
		LineTo(hdc, 300, 400);

		POINT arr[3] = { {50,0},{100,100},{0,100} };
		Polygon(hdc, arr, 3);
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		HDC hdc = GetDC(hwnd);
		POINTS pt = MAKEPOINTS(lParam);
		TCHAR str[50];
		wsprintf(str, TEXT("%d:%d"), pt.x, pt.y);

		InvalidateRect(hwnd, 0, TRUE); //무효화
		UpdateWindow(hwnd); // 큐를 즉각 실행
		TextOut(hdc, 300, 10, str, _tcslen(str));
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

	HWND hwnd = CreateWindowEx(0, TEXT("First"), TEXT("Hello"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 500, 0, 0, hInst, 0);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		//TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}