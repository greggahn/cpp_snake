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
    cbreak;  //키보드 입력을 받을 때 한번에 한 키만 받기 위해서

    noecho(); //커서 안보이게
    curs_set(0);

    Board board(BOARD_ROWS, BOARD_COLS); //생성자 호출 및 객체 생성
    board.initialize(); 

    SnakeGame game(BOARD_ROWS, BOARD_COLS);

    while (!game.isOver()) {
        game.processInput();  //키보드로 방향 입력받고 처리하기
        game.updateState(); //게임 상태 업데이트
        game.redraw();
    }
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    attron(COLOR_PAIR(1));
    mvprintw(20, 20, "GAME OVER"); //게임 종료 문구 출력
    refresh();
    
    getch();
    endwin();

    return 0;
}