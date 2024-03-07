//비트맵
#pragma comment(linker, "/subsystem:windows")
#include <Windows.h>
#include <tchar.h>

LRESULT	CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);					//화면DC
		HDC memDC = CreateCompatibleDC(hdc);	//메모리DC

		HBITMAP bitmap = (HBITMAP)LoadImage(0, TEXT("sample.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (bitmap == 0)
		{
			MessageBox(0, TEXT("오류"), TEXT("알림"), MB_OK);
			return 0;
		}

		//헤더에서 정보 획득
		BITMAP bm;		//비트맵 헤더를 저장하는 구조체
		GetObject(bitmap, sizeof(bm), &bm);

		//-----------------------------------------------------------------------		
		SelectObject(memDC, bitmap);	//선택
		TextOut(memDC, 5, 5, TEXT("대전하나시티즌"), 10);
		//위 둘이 문장이 바뀌면 먼저 텍스트가 나가고 그다음에 이미지가 덮어버림//
		//------------------------------------------------------------------------

		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmWidth,
			memDC, 0, 0, SRCCOPY);

		ReleaseDC(hwnd, hdc);
		DeleteDC(memDC);
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