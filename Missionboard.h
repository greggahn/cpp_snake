#pragma once
#include <curses.h>

class Missionboard {
	WINDOW* mission_win;

public:


	Missionboard() {}

	Missionboard(int width, int y, int x)
	{
		mission_win = newwin(15, width + 3, 15, x+5);
	}

	void initialize(int trGrowthScore, int trPoisonScore, int trGateScore,int trreverse, int trLength)
	{
		clear();
		box(mission_win, '|', '-');
		addAt(0, 0, '*');
		addAt(0, 42, '*');
		addAt(14, 0, '*');
		addAt(14, 42, '*');


		mvwprintw(mission_win, 1, 1, "Missionboard:");
		mvwprintw(mission_win, 3, 1, "B : %d ( )", trLength);
		mvwprintw(mission_win, 4, 1, "+ : %d ( )", trGrowthScore);
		mvwprintw(mission_win, 5, 1, "- : %d ( )", trPoisonScore);
		mvwprintw(mission_win, 6, 1, "G : %d ( )", trGateScore);
		mvwprintw(mission_win, 7, 1, "G : %d ( )", trGateScore);
		wrefresh(mission_win);
		refresh();
	}
	void addAt(int y, int x, chtype ch)
	{
		mvwaddch(mission_win, y, x, ch);
	}
	void wdelwin() {
		delwin(mission_win);
	};


	void lengthCheck() { 
		if (mvwinch(mission_win, 3, 8) == ' ') {
			mvwprintw(mission_win, 3, 8, "v");
			wrefresh(mission_win);
	}
		else if (mvwinch(mission_win, 3, 9) == ' ') {
			mvwprintw(mission_win, 3, 9, "v");
			wrefresh(mission_win);
		}
	}
	void growthScoreCheck() {
		if (mvwinch(mission_win, 4, 10) == ' ') {
			mvwprintw(mission_win, 4, 10, "v");
			wrefresh(mission_win);
		}
		else if (mvwinch(mission_win, 4, 11) == ' ') {
			mvwprintw(mission_win, 4, 11, "v");
			wrefresh(mission_win);
		}
	}
	void poisonScoreCheck() {
		if (mvwinch(mission_win, 5, 10) == ' ') {
			mvwprintw(mission_win, 5, 10, "v");
			wrefresh(mission_win);
		}
		else if (mvwinch(mission_win, 5, 11) == ' ') {
			mvwprintw(mission_win, 5, 11, "v");
			wrefresh(mission_win);
		}
	}
	void gateScoreCheck() { 
		if (mvwinch(mission_win, 6, 10) == ' ') {
			mvwprintw(mission_win, 6, 10, "v");
			wrefresh(mission_win);
		}
		else if (mvwinch(mission_win, 6, 11) == ' ') {
			mvwprintw(mission_win, 6, 11, "v");
			wrefresh(mission_win);
		}
	}


	void lengthUnCheck() {
		if (mvwinch(mission_win, 3, 8) == 'v') {
			mvwprintw(mission_win, 3, 8, " ");
			wrefresh(mission_win);
		} else if (mvwinch(mission_win, 3, 9) == 'v') {
			mvwprintw(mission_win, 3, 9, " ");
			wrefresh(mission_win);
		}
		else if (mvwinch(mission_win, 3, 10) == 'v') {
			mvwprintw(mission_win, 3, 10, " ");
			wrefresh(mission_win);
		}
		
		wrefresh(mission_win);
	};
	void growthScoreUnCheck() {
		if (mvwinch(mission_win, 4, 9) == 'v') {
			mvwprintw(mission_win, 4, 9, " ");
			wrefresh(mission_win);
		}
		else if (mvwinch(mission_win, 4, 10) == 'v') {
			mvwprintw(mission_win, 4, 10, " ");
			wrefresh(mission_win);
		}
	};
	void poisonScoreUnCheck() {
		if (mvwinch(mission_win, 5, 9) == 'v') {
			mvwprintw(mission_win, 5, 9, " ");
			wrefresh(mission_win);
		}
		else if (mvwinch(mission_win, 5, 10) == 'v') {
			mvwprintw(mission_win, 5, 10, " ");
			wrefresh(mission_win);
		}
	};
	void gateScoreUnCheck() {
		if (mvwinch(mission_win, 6, 9) == 'v') {
			mvwprintw(mission_win, 6, 9, " ");
			wrefresh(mission_win);
		}
		else if (mvwinch(mission_win, 6, 10) == 'v') {
			mvwprintw(mission_win, 6, 10, " ");
			wrefresh(mission_win);
		}
	};

	void clear()
	{
		wclear(mission_win);
	}

	void refresh()
	{
		wrefresh(mission_win);
	}
};
