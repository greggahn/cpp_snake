#pragma once
#include <curses.h>
#include "Drawable.h"
// ������ũ�� ������ ����ų� �������� ������� �� �� �� �ڸ��� ���� ����ϱ� ���� EmptyŬ����
class Empty : public Drawable {
public:
    Empty(int y, int x) {
        this->x = x;
        this->y = y;
        this->icon = ' ';
    }
};