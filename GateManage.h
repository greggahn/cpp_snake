#include "Gate.h"
#include "Snake.h"
#include "map.h"
#include <iostream>
#include <curses.h>
#include <cstdlib>

class GateManage
{
public:
    Gate *gate1;
    Gate *gate2;

    void getRandom(int &y, int &x, Map map[30][30]) // 1인 좌표 찾는 함수 (Gate 만들기 용도)
    {
        int maxY = 30;
        int maxX = 30;

        do
        {
            y = rand() % maxY;
            x = rand() % maxX;
        } while (map[y][x] != '1')
    }

    void createGate(Map map[30][30]) // 무슨 스테이지에서 할건지 받아야함
    {
        int y, x;
        getRandom(y, x, map);
        gate1 = new Gate(y, x);
        map[y][x] = 'G';

        // 게이트 2의 위치 결정
        int gate2_y, gate2_x;
        do
        {
            getRandom(gate2_y, gate2_x, map);
        } while (gate2_y == y && gate2_x == x); // 게이트 2의 위치가 게이트 1과 중복되는 경우 다시 랜덤으로 좌표를 선택

        gate2 = new Gate(gate2_y, gate2_x);
        map[gate2_y][gate2_x] = 'G';
    }

    void deleteGate(Map map[30][30])
    {
        map[gate1->y][gate1->x] = '1';
        map[gate2->y][gate2->x] = '1';

        delete gate1;
        delete gate2;
    }

    SnakePiece meetgate(Map map[30][30], Gate g) // 게이트에서 나올때 방향 설정
    {
        Gate exit;

    if (g == *gate1)    // 출구가 gate1
    {
        exit = *gate2;
    }
    else                // 출구가 gate2
    {
        exit = *gate1;
    }

    Direction dir = snake::getDirection();

    int row = exit.getY();
    int col = exit.getX();

    if (exit.getY() == 0) // 상단 벽
    {
        dir = down;
    }
    else if (exit.getY() == 29) // 하단 벽
    {
        dir = up;
    }
    else if (exit.getX() == 0) // 좌측 벽
    {
        dir = right;
    }
    else if (exit.getX == 29) // 우측 벽
    {
        dir = left;
    }
    else // 가운데에 있는 벽
    {
        Direction entryDir = snake::getDirection();

        // 진입 방향과 일치하는 방향이 우선
        if (entryDir == up || entryDir == down)
        {
            if (map[row][col - 1] != '1')
            {
                dir = left;
            }
            else if (map[row][col + 1] != '1')
            {
                dir = right;
            }
            else if (entryDir == up && map[row + 1][col] != '1')
            {
                dir = down;
            }
            else if (entryDir == down && map[row - 1][col] != '1')
            {
                dir = up;
            }
            else
            {
                // 진입 방향의 시계방향으로 회전
                if (entryDir == up)
                {
                    dir = right;
                }
                else
                {
                    dir = left;
                }
            }
        }
        else // entryDir == left || entryDir == right
        {
            if (map[row - 1][col] != '1')
            {
                dir = up;
            }
            else if (map[row + 1][col] != '1')
            {
                dir = down;
            }
            else if (entryDir == left && map[row][col + 1] != '1')
            {
                dir = right;
            }
            else if (entryDir == right && map[row][col - 1] != '1')
            {
                dir = left;
            }
            else
            {
                // 진입 방향의 역시계방향으로 회전
                if (entryDir == left)
                {
                    dir = down;
                }
                else
                {
                    dir = up;
                }
            }
        }
    }

    snake::setDirection(dir);

    switch (dir)
    {
        case down:
            col++;
            break;

        case up:
            col--;
            break;

        case left:
            row--;
            break;

        case right:
            row++;
            break;
    }

    return SnakePiece(row, col);
}
};
