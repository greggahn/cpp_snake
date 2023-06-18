#pragma once
#include <curses.h>

class SnakePic // �̼��� �Ϸ��� ������ ����� snake �׸� �Ϻθ� �׸� (�� ��������)
{
	WINDOW* snake_win;
public:


	SnakePic() {
		snake_win = newwin(30, 25, 0, 45);
	}

	void initialize() {
		clear();
		wrefresh(snake_win);
	};
	void wdelwin() {
		delwin(snake_win);
	};
	void drawPart1() {
		mvwprintw(snake_win, 3, 12, "     _______..__   __.      ___       __  ___  _______ ");
	mvwprintw(snake_win, 4, 12, "    /       ||  \\ |  |     /   \\     |  |/  / |   ____|");
	mvwprintw(snake_win, 5, 12, "   |   (----`|   \\|  |    /  ^  \\    |  '  /  |  |__   ");
	mvwprintw(snake_win, 6, 12, "    \\   \\    |  . `  |   /  /_\\  \\   |    <   |   __|  ");
	mvwprintw(snake_win, 7, 12, ".----)   |   |  |\\   |  /  _____  \\  |  .  \\  |  |____ ");
	mvwprintw(snake_win, 8, 12, "|_______/    |__| \\__| /__/     \\__\\ |__|\\__\\ |_______|");
	mvwprintw(snake_win, 9, 12,  "     _______      ___      .___  ___.  _______ ");
	mvwprintw(snake_win, 10, 14, "  /  _____|    /   \\     |   \\/   | |   ____|");
	mvwprintw(snake_win, 11, 14, " |  |  __     /  ^  \\    |  \\  /  | |  |__");
	mvwprintw(snake_win, 12, 14, " |  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|");
	mvwprintw(snake_win, 13, 14, " |  |__| |  /  _____  \\  |  |  |  | |  |____  ");
	mvwprintw(snake_win, 14, 14, "  \\______| /__/     \\__\\ |__|  |__| |_______|");
		wrefresh(snake_win);
	};

	void clear() {
		wclear(snake_win);
	}

	void refresh() {
		wrefresh(snake_win);
	};
};