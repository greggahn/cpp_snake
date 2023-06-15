#pragma once
#include <curses.h>
#include "Drawable.h"
#include <deque>

enum Direction { // 방향을 enum으로 설정하여 4개 중 하나의 값만 가질 수 있게 함.
    up = 1,
    down = -1,
    left = 2,
    right = -2
};
// 슨네이크의 좌표와 아이콘 설정
class SnakePiece : public Drawable
{
public:
    SnakePiece() {
        this->x = this->y = 0;
        this->icon = '#';
    }
    SnakePiece(int y, int x) {
        this->y = y;
        this->x = x;
        this->icon = '#';
    }
};
//스네이크 움직임 제어 및 길이 변경
class Snake {
    Direction cur_dir; //현재 스네이크가 움직이는 방향
public: 
    std::deque<SnakePiece> prev_snake; //덱을 사용해 삭제 연산을 편하게 함
    Snake() { //초기 방향은 아래로 설정
        cur_dir = down;
    }
    void attachPiece(SnakePiece piece) { //길이 늘리기
        prev_snake.push_back(piece);
    }

    void dettachPiece() { //흔적 삭제하기
        prev_snake.pop_front();
    }

    void dettachBackPiece() { //poison아이템 먹었을 때
        prev_snake.pop_back();
    }
    SnakePiece tail() { 
        return prev_snake.front();
    }

    SnakePiece head() {
        return prev_snake.back();
    }

    Direction getDirection() { //현재 방향 반환
        return cur_dir;
    }

    void setDirection(Direction d) { //현재 방향과 같은 방향이 입력되지 않으면 방향을 새로 설정
        if (d != cur_dir) { cur_dir = d; }
    }

    SnakePiece nexthead() { //스네이크의 움직임 구현 부분
        int row = head().getY();
        int col = head().getX();

        switch (cur_dir)
        {
        case down:
            row++;
            break;

        case up:
            row--;
            break;

        case left:
            //col--;
            col--;
            break;

        case right:
            //col++;
            col++;
            break;
        }

        return SnakePiece(row, col);
    }

};