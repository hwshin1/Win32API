//������ �ڵ�
#include <Windows.h>
#include <tchar.h>
#include <locale.h> // �ѱ� ����
#include <stdio.h>

int main()
{
	HWND hwnd = FindWindow(0, TEXT("����"));
	if (hwnd == 0)
	{
		printf("���⸦ ���� ����\n");
		return 0;
	}
	TCHAR msg[256];
	wsprintf(msg, TEXT("%d"), (int)hwnd);
	_wsetlocale(LC_ALL, _T("korean"));  //�ѱ� ����
	_tprintf(TEXT("%s\n"), msg);

	MessageBox(0, TEXT("�����̵�"), TEXT("Ȯ��"), MB_OK); //�ڵ� ���
	MoveWindow(hwnd, 0, 0, 300, 300, TRUE);
	return 0;
}