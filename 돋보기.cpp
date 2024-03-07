//돋보기.cpp
#pragma comment(linker, "/subsystem:windows")
#include <Windows.h>
#include <tchar.h>

LRESULT	CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		SetCapture(hwnd);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		ReleaseCapture();
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		POINT pt;
		GetCursorPos(&pt);					//스크린좌표

		if (GetCapture() == hwnd)
		{
			HDC hdcDisplay = GetDC(0);		//화면DC
			HDC hdcClient = GetDC(hwnd);	//출력DC

			StretchBlt(hdcClient, 0, 0, cxClient, cyClient,			//출력할 장소의 정보 
				hdcDisplay, pt.x, pt.y, cxClient / 2, cyClient / 2, //원본 DC
				SRCCOPY);											//원본 DC를 그대로 복사

			ReleaseDC(hwnd, hdcDisplay);
			ReleaseDC(hwnd, hdcClient);
		}
		return 0;
	}
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

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