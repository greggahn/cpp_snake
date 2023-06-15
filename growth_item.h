#pragma once
#include <curses.h>
#include "Drawable.h"
// 먹으면 길이가 1 증가하는 아이템 클래스
class GrowItem : public Drawable
{
public:
	GrowItem(int y, int x) {
		this->y = y;
		this->x = x;
		this->icon = 'A';
	}
};