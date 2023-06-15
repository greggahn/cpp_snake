#pragma once
#include <curses.h>
#include "Drawable.h"
// 스네이크의 흔적을 지우거나 아이템을 사라지게 할 때 그 자리에 공백 출력하기 위한 Empty클래스
class Empty : public Drawable {
public:
    Empty(int y, int x) {
        this->x = x;
        this->y = y;
        this->icon = ' ';
    }
};