//control.h
#pragma once
void con_init();
void con_Insert();
void con_PrintAll(HDC hdc);
void con_set_curPoint(POINT pt);
void con_set_curType(int key);
void con_Select(POINT pt);
void con_Delete(POINT pt);