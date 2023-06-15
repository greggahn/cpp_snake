#include <curses.h>
#include <iostream>
#include "Board.h"
#include "SnakeGame.h"

#define BOARD_DIM 20
#define BOARD_ROWS 30
#define BOARD_COLS 30

int main() {
    initscr();
    refresh();
    cbreak;  //Ű���� �Է��� ���� �� �ѹ��� �� Ű�� �ޱ� ���ؼ�

    noecho(); //Ŀ�� �Ⱥ��̰�
    curs_set(0);

    Board board(BOARD_ROWS, BOARD_COLS); //������ ȣ�� �� ��ü ����
    board.initialize(); 

    SnakeGame game(BOARD_ROWS, BOARD_COLS);

    while (!game.isOver()) {
        game.processInput();  //Ű����� ���� �Է¹ް� ó���ϱ�
        game.updateState(); //���� ���� ������Ʈ
        game.redraw();
    }
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    attron(COLOR_PAIR(1));
    mvprintw(20, 20, "GAME OVER"); //���� ���� ���� ���
    refresh();
    
    getch();
    endwin();

    return 0;
}