#pragma once
#include <curses.h>

class Scoreboard
{
	WINDOW *score_win;
public:
	Scoreboard(){}

	Scoreboard(int width, int y, int x)
	{
		score_win = newwin(15, width+3, y, x+5);;
	}

	void initialize(int maxLength)
	{
		clear();
		box(score_win, '|', '-');
		addAt(0, 0, '*');
		addAt(0, 42, '*');
		addAt(14, 0, '*');
		addAt(14, 42, '*');


		mvwprintw(score_win, 1, 1, "Scoreboard:");
		mvwprintw(score_win, 3, 1, "B : (0) / (%d)", maxLength);
		mvwprintw(score_win, 4, 1, "+ : 0");
		mvwprintw(score_win, 5, 1, "- : 0");
		mvwprintw(score_win, 6, 1, "G : 0");
		mvwprintw(score_win, 7, 1, "R : 0");
		wrefresh(score_win);
		refresh();
	}
	void wdelwin() {
		delwin(score_win);
	};
	void addAt(int y, int x, chtype ch)
	{
		mvwaddch(score_win, y, x, ch);
	}

	void updateGrowthScore(int growthScore)
	{
		mvwprintw(score_win, 4, 1, "+ : %d", growthScore);
	}
	void updatePoisonScore(int poisonScore)
	{
		mvwprintw(score_win, 5, 1, "- : %d", poisonScore);
	}
	void updateGateScore(int gateScore)
	{
		mvwprintw(score_win, 6, 1, "G : %d", gateScore);
	}
	void updateReverseScore(int reverseScore)
	{
		mvwprintw(score_win, 7, 1, "R : %d", reverseScore);
	}
	void updateLength(int currLength)
	{
		mvwprintw(score_win, 3, 1, "B : (%d)", currLength);
	}

	void clear()
	{
		wclear(score_win);
	}

	void refresh()
	{
		wrefresh(score_win);
	}
};
