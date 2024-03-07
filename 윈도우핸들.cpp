//윈도우 핸들
#include <Windows.h>
#include <tchar.h>
#include <locale.h> // 한글 지원
#include <stdio.h>

int main()
{
	HWND hwnd = FindWindow(0, TEXT("계산기"));
	if (hwnd == 0)
	{
		printf("계산기를 먼저 실행\n");
		return 0;
	}
	TCHAR msg[256];
	wsprintf(msg, TEXT("%d"), (int)hwnd);
	_wsetlocale(LC_ALL, _T("korean"));  //한글 지원
	_tprintf(TEXT("%s\n"), msg);

	MessageBox(0, TEXT("계산기이동"), TEXT("확인"), MB_OK); //핸들 사용
	MoveWindow(hwnd, 0, 0, 300, 300, TRUE);
	return 0;
}