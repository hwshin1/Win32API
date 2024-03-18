//shape.h
#pragma once

typedef struct tagShape
{
	int type;			//1: 사각형, 2: 타원
	POINT pt;
}Shape;