#pragma once
#include <curses.h>
#include "Drawable.h"
// ������ ���̰� 1 �����ϴ� ������ Ŭ����
class GrowItem : public Drawable
{
public:
	GrowItem(int y, int x) {
		this->y = y;
		this->x = x;
		this->icon = 'A';
	}
};