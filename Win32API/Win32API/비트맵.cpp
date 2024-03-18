//��Ʈ��
#pragma comment(linker, "/subsystem:windows")
#include <Windows.h>
#include <tchar.h>

LRESULT	CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);					//ȭ��DC
		HDC memDC = CreateCompatibleDC(hdc);	//�޸�DC

		HBITMAP bitmap = (HBITMAP)LoadImage(0, TEXT("sample.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (bitmap == 0)
		{
			MessageBox(0, TEXT("����"), TEXT("�˸�"), MB_OK);
			return 0;
		}

		//������� ���� ȹ��
		BITMAP bm;		//��Ʈ�� ����� �����ϴ� ����ü
		GetObject(bitmap, sizeof(bm), &bm);

		//-----------------------------------------------------------------------		
		SelectObject(memDC, bitmap);	//����
		TextOut(memDC, 5, 5, TEXT("�����ϳ���Ƽ��"), 10);
		//�� ���� ������ �ٲ�� ���� �ؽ�Ʈ�� ������ �״����� �̹����� �������//
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