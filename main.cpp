#include <curses.h>
#include <time.h>
#include <iostream>

#include "Board.h"
#include "SnakeGame.h"
#include "Drawable.h"

#define BOARD_DIM 20
#define BOARD_ROWS 30
#define BOARD_COLS 30

int main()
{
	initscr();
	refresh();
	cbreak;

	noecho();
	curs_set(0);
  	
 
	SnakeGame game(BOARD_ROWS, BOARD_COLS);
  	mvprintw(0, 8, "C++ Programming - Section 3 - Group 8");
  	mvprintw(4, 15, "snake game project");
  	mvprintw(6, 15, "20222222 AHN HYOUN JONG");
  	mvprintw(7, 15, "20222222 KIM HYE WON");
  	mvprintw(8, 15, "20222222 OH JU YEOP");
  	mvprintw(9, 15, "20192062 PARK JEONG BIN");
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(1));
    mvprintw(20, 15, "Press 'A' To Start Game");
    attroff(COLOR_PAIR(1));

	getch();
	while (!game.isOver())
	{
		game.processInput();
		game.updateState();
		game.redraw();

	}
	initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    attron(COLOR_PAIR(1));
    mvprintw(20, 10, "GAME OVER"); //
    refresh();
    
    getch();
    endwin();

	return 0;
}