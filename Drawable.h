#pragma once
// 스네이크, 아이템 등의 좌표와 아이콘 설정 및 반환
class Drawable {
public :
    Drawable() {
        y = x = 0;
        icon = ' ';
    }

    Drawable(int y, int x, chtype ch) {
        this->y = y;
        this->x = x;
        this->icon = ch;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
    
    chtype getIcon() {
        return icon;
    }

protected:
    int y, x;
    chtype icon;
};
