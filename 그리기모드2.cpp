//그리기모드 도형 그리기
#pragma comment(linker, "/subsystem:windows")
#include <Windows.h>
#include <tchar.h>

LRESULT	CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		start = end = MAKEPOINTS((lParam));
		SetCapture(hwnd);

		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (GetCapture() == hwnd)
		{
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOTXORPEN);

			HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH); //투명 브러쉬
			HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

			HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HPEN oldpen = (HPEN)SelectObject(hdc, pen);

			//기존 라인 지우기		
			Rectangle(hdc, start.x, start.y, end.x, end.y);

			//새로운 라인 그리기
			end = MAKEPOINTS(lParam);
			Rectangle(hdc, start.x, start.y, end.x, end.y);

			SelectObject(hdc, oldbrush);
			DeleteObject(SelectObject(hdc, oldpen));
			ReleaseDC(hwnd, hdc);
		}
		return 0;
	}
	case WM_LBUTTONUP:
	{
		HDC hdc = GetDC(hwnd);

		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HPEN oldpen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, start.x, start.y, end.x, end.y);

		SelectObject(hdc, oldbrush);
		DeleteObject(SelectObject(hdc, oldpen));

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