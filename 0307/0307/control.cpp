//control.cpp
#include "std.h"

Shape cur_shape;
vector<Shape*> shapes; //shape 주소 저장

void con_set_curPoint(POINT pt)
{
	cur_shape.pt = pt;
}

void con_set_curType(int key)
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

void con_Select(POINT pt)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		Shape* p = shapes[i];
		RECT rc = { p->pt.x, p->pt.y, p->pt.x + 50, p->pt.y + 50 };
		if (PtInRect(&rc, pt) == TRUE)
		{
			MessageBox(0, TEXT("찾음"), TEXT("확인"), MB_OK);
			return;
		}
	}
}

void con_Delete(POINT pt)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		Shape* p = shapes[i];
		RECT rc = { p->pt.x, p->pt.y, p->pt.x + 50, p->pt.y + 50 };
		if (PtInRect(&rc, pt) == TRUE)
		{
			shapes.erase(shapes.begin() + i);
			free(p);
			return;
		}
	}
}

void con_init()
{
	cur_shape.type = 1;
	cur_shape.pt.x = 10;
	cur_shape.pt.y = 20;
}

void con_Insert()
{
	Shape* pshape = (Shape*)malloc(sizeof(Shape));
	pshape->type = cur_shape.type;
	pshape->pt = cur_shape.pt;
	shapes.push_back(pshape);
}

void con_PrintAll(HDC hdc)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		Shape* p = shapes[i];
		if (p->type == 1) {
			Rectangle(hdc, p->pt.x, p->pt.y, p->pt.x + 50, p->pt.y + 50);
		}
		else if (p->type == 2) {
			Ellipse(hdc, p->pt.x, p->pt.y, p->pt.x + 50, p->pt.y + 50);
		}
	}
}