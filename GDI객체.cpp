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
		HBRUSH brush = (HBRUSH)GetStockObject(GRAY_BRUSH);	//������ ����
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);	//������ ���� �տ� ��

		Rectangle(hdc, 10, 10, 100, 100);

		SelectObject(hdc, oldbrush);						//���� ����
		ReleaseDC(hwnd, hdc);
		return 0;
	}
	//���� ���
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);

		HBRUSH brush = CreateSolidBrush(RGB(255,0,0));		//������ ���� �����
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);	//������ ���� �տ� ��

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(0,255,0));
		HPEN oldpen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, 10, 10, 100, 100);

		DeleteObject(SelectObject(hdc, oldbrush));			//���� ������ ������ ���� �Ҹ�ó��
		DeleteObject(SelectObject(hdc, oldpen));

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
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = 0;

	RegisterClass(&wc);
	HWND hwnd = CreateWindowEx(0,
		TEXT("First"),
		TEXT("Hello"),
		WS_OVERLAPPEDWINDOW,
		0, 0, 500, 500,
		0, 0,
		hInst, 0);

	ShowWindow(hwnd, SW_SHOW);


	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		//TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}