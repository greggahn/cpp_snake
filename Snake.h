#pragma once

#include "Drawable.h"
#include <deque>
using namespace std;
enum Direction
{
	go_up = -1,
	go_down = 1,
	go_left = -2,
	go_right = 2
};

class SnakePiece : public Drawable
{
public:
    SnakePiece()
    {
        this->x = this->y = 0;
        this->icon = '#';
    }

    SnakePiece(int y, int x)
    {
        this->x = x;
        this->y = y;
        this->icon = '#';
    }

    SnakePiece(int y, int x, chtype icon)
    {
        this->x = x;
        this->y = y;
        this->icon = icon;
    }

};

class Snake
{
	
	Direction cur_direction;

public:
	deque<SnakePiece> prev_pieces;

	Snake()
    {
        cur_direction = go_down;
    }
    void addPiece(SnakePiece piece)
    {
        prev_pieces.push_back(piece);
    }

    void removePiece()
    {
        prev_pieces.pop_front();
    }

    // eatPoison
    void removeBackPiece()
    {
        prev_pieces.pop_back();
    }
	SnakePiece tail()
    {
        return prev_pieces.front();
    }

    SnakePiece head()
    {
        return prev_pieces.back();
    }

    Direction getDirection()
    {
        return cur_direction;
    }

    void setDirection(Direction d)
    {
        cur_direction = d;
    }

	SnakePiece nexthead()
    {
        int row = head().getY();
        int col = head().getX();

        switch (cur_direction)
        {
        case go_down:
            row++;
            break;

        case go_up:
            row--;
            break;

        case go_left:
            col--;
            break;

        case go_right:
            col++;
            break;
        }

        return SnakePiece(row, col);
    }
};








