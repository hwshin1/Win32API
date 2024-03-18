//control.cpp
#include "std.h"

Shape cur_shape;
vector<Shape*> shapes;

COLORREF color = RGB(0, 255, 0);

HWND hEdit1, hButton1, hListBox1, hComBoBox1;

void con_init()
{
	cur_shape.type = 1;
	cur_shape.pt.x = 10;
	cur_shape.pt.y = 10;
}

void con_curpoint(POINT pt)
{
	cur_shape.pt = pt;
}

void con_Insert()
{
	Shape* pshape = (Shape*)malloc(sizeof(Shape));
	pshape->type = cur_shape.type;
	pshape->pt = cur_shape.pt;
	shapes.push_back(pshape);
}

void con_select(POINT pt)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		Shape* p = shapes[i];
		RECT rc = { p->pt.x, p->pt.y, p->pt.x + 30, p->pt.y + 30 };
		if (PtInRect(&rc, pt) == TRUE)
		{
			MessageBox(0, TEXT("찾음"), TEXT("확인"), MB_OK);
		}
	}
}

void con_delete(POINT pt)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		Shape* p = shapes[i];
		RECT rc = { p->pt.x, p->pt.y, p->pt.x + 30, p->pt.y + 30 };
		if (PtInRect(&rc, pt) == TRUE)
		{
			shapes.erase(shapes.begin() + i);
			free(p);
			return;
		}
	}
}

void con_paint(HDC hdc)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		Shape* p = shapes[i];
		if (p->type == 1)
		{
			Rectangle(hdc, p->pt.x, p->pt.y, p->pt.x + 30, p->pt.y + 30);
		}
		else if (p->type == 2)
		{
			Ellipse(hdc, p->pt.x, p->pt.y, p->pt.x + 30, p->pt.y + 30);
		}
	}
}

void con_curType(int key)
{
	if (key == 'R')
	{
		cur_shape.type = 1;
	}
	else if (key == 'E')
	{
		cur_shape.type = 2;
	}
}

void con_brush(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

	for (int i = 0; i < shapes.size(); i++)
	{
		Shape* p = shapes[i];
		if (p->type == 1)
		{
			Rectangle(hdc, p->pt.x, p->pt.y, p->pt.x + 30, p->pt.y + 30);
		}
		else if (p->type == 2)
		{
			Ellipse(hdc, p->pt.x, p->pt.y, p->pt.x + 30, p->pt.y + 30);
		}
	}
	DeleteObject(SelectObject(hdc, oldbrush));
}

void con_Menu(HWND hwnd, POINT pt)
{
	HMENU hMenu = GetMenu(hwnd);
	HMENU hSubMenu = GetSubMenu(hMenu, 1);

	TrackPopupMenu(hSubMenu, TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, 0);
}

void con_command(HWND hwnd, WPARAM wParam)
{
	if (LOWORD(wParam) == ID_40002)
	{
		color = RGB(0, 255, 0); InvalidateRect(hwnd, 0, FALSE);
	}
	else if (LOWORD(wParam) == ID_40003)
	{
		color = RGB(155, 39, 67); InvalidateRect(hwnd, 0, FALSE);
	}
	else if (LOWORD(wParam) == ID_40004)
	{
		color = RGB(0, 0, 255); InvalidateRect(hwnd, 0, FALSE);
	}
	else if (LOWORD(wParam) == ID_FILE_EXIT)
	{
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

void con_EnableMenu(HMENU hMenu)
{
	EnableMenuItem(hMenu, ID_40002, color == RGB(0, 255, 0) ? MF_GRAYED : MF_ENABLED);
	EnableMenuItem(hMenu, ID_40003, color == RGB(155, 39, 67) ? MF_GRAYED : MF_ENABLED);
	EnableMenuItem(hMenu, ID_40004, color == RGB(0, 0, 255) ? MF_GRAYED : MF_ENABLED);
}

void con_control(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	hEdit1 = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, 10, 200, 25, hwnd, (HMENU)IDC_EDIT1, 0, 0);

	hButton1 = CreateWindow(TEXT("button"), TEXT("클릭!"), WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, 50, 200, 25, hwnd, (HMENU)IDC_BUTTON1, 0, 0);

	hListBox1 = CreateWindow(TEXT("ListBox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		10, 100, 200, 200, hwnd, (HMENU)IDC_LISTBOX1, 0, 0);

	hComBoBox1 = CreateWindow(TEXT("Combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
		250, 100, 200, 200, hwnd, (HMENU)IDC_LISTBOX1, 0, 0);
}

void con_Time(HWND hwnd)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR buf[50];
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("tt h시 m분 s초"), buf, 50);
	SetWindowText(hwnd, buf);
}