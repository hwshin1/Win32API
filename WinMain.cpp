//WinMain 사용
#include <Windows.h>
#include <tchar.h>
#pragma comment(linker, "/subsystem:windows")

LRESULT	CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPTSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = 0;

	RegisterClass(&wc);
	HWND hwnd = CreateWindowEx(0,
		TEXT("First"), TEXT("Hello"),
		WS_OVERLAPPEDWINDOW &~ WS_THICKFRAME, //창 크기 조정 테두리
		CW_USEDEFAULT, 0, 500, 500, 0, 0, hInst, 0);

	ShowWindow(hwnd, SW_SHOW);

	MessageBox(0, TEXT("Hello, API"), TEXT("First"), MB_OKCANCEL | MB_ICONQUESTION);
	return 0;
}