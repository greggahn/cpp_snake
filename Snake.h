#pragma once
#include <curses.h>
#include "Drawable.h"
#include <deque>

enum Direction { // ������ enum���� �����Ͽ� 4�� �� �ϳ��� ���� ���� �� �ְ� ��.
    up = 1,
    down = -1,
    left = 2,
    right = -2
};
// ������ũ�� ��ǥ�� ������ ����
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
//������ũ ������ ���� �� ���� ����
class Snake {
    Direction cur_dir; //���� ������ũ�� �����̴� ����
public: 
    std::deque<SnakePiece> prev_snake; //���� ����� ���� ������ ���ϰ� ��
    Snake() { //�ʱ� ������ �Ʒ��� ����
        cur_dir = down;
    }
    void attachPiece(SnakePiece piece) { //���� �ø���
        prev_snake.push_back(piece);
    }

    void dettachPiece() { //���� �����ϱ�
        prev_snake.pop_front();
    }

    void dettachBackPiece() { //poison������ �Ծ��� ��
        prev_snake.pop_back();
    }
    SnakePiece tail() { 
        return prev_snake.front();
    }

    SnakePiece head() {
        return prev_snake.back();
    }

    Direction getDirection() { //���� ���� ��ȯ
        return cur_dir;
    }

    void setDirection(Direction d) { //���� ����� ���� ������ �Էµ��� ������ ������ ���� ����
        if (d != cur_dir) { cur_dir = d; }
    }

    SnakePiece nexthead() { //������ũ�� ������ ���� �κ�
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